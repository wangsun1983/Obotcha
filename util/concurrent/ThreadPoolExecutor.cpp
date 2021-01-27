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
    if(task == mCurrentTask) {
        quit();
        return true;
    }

    return false;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
    if(mCurrentTask != nullptr && mCurrentTask->getStatus() == st(Future)::Running) {
        mCurrentTask->onShutDown();
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

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    init(queuesize,threadnum);
}

_ThreadPoolExecutor::_ThreadPoolExecutor(int threadnum) {
    init(-1,threadnum);
}

_ThreadPoolExecutor::_ThreadPoolExecutor() {
    init(-1,DefaultThreadNum);
}

void _ThreadPoolExecutor::init(int queuesize,int threadnum) {
    mStatus = createAtomicInteger(LocalStatus::Idle);

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

    mStatus->set(LocalStatus::Running);
}

int _ThreadPoolExecutor::execute(Runnable runnable) {
    if(runnable == nullptr) {
        return -InvalidParam;
    }

    if(mStatus->get() != LocalStatus::Running) {
        return -AlreadyDestroy;
    }
      
    FutureTask task = createFutureTask(runnable);
    mPool->enQueueLast(task);
    return 0;
}

int _ThreadPoolExecutor::shutdown() {
    int status = mStatus->compareAndSet(LocalStatus::ShutDown);
    if(status == LocalStatus::ShutDown) {
        return -AlreadyDestroy;
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
    if(r == nullptr || mStatus->get() != LocalStatus::Running) {
        return nullptr;
    }
    FutureTask task = createFutureTask(r,AutoClone(this));
    mPool->enQueueLast(task);
    return createFuture(task);
}

bool _ThreadPoolExecutor::isTerminated() {
    return mStatus->get() == LocalStatus::ShutDown;
}

void _ThreadPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

void _ThreadPoolExecutor::setAsTerminated() {
    mStatus->set(LocalStatus::Terminated);
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    if(mStatus->get() == LocalStatus::Terminated) {
        return 0;
    }
    
    if(mStatus->get() != LocalStatus::ShutDown){
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
    return mThreadNum;
}

int _ThreadPoolExecutor::getQueueSize() {
    return mPool->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    if(mStatus->get() == LocalStatus::Running) {
        LOG(ERROR)<<"ThreadPoolExecutor distroy while running";
    }
}

void _ThreadPoolExecutor::onCancel(FutureTask t) {
    if(mStatus->get() == LocalStatus::ShutDown) {
        return;
    }

    {
        AutoLock ll(mHandlersMutex);
        if(mStatus->get() == LocalStatus::Running) {
            int size = mHandlers->size();
            for(int i = 0;i < size;i++) {
                ThreadPoolExecutorHandler h = mHandlers->get(i);
                if(h != nullptr) {
                    if(h->shutdownTask(t)) {
                        mHandlers->remove(h);
                        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);
                        mHandlers->add(h);
                        break;
                    }
                }
            }
        }
    }
}

}
