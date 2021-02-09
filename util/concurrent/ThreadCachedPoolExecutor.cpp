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
    if(mStatus == StatusShutDown || mStatus == StatusTerminate) {
        return 0;
    }

    mStatus = StatusShutDown;

    //all task should onInterrupt
    while(1) {
        FutureTask task = mTasks->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
            continue;
        }
        break;
    }

    //notify all thread to close
    mTasks->destroy();
    return 0;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return mStatus == StatusTerminate;
}

void _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    switch(mStatus) {
        case StatusRunning:
        return -InvalidStatus;

        case StatusTerminate:
        return 0;
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

void _ThreadCachedPoolExecutor::submit(FutureTask task) {
    AutoLock l(mHandlerMutex);
    int taskSize = mTasks->size();
    int handlerSize = mHandlers->size();
    if(handlerSize <= taskSize) {
        setUpOneIdleThread();
    }

    mTasks->enQueueLast(task);
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
    mStatus = StatusRunning;
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
}

void _ThreadCachedPoolExecutor::setUpOneIdleThread() {
    if(mStatus != StatusRunning) {
        return;
    }

    {
        AutoLock l(mHandlerMutex);
        if(mHandlers->size() >= maxThreadNum) {
            return;
        }
    }

    auto handlerFunction = [this](){
        FutureTask mCurrentTask = nullptr;
        while(1) {
            mCurrentTask = mTasks->deQueueLast(mThreadTimeout);

            if(mCurrentTask == nullptr) {
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
    };
    Thread handler = createThread(handlerFunction);
    handler->start();
    
    {
        AutoLock l(mHandlerMutex);
        mHandlers->add(handler);
    }
    
}

}
