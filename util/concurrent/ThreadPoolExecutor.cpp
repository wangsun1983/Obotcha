#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "Executors.hpp"

namespace obotcha {

const int _ThreadPoolExecutor::DefaultThreadNum = 4;

_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool):mPool(pool) {
    this->start();
}

_ThreadPoolExecutorHandler::~_ThreadPoolExecutorHandler() {
    
}

bool _ThreadPoolExecutorHandler::shutdownTask(FutureTask task) {
    if(mCurrentTask != nullptr && task == mCurrentTask) {
        quit();
        return true;
    }

    return false;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
    if(mCurrentTask != nullptr && mCurrentTask->getStatus() == st(Future)::Running) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
    }
    mCurrentTask = nullptr;
}

void _ThreadPoolExecutorHandler::run() {
    while(1) {
        mCurrentTask = nullptr;
        mCurrentTask = mPool->deQueueFirst();
        if(mCurrentTask == nullptr) {
            break;
        }

        if(mCurrentTask->getStatus() == st(Future)::Cancel) {
            continue;
        }

        mCurrentTask->onRunning();
    
        Runnable runnable = mCurrentTask->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }

        mCurrentTask->onComplete();
    }
}

bool _ThreadPoolExecutorHandler::isTerminated() {
    return this->getStatus() == Complete;
}

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    init(queuesize,threadnum);
}

_ThreadPoolExecutor::_ThreadPoolExecutor() {
    init(-1,DefaultThreadNum);
}

void _ThreadPoolExecutor::init(int queuesize,int threadnum) {
    mStatusMutex = createMutex("ThreadPoolExecutor");
    mHandlersMutex = createMutex("handlerMutex");

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

    {
        AutoLock l(mStatusMutex);

        if(mIsShutDown) {
            return -AlreadyDestroy;
        }
    }
    
    FutureTask task = createFutureTask(runnable);
    mPool->enQueueLast(task);
    return 0;
}

int _ThreadPoolExecutor::shutdown() {
    {
        AutoLock l(mStatusMutex);
        if(mIsShutDown) {
            return -AlreadyDestroy;
        }
        mIsShutDown = true;
    }

    {
        AutoLock l(mHandlersMutex);
        ListIterator<ThreadPoolExecutorHandler> iterator = mHandlers->getIterator();
        while(iterator->hasValue()) {
            ThreadPoolExecutorHandler h = iterator->getValue();
            h->quit();
            iterator->next();
        }
    }

    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->onShutDown();
            continue;
        } 
        break;
    }
    
    mPool->destroy();

    st(ExecutorRecyler)::getInstance()->add(AutoClone(this));
    
    return 0;
}

Future _ThreadPoolExecutor::submit(Runnable r) {
    if(r == nullptr) {
        return nullptr;
    }

    {
        AutoLock l(mStatusMutex);

        if(mIsShutDown) {
            return nullptr;
        }
    }
    
    FutureTask task = createFutureTask(r,AutoClone(this));
    mPool->enQueueLast(task);

    return createFuture(task);
}

bool _ThreadPoolExecutor::isTerminated() {
    AutoLock l(mStatusMutex);
    return mIsTerminated;
}

void _ThreadPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

void _ThreadPoolExecutor::setAsTerminated() {
    {
        AutoLock l(mStatusMutex);
        mIsTerminated = true;
    }

    mHandlers->clear();
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    {
        AutoLock l(mStatusMutex);
        if(!mIsShutDown) {
            return -InvalidStatus;
        }
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
    return mThreadNum;
}

int _ThreadPoolExecutor::getQueueSize() {
    return mPool->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
}

void _ThreadPoolExecutor::onCancel(FutureTask t) {
    bool isHit = false;
    {
        AutoLock l(mStatusMutex);

        if(mIsShutDown) {
            return;
        }
    }

    {
        AutoLock ll(mHandlersMutex);
        int size = mHandlers->size();
        for(int i = 0;i < size;i++) {
            ThreadPoolExecutorHandler h = mHandlers->get(i);
            if(h != nullptr) {
                if(h->shutdownTask(t)) {
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
