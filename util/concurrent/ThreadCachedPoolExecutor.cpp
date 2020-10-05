#include <stdio.h>
#include <vector>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "Error.hpp"

namespace obotcha {

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   ThreadCachedPoolExecutor service, 
                                                                   long timeout)
                                                                         :mPool(pool),
                                                                         mStop(false) {
    
    mThreadTimeout = timeout;

    mCurrentTask = nullptr;

    mStop = false;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    quit();
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        //step 1
        if(mCurrentTask == nullptr) {
            //step 2
            mCurrentTask = mPool->deQueueLast(mThreadTimeout);
            if(mCurrentTask == nullptr) {
                ThreadCachedPoolExecutorHandler h;
                h.set_pointer(this);
                mServiceExecutor->onThreadComplete(h);
                stop();
                return;
            }
        }
    
        //step 3    
        if(mCurrentTask->getStatus() != st(Future)::Cancel) {
            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onRunning();
            }

            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->run();
            }
            
            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onComplete();
            }    
        }

        mCurrentTask = nullptr;   
        
        if(mPool->size() != 0) {
            mCurrentTask = mPool->deQueueLastNoBlock();
        }
    }

end:
    mServiceExecutor = nullptr;
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    {
        if(mCurrentTask != nullptr) {
            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->onInterrupt();
            }
            mCurrentTask = nullptr;
        }
    }
    mServiceExecutor = nullptr;
}

bool _ThreadCachedPoolExecutorHandler::shutdownTask(FutureTask task) {
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        stop();
        return true;
    }

    return false;
}

//---------------ThreadCachedPoolExecutor ---------------------
const int _ThreadCachedPoolExecutor::StatusIdle = 0;
const int _ThreadCachedPoolExecutor::StatusRunning = 1;
const int _ThreadCachedPoolExecutor::StatusShutDown = 2;
const int _ThreadCachedPoolExecutor::DefaultWaitTime = 15*1000;
const int _ThreadCachedPoolExecutor::DefaultMaxThreadNums = 4;
const int _ThreadCachedPoolExecutor::DefaultQueueNums = 32;

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    init(queuesize,minthreadnum,maxthreadnum,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int maxthreadnum,long timeout) {
    init(-1,0,maxthreadnum,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor() {
    init(-1,0,DefaultMaxThreadNums,DefaultWaitTime);
}

int _ThreadCachedPoolExecutor::shutdown(){
    if(mStatus->get() == StatusShutDown) {
        return 0;
    }

    mStatus->set(StatusShutDown);

    AutoLock l(mHandlerMutex);
    ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadCachedPoolExecutorHandler handler = iterator->getValue();
        handler->stop();
    }
    return 0;
}

int _ThreadCachedPoolExecutor::execute(Runnable r) {
    
    if(submit(r) == nullptr) {
        return -InvalidStatus;
    }
    return 0;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    AutoLock l(mHandlerMutex);
    return (mStatus->get() == StatusShutDown) && mHandlers->size() == 0;
}

void _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(mStatus->get() != StatusShutDown) {
        return -InvalidStatus;
    }

    bool isWaitForever = (millseconds == 0);

    ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadCachedPoolExecutorHandler handler = iterator->getValue();
        long current = st(System)::currentTimeMillis();
        handler->join(millseconds);
        long interval = (st(System)::currentTimeMillis() - current);
        if(!isWaitForever) {
            millseconds -= interval;
            if(millseconds <= 0) {
                return -WaitTimeout;
            }
        }
        iterator->next();
    }

    return 0;
}

int _ThreadCachedPoolExecutor::getThreadsNum() {
    AutoLock l(mHandlerMutex);
    return mHandlers->size();
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mStatus->get() == StatusShutDown) {
        return nullptr;
    }

    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    Future future = createFuture(task);
    
    AutoLock l(mHandlerMutex);
    if( mTasks->size() > 0 && mHandlers->size() < maxThreadNum) {
        setUpOneIdleThread();
    }
    mTasks->enQueueLast(task);

    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        throw InitializeException(createString("ThreadCachedPool"));
    }

    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();
    mTasks = createBlockingQueue<FutureTask>();
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");
    mStatus = createAtomicInteger(StatusIdle);
}

void _ThreadCachedPoolExecutor::onCancel(FutureTask task) {
    AutoLock l(mHandlerMutex);
    ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
    bool isFound = false;

    while(iterator->hasValue()) {
        ThreadCachedPoolExecutorHandler handler = iterator->getValue();
        if(handler == handler) {
            iterator->remove();
            handler->stop();
            isFound = true;
            break;
        }
        iterator->next();
    }

    if(isFound) {
        setUpOneIdleThread();
    }
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    //TODO
}

void _ThreadCachedPoolExecutor::onThreadComplete(ThreadCachedPoolExecutorHandler h) {
    AutoLock l(mHandlerMutex);
    ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadCachedPoolExecutorHandler handler = iterator->getValue();
        if(handler == h) {
            iterator->remove();
            return;
        }
        iterator->next();
    }
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    AutoLock l(mHandlerMutex);
    ThreadCachedPoolExecutor executor;
    executor.set_pointer(this);

    ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mTasks,
                    executor,
                    mThreadTimeout);
    handler->start();
    while(handler->getStatus() == NotStart) {
        usleep(100);
    }

    mHandlers->add(handler);
}

}
