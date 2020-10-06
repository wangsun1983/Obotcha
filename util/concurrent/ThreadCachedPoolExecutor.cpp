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

const int _ThreadCachedPoolExecutorHandler::HandleIdle = 0;
const int _ThreadCachedPoolExecutorHandler::HandleBusy = 1;
const int _ThreadCachedPoolExecutorHandler::HandleDestroy = 2;

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   ThreadCachedPoolExecutor service, 
                                                                   long timeout)
                                                                         :mPool(pool),
                                                                         mStop(false) {
    
    mThreadTimeout = timeout;

    mServiceExecutor = service;

    mCurrentTask = nullptr;

    mStop = false;

    mStatusMutex = createMutex("CachedHandlerMutex");
    mStatus = HandleIdle;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    mStatusMutex = createMutex("CachedHandlerMutex");
    {
        AutoLock l(mStatusMutex);
        mStatus = HandleDestroy;
    }
    
    quit();
}

bool _ThreadCachedPoolExecutorHandler::isIdle() {
    AutoLock l(mStatusMutex);
    return mStatus == HandleIdle;
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        //step 1
        if(mCurrentTask == nullptr) {
            //step 2
            {
                AutoLock l(mStatusMutex);
                mStatus = HandleIdle;
            }
            mCurrentTask = mPool->deQueueLast(mThreadTimeout);
            {
                AutoLock l(mStatusMutex);
                mStatus = HandleBusy;
            }
            
            {
                if(mPool->size() != 0) {
                    mServiceExecutor->setUpOneIdleThread();
                }
            }

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
                //printf("cached task run 1 \n");
                r->run();
                //printf("cached task run 2 \n");
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
    //printf("_ThreadCachedPoolExecutorHandler onInterrupt 1 \n");
    {
        if(mCurrentTask != nullptr) {
            //printf("current status is %d \n",mCurrentTask->getStatus());
            if(mCurrentTask->getStatus() == st(Future)::Running) {
                Runnable r = mCurrentTask->getRunnable();
                if(r != nullptr) {
                    r->onInterrupt();
                }
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
        iterator->next();
    }

    //all task should onInterrupt
    while(1) {
        FutureTask task = mTasks->deQueueLastNoBlock();
        if(task != nullptr) {
            task->onShutDown();
            continue;
        }
        break;
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
    if(mStatus->get() != StatusShutDown) {
        return false;
    }

    //printf("handler size is %d \n",mHandlers->size());
    ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadCachedPoolExecutorHandler h = iterator->getValue();
        if(h->getStatus() != st(Thread)::Complete) {
            return false;
        }
        iterator->next();
    }
    return true;
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
    //printf("awaitTermination start 1 \n");
    while(iterator->hasValue()) {
        ThreadCachedPoolExecutorHandler handler = iterator->getValue();
        long current = st(System)::currentTimeMillis();
        //printf("awaitTermination wait at %ld \n",st(System)::currentTimeMillis());
        handler->join(millseconds);
        //printf("awaitTermination finish wait at %ld \n",st(System)::currentTimeMillis());
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
    //printf("thread cached pool start submit \n");
    if(mStatus->get() == StatusShutDown) {
        return nullptr;
    }

    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    Future future = createFuture(task);
    //printf("thread cached pool start submit 2 \n");
    AutoLock l(mHandlerMutex);
    if( mTasks->size() > 0) {
        //printf("thread cached pool start submit 3 \n");
        setUpOneIdleThread();
    } else if(mTasks->size() == 0) {
        //we should check whether there is a idle thread
        if(mHandlers->size() == 0) {
            setUpOneIdleThread();
        } else {
            ListIterator<ThreadCachedPoolExecutorHandler> iterator = mHandlers->getIterator();
            while(iterator->hasValue()) {
                ThreadCachedPoolExecutorHandler handler = iterator->getValue();
                if(handler->isIdle()) {
                    mTasks->enQueueLast(task);
                    return future;
                }
                iterator->next();
            }

            setUpOneIdleThread();
        }
    }
    //printf("thread cached pool start submit 4\n");
    
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
        if(handler->shutdownTask(task)) {
            iterator->remove();
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
    //printf("wait CachePoll Executor release \n");
    awaitTermination(1000);
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
    //printf("thread cached pool setUpOneIdleThread 1 \n");
    AutoLock l(mHandlerMutex);
    if(mHandlers->size() >= maxThreadNum) {
        return;
    }

    ThreadCachedPoolExecutor executor;
    executor.set_pointer(this);

    ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mTasks,
                    executor,
                    mThreadTimeout);
    handler->start();
    //printf("thread cached pool setUpOneIdleThread 2\n");
    while(handler->getStatus() == NotStart) {
        //printf("thread cached pool setUpOneIdleThread 3 \n");
        usleep(100);
    }
    //printf("thread cached pool setUpOneIdleThread 4 \n");
    mHandlers->add(handler);
}



}
