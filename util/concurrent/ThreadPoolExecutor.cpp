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

const int _ThreadPoolExecutor::DefaultThreadNum = 4;

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    mStatus = LocalStatus::Idle;
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

        for(;;) {
            FutureTask task = mPool->deQueueLastNoBlock();
            if(task != nullptr) {
                task->cancel();
                continue;
            } 
            break;
        }
        mPool->destroy();
    }
    
    //interrupt all thread
    ListIterator<Thread> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        Thread t = iterator->getValue();
        t->interrupt();
        iterator->next();
    }
    return 0;
}

bool _ThreadPoolExecutor::isShtuDown() {
    AutoLock l(mPool->mMutex);
    return mStatus == LocalStatus::ShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    ListIterator<Thread> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        Thread t = iterator->getValue();
        if(t->getStatus() != st(Thread)::Complete) {
            return false;
        }
        iterator->next();
    }

    return true;
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
