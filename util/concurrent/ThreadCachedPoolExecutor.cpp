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
#include "Executors.hpp"

namespace obotcha {

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   ThreadCachedPoolExecutor service, 
                                                                   long timeout)
                                                                         :mPool(pool){
    
    mThreadTimeout = timeout;

    mServiceExecutor = service;

    mCurrentTask = nullptr;

    mStatusMutex = createMutex("CachedHandlerMutex");

    mStatus = HandleIdle;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
}

bool _ThreadCachedPoolExecutorHandler::isIdle() {
    AutoLock l(mStatusMutex);
    return mStatus == HandleIdle;
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(1) {
        {
            AutoLock l(mStatusMutex);
            if(mStatus == HandleDestroy) {
                mServiceExecutor->onThreadComplete(AutoClone(this));
                break;
            }
        }

        if(mCurrentTask == nullptr) {
            {
                AutoLock l(mStatusMutex);
                mStatus = HandleIdle;
            }
            mCurrentTask = mPool->deQueueLast(mThreadTimeout);
            {
                AutoLock l(mStatusMutex);
                mStatus = HandleBusy;
            }
            
            if(mCurrentTask != nullptr){
                if(mPool->size() != 0) {
                    mServiceExecutor->setUpOneIdleThread();
                }
            } else {
                AutoLock l(mStatusMutex);
                mStatus = HandleDestroy;
                continue;
            }
        }
  
        if(mCurrentTask->getStatus() != st(Future)::Cancel) {
            mCurrentTask->onRunning();
            
            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->run();
            }
            
            mCurrentTask->onComplete();
        }

        mCurrentTask = nullptr;
        
        if(mPool->size() != 0) {
            mCurrentTask = mPool->deQueueLastNoBlock();
        }
    }

    mServiceExecutor = nullptr;
}

//---------------ThreadCachedPoolExecutor ---------------------

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
    if(mStatus == StatusShutDown || mStatus == StatusTerminate) {
        return 0;
    }

    mStatus = StatusShutDown;

    //all task should onInterrupt
    while(1) {
        FutureTask task = mTasks->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
            continue;
        }
        break;
    }

    //notify all thread to close
    mTasks->destroy();

    st(ExecutorRecyler)::getInstance()->add(AutoClone(this));
    return 0;
}

int _ThreadCachedPoolExecutor::execute(Runnable r) {
    
    if(submit(r) == nullptr) {
        return -InvalidStatus;
    }
    return 0;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return mStatus == StatusTerminate;
}

void _ThreadCachedPoolExecutor::setAsTerminated() {
    mStatus = StatusTerminate;
    mHandlers->clear();
}

void _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    switch(mStatus) {
        case StatusRunning:
        return -InvalidStatus;

        case StatusTerminate:
        return 0;
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

void _ThreadCachedPoolExecutor::submit(FutureTask task) {
    AutoLock l(mHandlerMutex);
    if( mTasks->size() > 0) {
        setUpOneIdleThread();
    } else if(mTasks->size() == 0) {
        if(mHandlers->size() == 0) {
            setUpOneIdleThread();
        } else {
            ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
            while(iterator->hasValue()) {
                ThreadCachedPoolExecutorHandler handler = iterator->getValue();
                if(handler->isIdle()) {
                    mTasks->enQueueLast(task);
                    return;
                }
                iterator->next();
            }

            setUpOneIdleThread();
        }
    }
    mTasks->enQueueLast(task);
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mStatus != StatusRunning) {
        return nullptr;
    }

    FutureTask task = createFutureTask(r);
    Future future = createFuture(task);
    submit(task);
    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        Trigger(InitializeException,"ThreadCachedPool");
    }

    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();
    mTasks = createBlockingQueue<FutureTask>();
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");
    mStatus = StatusRunning;
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
}

void _ThreadCachedPoolExecutor::onThreadComplete(ThreadCachedPoolExecutorHandler h) {
    AutoLock l(mHandlerMutex);
    mHandlers->remove(h);
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    if(mStatus != StatusRunning) {
        return;
    }

    {
        AutoLock l(mHandlerMutex);
        if(mHandlers->size() >= maxThreadNum) {
            return;
        }
    }

    ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mTasks,
                    AutoClone(this),
                    mThreadTimeout);
    handler->start();
    while(handler->getStatus() == NotStart) {
        usleep(100);
    }
    
    {
        AutoLock l(mHandlerMutex);
        mHandlers->add(handler);
    }
    
}

}
