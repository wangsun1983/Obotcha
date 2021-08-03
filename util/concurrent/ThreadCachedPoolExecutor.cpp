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
        Trigger(InitializeException,"ThreadCachedPool illeagal param");
    }

    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createArrayList<Thread>();
    mHandlerMutex = createMutex();
    mTasks = createBlockingQueue<FutureTask>(queuesize);
    mStatus = Running;
    mIdleNum = createAtomicInteger(0);
}

int _ThreadCachedPoolExecutor::shutdown(){
    if(mStatus == ShutDown) {
        return 0;
    }
    
    mStatus = ShutDown;

    mTasks->freeze();
    mTasks->foreach([](FutureTask &t) {
        t->cancel();
        return Global::Continue;
    });
    //notify all thread to close
    mTasks->destroy();
    mTasks->unfreeze();
    
    {
        AutoLock l(mHandlerMutex);
        mHandlers->foreach([](Thread &t) {
            t->interrupt();
            return Global::Continue;
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
    if(mStatus == Running) {
        return -InvalidStatus;
    }

    bool isWaitForever = (millseconds == 0);

    //ListIterator<Thread> iterator = mHandlers->getIterator();
    ArrayList<Thread> list = createArrayList<Thread>();
    {
        AutoLock l(mHandlerMutex);
        list->add(mHandlers);
    }
    auto iterator = list->getIterator();
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

    if(mStatus != Running) {
        return nullptr;
    }

    FutureTask task = createFutureTask(r);
    Future future = createFuture(task);
    mTasks->enQueueLast(task);
    if(mIdleNum->get() == 0) {
        setUpOneIdleThread();
    }
    
    return future;
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    if(mStatus != Running) {
        return;
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
                Thread handler = st(Thread)::current();
                {
                    AutoLock l(executor->mHandlerMutex);
                    executor->mHandlers->remove(handler);
                    executor = nullptr;
                }
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
    
    handler->start();
    {
        AutoLock l(mHandlerMutex);
        mHandlers->add(handler);
    }

    mIdleNum->addAndGet(1);
}

}
