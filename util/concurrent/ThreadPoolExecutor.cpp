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

    if(queuesize != -1) {
        mPool = createBlockingQueue<FutureTask>(queuesize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    mHandlers = createArrayList<Thread>();

    mThreadNum = threadnum;

    for(int i = 0; i < threadnum;i++) {
        Thread thread = createThread([](BlockingQueue<FutureTask> &pool) {
            while(1) {
                FutureTask mCurrentTask = pool->deQueueFirst();
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
        },mPool);
        thread->start();
        mHandlers->add(thread);
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
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
            continue;
        } 
        break;
    }
    mPool->destroy();
    //interrupt all thread
    ListIterator<Thread> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        Thread t = iterator->getValue();
        t->interrupt();
        iterator->next();
    }
    
    return 0;
}

Future _ThreadPoolExecutor::submit(Runnable r) {
    if(r == nullptr || mStatus->get() != LocalStatus::Running) {
        return nullptr;
    }
    FutureTask task = createFutureTask(r);
    mPool->enQueueLast(task);
    return createFuture(task);
}

bool _ThreadPoolExecutor::isTerminated() {
    return mStatus->get() == LocalStatus::ShutDown;
}

void _ThreadPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    
    if(mStatus->get() != LocalStatus::ShutDown){
        return -InvalidStatus;
    }
    
    bool isWaitForever = (millseconds == 0);
    
    ListIterator<Thread> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        Thread handler = iterator->getValue();
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

}
