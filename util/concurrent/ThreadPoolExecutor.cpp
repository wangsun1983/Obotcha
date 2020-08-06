#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"


namespace obotcha {

#define DEFAULT_THREAD_NUM 4

_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool,sp<_ThreadPoolExecutor> exe):mPool(pool),
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

bool _ThreadPoolExecutorHandler::shutdownTask(FutureTask task) {
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        AutoLock l(mStateMutex);
        if(state == terminateState) {
            return false;
        }

        stop();
        return true;
    }

    return false;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
    {
        AutoLock l(mStateMutex);
        state = terminateState;
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }

    ThreadPoolExecutorHandler h;
    h.set_pointer(this);
    mExecutor->onCompleteNotify(h);
    mExecutor.remove_pointer();
    mThread = nullptr;
}

void _ThreadPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        mCurrentTask = mPool->deQueueFirst();
        if(mCurrentTask == nullptr) {
            break;
        }
        if(mCurrentTask->getStatus() == st(Future)::Cancel) {
            continue;
        }
        
        {
            AutoLock l(mStateMutex);
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
            AutoLock l(mStateMutex);
            state = idleState;

            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onComplete();
            }
        }
    }

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoLock l(mStateMutex);
        state = terminateState;

        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    ThreadPoolExecutorHandler h;
    h.set_pointer(this);
    mExecutor->onCompleteNotify(h);
    mExecutor.remove_pointer();
    mThread = nullptr;
}

void _ThreadPoolExecutorHandler::waitForTerminate() {
    AutoLock l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadPoolExecutorHandler::waitForTerminate(long interval) {
    AutoLock l(mStateMutex);
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
    mHandlersMutex = createMutex("ThreadPoolHandlers");
    mWaitMutex = createMutex("ThreadPoolWaitMutex");
    mWaitCondition = createCondition();

    if(queuesize != -1) {
        mPool = createBlockingQueue<FutureTask>(queuesize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    mHandlers = createArrayList<ThreadPoolExecutorHandler>();

    mThreadNum = threadnum;

    for(int i = 0; i < threadnum;i++) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool,this);
        mHandlers->add(h);
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

    AutoLock l(mProtectMutex);

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

    {
        AutoLock l(mProtectMutex);

        if(mIsShutDown ||mIsTerminated) {
            return -AlreadyDestroy;
        }

        mIsShutDown = true;
    }

    AutoLock ll1(mHandlersMutex);
    ListIterator<ThreadPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadPoolExecutorHandler h = iterator->getValue();
        h->stop();
        iterator->next();
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

    AutoLock l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }
    
    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    mPool->enQueueLast(task);

    return createFuture(task);
}

bool _ThreadPoolExecutor::isTerminated() {
    return mIsTerminated;
}

void _ThreadPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }

    AutoLock ll(mWaitMutex);

    if(mIsTerminated) {
        return 0;
    }

    return mWaitCondition->wait(mWaitMutex,millseconds);
}

void _ThreadPoolExecutor::onCompleteNotify(ThreadPoolExecutorHandler h) {
    AutoLock ll(mHandlersMutex);
    ListIterator<ThreadPoolExecutorHandler>iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadPoolExecutorHandler t = iterator->getValue();
        if(t == h) {
            iterator->remove();
            break;
        }
        iterator->next();
    }

    if(mIsShutDown) {
        if(mHandlers->size() == 0) {         
            AutoLock ll(mWaitMutex);
            mIsTerminated = true;
            mWaitCondition->notifyAll();
        }
    }
}

int _ThreadPoolExecutor::getThreadsNum() {
    AutoLock ll(mProtectMutex);
    return mHandlers->size();
}

int _ThreadPoolExecutor::getQueueSize() {
    return mPool->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    if(!mIsShutDown) {
        //cannot throw exception in destructor
        //throw ExecutorDestructorException("ThreadPoolExecutor destruct error");
        //LOGE(TAG,"ThreadPoolExecutor destruct error");
    }
}

void _ThreadPoolExecutor::onCancel(FutureTask t) {
    bool isHit = false;

    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    AutoLock l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return;
    }
    
    
    ThreadPoolExecutorHandler h = nullptr;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        h = mHandlers->get(i);
        if(h != nullptr) {
            if(h->shutdownTask(t)) {
                AutoLock ll1(mHandlersMutex);
                mHandlers->remove(h);
                isHit = true;
                break;
            }
        }
    }
    
    //we should insert a new
    if(!mIsShutDown && isHit) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool,this);
        AutoLock ll1(mHandlersMutex);
        mHandlers->add(h);
    }
}

}
