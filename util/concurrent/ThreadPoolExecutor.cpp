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

_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool):mPool(pool),
                                                                         mStop(false){
    this->start();
}

_ThreadPoolExecutorHandler::~_ThreadPoolExecutorHandler() {
    
}

void _ThreadPoolExecutorHandler::stop() {
    mStop = true;
    quit();
}

bool _ThreadPoolExecutorHandler::shutdownTask(FutureTask task) {
    if(mCurrentTask != nullptr && task == mCurrentTask) {
        stop();
        return true;
    }

    return false;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
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

        if(mCurrentTask->getStatus() == st(Future)::Cancel) {
            continue;
        }
        
        if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
            mCurrentTask->onRunning();
        }
    
        Runnable runnable = mCurrentTask->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
     
        if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
            mCurrentTask->onComplete();
        }
    }
}

bool _ThreadPoolExecutorHandler::isTerminated() {
    return this->getStatus() == Complete;
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
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);
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
    return 0;
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

    {
        AutoLock ll1(mHandlersMutex);
        ListIterator<ThreadPoolExecutorHandler> iterator = mHandlers->getIterator();
        while(iterator->hasValue()) {
            ThreadPoolExecutorHandler h = iterator->getValue();
            h->stop();
            iterator->next();
        }
    }

    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
            continue;
        } 
        break;
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
    AutoLock l(mProtectMutex);
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    bool isWaitForever = (millseconds == 0);
    ListIterator<ThreadPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadPoolExecutorHandler handler = iterator->getValue();
        long current = st(System)::currentTimeMillis();
        handler->join(millseconds);
        if(!isWaitForever) {
            long waitInterval = (st(System)::currentTimeMillis() - current);
            millseconds -= waitInterval;
            if(millseconds <= 0) {
                return -WaitTimeout;
            }
        }
        iterator->next();
    }

    return 0;
}

int _ThreadPoolExecutor::getThreadsNum() {
    AutoLock ll(mProtectMutex);
    ListIterator<ThreadPoolExecutorHandler>iterator = mHandlers->getIterator();
    int threadNum = 0;
    while(iterator->hasValue()) {
        ThreadPoolExecutorHandler handler = iterator->getValue();
        if(handler->getStatus() != st(Thread)::Complete) {
            threadNum++;
        }
        iterator->next();
    }

    return threadNum;
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

    {
        AutoLock ll(mHandlersMutex);
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
    }
    
    //we should insert a new
    if(!mIsShutDown && isHit) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);
        AutoLock ll(mHandlersMutex);
        mHandlers->add(h);
    }
}

}
