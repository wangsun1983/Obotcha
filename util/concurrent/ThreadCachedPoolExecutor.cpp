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
#include "FutureTask.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "Error.hpp"

namespace obotcha {

//---------------ThreadCachedPoolExecutor ---------------------
_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        Trigger(InitializeException,"ThreadCachedPool");
    }

    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createArrayList<Thread>();
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");
    mTasks = createBlockingQueue<FutureTask>();
    mStatus = Running;
    mIdleNum = createAtomicInteger(0);
}

int _ThreadCachedPoolExecutor::shutdown(){
    {
        AutoLock l(mTasks->mMutex);
        if(mStatus == ShutDown) {
            return 0;
        }
        mStatus = ShutDown;

        mTasks->foreach([](FutureTask &t) {
            t->cancel();
            return 1;
        });

        //notify all thread to close
        mTasks->destroy();
    }

    {
        AutoLock l(mHandlerMutex);
        mHandlers->foreach([](Thread &t) {
            t->interrupt();
            return 1;
        });
    }
    
    return 0;
}

bool _ThreadCachedPoolExecutor::isShutDown() {
    return mStatus == ShutDown;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    AutoLock l(mHandlerMutex);
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

void _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    {
        AutoLock l(mTasks->mMutex);
        if(mStatus == Running) {
            return -InvalidStatus;
        }
    }

    bool isWaitForever = (millseconds == 0);

    ListIterator<Thread> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        Thread handler = iterator->getValue();
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

Future _ThreadCachedPoolExecutor::poolSubmit(Runnable r) {
    Future future = nullptr;
    {
        AutoLock l(mTasks->mMutex);
        if(mStatus != Running) {
            return nullptr;
        }
        FutureTask task = createFutureTask(r);
        future = createFuture(task);
        mTasks->enQueueLastNoLock(task);
    }
    if(mIdleNum->get() == 0) {
        setUpOneIdleThread();
    }
    
    return future;
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    {
        AutoLock l(mTasks->mMutex);
        if(mStatus != Running) {
            return;
        }
    }

    {
        AutoLock l(mHandlerMutex);
        if(mHandlers->size() >= maxThreadNum) {
            return;
        }
    }

    Thread handler = createThread([](ThreadCachedPoolExecutor &executor){
        FutureTask mCurrentTask = nullptr;
        while(1) {
            mCurrentTask = executor->mTasks->deQueueFirst(executor->mThreadTimeout);
            executor->mIdleNum->subAndGet(1); 
            if(mCurrentTask == nullptr) {
                AutoLock l(executor->mHandlerMutex);
                Thread handler = st(Thread)::current();
                executor->mHandlers->remove(handler);
                executor = nullptr;
                return;
            }
            if(mCurrentTask->getStatus() != st(Future)::Cancel) {
                mCurrentTask->onRunning();
                Runnable r = mCurrentTask->getRunnable();
                if(r != nullptr) {
                    r->run();
                }
                mCurrentTask->onComplete();
            }
            executor->mIdleNum->addAndGet(1); 
            mCurrentTask = nullptr;
        }
    },AutoClone(this));
    mIdleNum->addAndGet(1);
    handler->start();
    {
        AutoLock l(mHandlerMutex);
        mHandlers->add(handler);
    }
}

}
