#include <stdio.h>
#include <stdlib.h>

#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    mPool = createBlockingQueue<ExecutorTask>(queuesize);    
    mHandlers = createArrayList<Thread>();

    for(int i = 0; i < threadnum;i++) {
        Thread thread = createThread([](ThreadPoolExecutor executor) {
            while(1) {
                ExecutorTask mCurrentTask = nullptr;
                mCurrentTask = executor->mPool->deQueueFirst();
                
                if(mCurrentTask == nullptr) {
                    //clear executor to enable executor release.
                    executor = nullptr;
                    return;
                }
                mCurrentTask->execute();
            }
        },AutoClone(this));

        thread->start();
        mHandlers->add(thread);
    }

    mStatus = LocalStatus::Running;
}

int _ThreadPoolExecutor::shutdown() {
    {
        if(mStatus != Running) {
            return -InvalidStatus;
        }

        mStatus = ShutDown;

        mPool->freeze();
        mPool->foreach([](ExecutorTask &task) {
            task->cancel();
            return Global::Continue;
        });

        mPool->destroy();
        mPool->unfreeze();
    }
    
    //interrupt all thread
    mHandlers->foreach([](Thread t){
        t->interrupt();
        return Global::Continue;
    });

    return 0;
}

bool _ThreadPoolExecutor::isShtuDown() {
    return mStatus == LocalStatus::ShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    bool isTerminated = true;
    mHandlers->foreach([&isTerminated](Thread &t) {
        if(t->getStatus() != st(Thread)::Complete) {
            isTerminated = false;
            return Global::Break;
        }
        return Global::Continue;
    });

    return isTerminated;
}

void _ThreadPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    
    if(mStatus != LocalStatus::ShutDown){
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
    return mHandlers->size();
}

int _ThreadPoolExecutor::getQueueSize() {
    return mPool->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
}

}
