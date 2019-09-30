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

_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool,_ThreadPoolExecutor* exe):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitTerminate(false),
                                                                         mExecutor(exe){
    mStateMutex = createMutex("ThreadPoolExeHandlerMutex");
    mWaitCond = createCondition();
    Runnable r;
    r.set_pointer(this);
    mThread = createThread(r);

    mExecutorMutex = createMutex("ThreadPoolExecutorMutex");

    state = idleState;
    mThread->start();
}

_ThreadPoolExecutorHandler::~_ThreadPoolExecutorHandler() {
    
}

void _ThreadPoolExecutorHandler::stop() {
    mStop = true;
    mThread->quit();
}

void _ThreadPoolExecutorHandler::onExecutorDestroy() {
    //printf("onExecutorDestroy 1 \n");
    AutoMutex ll(mExecutorMutex);
    //printf("onExecutorDestroy 1 \n");
    mExecutor = nullptr;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
    //printf("ThreadPoolExecutor onInterrutp \n");
    {
        AutoMutex l(mStateMutex);
        state = terminateState;
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    //printf("ThreadPoolExecutor onInterrutp1 \n");
    if(mCurrentTask != nullptr) {
        ////printf("ThreadPoolExecutor onInterrutp2 \n");
        Runnable r = mCurrentTask->getRunnable();
        ////printf("ThreadPoolExecutor onInterrutp3 \n");
        if(r != nullptr) {
            ////printf("ThreadPoolExecutor onInterrutp4 \n");
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }
    //printf("ThreadPoolExecutor onInterrutp5 \n");
    //printf("this count1 is %d \n",this->getStrongCount());
    {
        AutoMutex ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            mExecutor->onHandlerRelease();
        }
    }
    
    mThread = nullptr;
    //printf("this count2 is %d \n",this->getStrongCount());
}

void _ThreadPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        //printf("ThreadPoolExecutor run1 \n");
        mCurrentTask = mPool->deQueueFirst();
        if(mCurrentTask == nullptr) {
            break;
        }
        //printf("ThreadPoolExecutor run2 \n");
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
        //printf("ThreadPoolExecutor run3 \n");
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
        //printf("ThreadPoolExecutor run4 \n");
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

    //printf("ThreadPoolExecutor run end \n");
    {
        AutoMutex ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            mExecutor->onHandlerRelease();
        }
    }
    
    mThread = nullptr;
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
    mProtectMutex = createMutex("ThreadPoolExecutor");

    if(queuesize != -1) {
        mPool = createBlockingQueue<FutureTask>(queuesize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    mHandlers = createConcurrentQueue<ThreadPoolExecutorHandler>();

    mThreadNum = threadnum;

    for(int i = 0; i < threadnum;i++) {
        //printf("init this is %x \n",this);
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool,this);
        mHandlers->enQueueLast(h);
    }

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
        ThreadPoolExecutorHandler h = mHandlers->get(i);
        if(h != nullptr) {
            h->stop();
        }
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
        ThreadPoolExecutorHandler h = mHandlers->get(i);
        if(h != nullptr && !h->isTerminated()) {
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
            ThreadPoolExecutorHandler h = mHandlers->get(i);
            if(h != nullptr) {
                h->waitForTerminate();
            }
        }
        mIsTerminated = true;
        return 0;
    } else {
        for(int i = 0;i < size;i++) {
            long current = st(System)::currentTimeMillis();
            if(millseconds > 0) {
                //mHandlers->get(i)->waitForTerminate(millseconds);
                ThreadPoolExecutorHandler h = mHandlers->get(i);
                if(h != nullptr) {
                    h->waitForTerminate(millseconds);
                }
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

void _ThreadPoolExecutor::onHandlerRelease() {
    //printf("onHandler Release this is %x\n",this);
    AutoMutex ll(mProtectMutex);
    mThreadNum--;

    //printf("onHandler Release mThreadNum is %d \n",mThreadNum);
    if(mThreadNum == 0) {
        mHandlers->clear();
    }
}

int _ThreadPoolExecutor::getThreadsNum() {
    AutoMutex ll(mProtectMutex);
    return mHandlers->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    //printf("~_ThreadPoolExecutor() \n");
    int size = mHandlers->size();

    for(int i = 0;i < size;i++) {
        //printf("~_ThreadPoolExecutor() 3 \n");
        ThreadPoolExecutorHandler h = mHandlers->get(i);
        if(h != nullptr) {
            h->onExecutorDestroy();
        }
    }

    shutdown();
}

}
