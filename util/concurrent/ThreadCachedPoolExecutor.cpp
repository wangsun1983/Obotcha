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
#include "Executors.hpp"

namespace obotcha {

//---------------ThreadCachedPoolExecutor ---------------------

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
    if(mStatus == ShutDown) {
        return 0;
    }

    mStatus = ShutDown;

    //all task should onInterrupt
    while(1) {
        FutureTask task = mTasks->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
            continue;
        }
        break;
    }

    {
        AutoLock l(mHandlerMutex);
        ListIterator<Thread> iterator = mHandlers->getIterator();
        while(iterator->hasValue()) {
            Thread t = iterator->getValue();
            t->interrupt();
            iterator->next();
        }
    }

    //notify all thread to close
    mTasks->destroy();
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
    if(mStatus != Running) {
        return nullptr;
    }

    FutureTask task = createFutureTask(r);
    Future future = createFuture(task);

    AutoLock l(mHandlerMutex);
    int taskSize = mTasks->size();
    int handlerSize = mHandlers->size();
    if(handlerSize <= taskSize) {
        setUpOneIdleThread();
    }

    mTasks->enQueueLast(task);
    return future;
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        Trigger(InitializeException,"ThreadCachedPool");
    }

    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createArrayList<Thread>();
    mTasks = createBlockingQueue<FutureTask>();
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");
    mStatus = Running;
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

    Thread handler = nullptr;

    handler = createThread([](BlockingQueue<FutureTask> &tasks,Mutex &mutex,ArrayList<Thread> &handlers,long threadtimeout){
        FutureTask mCurrentTask = nullptr;
        while(1) {
            mCurrentTask = tasks->deQueueLast(threadtimeout);
            if(mCurrentTask == nullptr) {                
                AutoLock l(mutex);
                ListIterator<Thread> iterator = handlers->getIterator();
                Thread handler = st(Thread)::current();

                while(iterator->hasValue()) {
                    Thread th = iterator->getValue();
                    if(th == handler) {
                        iterator->remove();
                        return;
                    }
                    iterator->next();
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

            mCurrentTask = nullptr;
        }
    },mTasks,mHandlerMutex,mHandlers,mThreadTimeout);
    
    handler->start();
    
    {
        AutoLock l(mHandlerMutex);
        mHandlers->add(handler);
    }
    
}

}
