#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    mPool = createBlockingQueue<FutureTask>(queuesize);    
    mHandlers = createArrayList<Thread>();

    for(int i = 0; i < threadnum;i++) {
        Thread thread = createThread([](ThreadPoolExecutor &executor) {
            while(1) {
                FutureTask mCurrentTask = nullptr;
                mCurrentTask = executor->mPool->deQueueFirst();
                
                if(mCurrentTask == nullptr) {
                    //clear executor to enable executor release.
                    executor = nullptr;
                    return;
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
        },AutoClone(this));

        thread->start();
        mHandlers->add(thread);
    }

    mStatus = LocalStatus::Running;
}

int _ThreadPoolExecutor::shutdown() {
    {
        AutoLock l(mPool->mMutex);
        if(mStatus != Running) {
            return -InvalidStatus;
        }

        mStatus = ShutDown;

        mPool->foreach([](FutureTask &task) {
            task->cancel();
            return 1;
        });

        mPool->destroy();
    }
    
    //interrupt all thread
    mHandlers->foreach([](Thread t){
        t->interrupt();
        return 1;
    });

    return 0;
}

bool _ThreadPoolExecutor::isShtuDown() {
    AutoLock l(mPool->mMutex);
    return mStatus == LocalStatus::ShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    bool isTerminated = true;
    mHandlers->foreach([&isTerminated](Thread &t) {
        if(t->getStatus() != st(Thread)::Complete) {
            isTerminated = false;
            return -1;
        }
        return 1;
    });

    return isTerminated;
}

void _ThreadPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    {
        AutoLock l(mPool->mMutex);
        if(mStatus != LocalStatus::ShutDown){
            return -InvalidStatus;
        }
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
    return mHandlers->size();
}

int _ThreadPoolExecutor::getQueueSize() {
    return mPool->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
}

}
