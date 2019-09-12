#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"

static int id = 0;

#define DEFAULT_THREAD_NUM 4

namespace obotcha {
_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitTerminate(false){
    mStateMutex = createMutex("ThreadPoolExeHandlerMutex");
    mWaitCond = createCondition();
    Runnable r;
    r.set_pointer(this);
    mThread = createThread(r);
    state = idleState;
    mThread->start();
}

void _ThreadPoolExecutorHandler::forceStop() {
    mThread->exit();
    mStop = true;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
    AutoMutex l(mStateMutex);
    state = terminateState;
    if(isWaitTerminate) {
        mWaitCond->notify();
        isWaitTerminate = false;
    }

    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }
}

void _ThreadPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        mCurrentTask = mPool->deQueueFirst();
        if(mCurrentTask == nullptr) {
            break;
        }

        if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
            continue;
        }
        
        {
            AutoMutex l(mStateMutex);
            state = busyState;
            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onRunning();
            }
        }

        Runnable runnable = mCurrentTask->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }

        {
            AutoMutex l(mStateMutex);
            state = idleState;

            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onComplete();
            }
        }
    }

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoMutex l(mStateMutex);
        state = terminateState;

        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }
}

void _ThreadPoolExecutorHandler::waitForTerminate() {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadPoolExecutorHandler::waitForTerminate(long interval) {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex,interval);
    }
}

void _ThreadPoolExecutorHandler::stop() {
    mStop = true;
}

bool _ThreadPoolExecutorHandler::isTerminated() {
    return state == terminateState;
}

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    init(queuesize,threadnum);
}

_ThreadPoolExecutor::_ThreadPoolExecutor() {
    init(-1,DEFAULT_THREAD_NUM);
}

void _ThreadPoolExecutor::init(int queuesize,int threadnum) {
    if(queuesize != -1) {
        mPool = createBlockingQueue<FutureTask>(queuesize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    mHandlers = createConcurrentQueue<ThreadPoolExecutorHandler>();

    mThreadNum = threadnum;

    for(int i = 0; i < threadnum;i++) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);
        mHandlers->enQueueLast(h);
    }

    mProtectMutex = createMutex("ThreadPoolExecutor");

    mIsTerminated = false;

    mIsShutDown = false;
}

int _ThreadPoolExecutor::execute(Runnable runnable) {
    if(runnable == nullptr) {
        return -InvalidParam;
    }

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_NORMAL,runnable);

    mPool->enQueueLast(task);
}

int _ThreadPoolExecutor::shutdown() {
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->stop();
    }

    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }

    mPool->clear();

    return 0;
}

int _ThreadPoolExecutor::shutdownNow() {
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    mPool->clear();

    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->forceStop();
    }

    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }

    mIsTerminated = true;

    return 0;
}

Future _ThreadPoolExecutor::submit(Runnable r) {
    if(r == nullptr) {
        return nullptr;
    }

    if(mIsShutDown||mIsTerminated) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    mPool->enQueueLast(task);

    return createFuture(task);
}

bool _ThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    if(mIsTerminated) {
        return true;
    }

    AutoMutex l(mProtectMutex);

    if(mIsTerminated) {
        return true;
    }

    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        if(!mHandlers->get(i)->isTerminated()) {
            return false;
        }
    }

    mIsTerminated = true;
    return mIsTerminated;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }

    int size = mHandlers->size();

    if(millseconds == 0) {
        for(int i = 0;i < size;i++) {
            mHandlers->get(i)->waitForTerminate();
        }
        mIsTerminated = true;
        return 0;
    } else {
        for(int i = 0;i < size;i++) {
            long current = st(System)::currentTimeMillis();
            if(millseconds >= 0) {
                mHandlers->get(i)->waitForTerminate(millseconds);
            } else {
                break;
            }
            millseconds -= (st(System)::currentTimeMillis() - current);
        }

        if(millseconds <= 0) {
            return -WaitTimeout;
        }
    }

    return 0;
}

int _ThreadPoolExecutor::getThreadsNum() {
    return mThreadNum;
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    shutdownNow();
}

}
