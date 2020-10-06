#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "Thread.hpp"
#include "AutoLock.hpp"
#include "ThreadLocal.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

ThreadLocal<Thread> mThreads = createThreadLocal<Thread>();

void doThreadExit(_Thread *thread) {
    pthread_detach(thread->getThreadId());
    mThreads->remove(thread->getThreadId());
}

//------------Thread Stack function---------------//
void cleanup(void *th) {
    _Thread *thread = static_cast<_Thread *>(th);
    if(thread->getRunnable() != nullptr) {
        thread->getRunnable()->onInterrupt();
    } else {
        thread->onInterrupt();
    }
    
    {
        AutoLock ll(thread->mJoinMutex);
        thread->mStatus = st(Thread)::Complete;
        thread->mJoinDondtion->notifyAll();
    }
    
    doThreadExit(thread);
}

//------------Thread---------------//
void* _Thread::localRun(void *th) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    _Thread *thread = static_cast<_Thread *>(th);

    sp<_Thread> localThread;
    localThread.set_pointer(thread);

    mThreads->set(thread->getThreadId(),localThread);
   
    thread->mStatus = st(Thread)::Running;
    thread->bootFlag->orAndGet(1);
    
    pthread_cleanup_push(cleanup, th);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    if(thread->mStatus == WaitExit) {
        goto end;
    }

    thread->initPolicyAndPriority();
    thread->setSchedPolicy(SchedOther);
    thread->setPriority(thread->mPriority);
    if(thread->mName != nullptr) {
        pthread_setname_np(thread->mPthread,thread->mName->toChars());
    }
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    if(thread->mRunnable != nullptr) {
        thread->mRunnable->run();
        thread->mRunnable = nullptr;
    } else {
        thread->run();
    }

    thread->onComplete();
end:
    pthread_cleanup_pop(0);
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoLock ll(thread->mJoinMutex);
        thread->mStatus = Complete;
        thread->mJoinDondtion->notifyAll();
    }
  
    localThread.remove_pointer();

    doThreadExit(thread);
    return nullptr;
}


_Thread::_Thread():_Thread(nullptr,nullptr) {
}

_Thread::_Thread(Runnable run):_Thread{nullptr,run} {
}

_Thread::_Thread(String name,Runnable run){
    if(name != nullptr) {
        mName = name;    
    }
    
    mRunnable = run;
   
    mPriority = LowPriority;
    mStatus = NotStart;
    bootFlag = createAtomicInteger(0);

    mProtectMutex = createMutex("ThreadProtectMutex");

    mJoinMutex = createMutex("ThreadJoinMutex");

    mJoinDondtion = createCondition();
}

int _Thread::setName(String name) {
    switch(mStatus) {
        case Idle:
        case NotStart:
            return -NotStart;

        case Complete:
            return -AlreadyComplete;
    }

    mName = name;
    return pthread_setname_np(mPthread,name->toChars());
}

String _Thread::getName() {
    return mName;
}

_Thread::~_Thread(){
    this->quit();
}

Runnable _Thread::getRunnable() {
    return mRunnable;
}

void _Thread::run() {
    //child thread can overwrite it.
}                                                                                                    

int _Thread::start() {
    //pthread_create(&mPthread, &mThreadAttr, localRun, this);
    //if we use sp or declare a thread on stack
    //eg.
    //{
    //   Thread t1 = new Thread(new Runnable(setThreadSchedPolicy) {xxxxxx});
    //   t1->start();
    //}
    //when we leave the life circle,the thread is still running
    //the release may cause the corruption.
    //we should incStrong.after the thread complete,
    //we force decStrong to release;
    //incStrong(0);
    //sp<_Thread> localThread;
    //localThread.set_pointer(this);
    if(mStatus != NotStart) {
        return -AlreadyExecute;
    }

    AutoLock l(mProtectMutex);

    if(mStatus != NotStart) {
        return -AlreadyExecute;
    }

    mStatus = Idle;
    pthread_attr_init(&mThreadAttr);
    if(pthread_create(&mPthread, &mThreadAttr, localRun, this)!= 0) {
        mStatus = NotStart;
        return -1;
    } 

    while(bootFlag->orAndGet(0) == 0) {
        st(Thread)::yield();
    }
    return 0;
}

void _Thread::initPolicyAndPriority() {
    int policy = SchedOther;
    pthread_attr_getschedpolicy(&mThreadAttr,&policy);
    updateThreadPrioTable(policy);
}

void _Thread::join() {
    AutoLock ll(mJoinMutex);
    if(getStatus() == Running) {
        mJoinDondtion->wait(mJoinMutex);
    }
}

int _Thread::join(long timeInterval) {
    AutoLock ll(mJoinMutex);
    if(getStatus() == Running) {
        return mJoinDondtion->wait(mJoinMutex,timeInterval);
    }
    return 0;
}

int _Thread::getStatus() {
    return mStatus;
}

void _Thread::onComplete(){
    //Do nothing
}

void _Thread::quit() {
    if(mStatus == Complete||mStatus == NotStart||mStatus == WaitExit) {
        return;
    }

    AutoLock l(mProtectMutex);
    if(mStatus == Complete||mStatus == NotStart) {
        mStatus = Complete;
        return;
    }else if(mStatus == WaitExit) {
        return;
    }
    
    if(mStatus == Idle) {
        mStatus = WaitExit;
        while(1) {
            join(100);
            if(mStatus == Running) {
                pthread_cancel(mPthread);
                return;
            } else if(mStatus == Complete) {
                return;
            }
        }
        
        return;
    }

    //mStatus = Complete;
   
    pthread_cancel(mPthread);
}

int _Thread::setPriority(int priority) {
    switch(mStatus) {
        case Idle:
        case NotStart:
            return -NotStart;

        case Complete:
            return -AlreadyComplete;
    }
   
    mPriority = priority;
    
    //int schedPrio = mPriorityTable->get(mPolicy)[priority];
    struct sched_param param;
    pthread_attr_getschedparam(&mThreadAttr, &param);

    param.sched_priority = mPriorityArray[priority];
    return pthread_attr_setschedparam(&mThreadAttr, &param);
}

int _Thread::getPriority() {
    if(mStatus != Running) {
        return -NotStart;
    }
    return mPriority;
}

int _Thread::setSchedPolicy(int policy) {
    
    switch(mStatus) {
        case Idle:
        case NotStart:
            return -NotStart;

        case Complete:
            return -AlreadyComplete;
    }

    if(policy != SchedOther
        &&policy != SchedFifo
        &&policy != SchedRr) {
        return -NotSupport;
    }

    int rs = pthread_attr_setschedpolicy(&mThreadAttr, policy);
    if(rs != 0) {
        return -1;
    }

    updateThreadPrioTable(policy);

    struct sched_param param;
    rs = pthread_attr_getschedparam(&mThreadAttr, &param);

    for(int i = LowestPriority;i < PriorityMax-1;i++) {
        if(mPriorityArray[i] < param.sched_priority) {
            mPriority = i;
            break;
        }
    }

    if(rs == 0) {
        return 0;
    }

    return -1;

}

int _Thread::getSchedPolicy() {
    if(mStatus != Running) {
        return -NotStart;
    }

    int policy = SchedOther;
    int rs = pthread_attr_getschedpolicy(&mThreadAttr, &policy);
    if(rs != 0) {
        return -1;
    }
    return policy;
}

pthread_t _Thread::getThreadId() {
    return mPthread;
}

void _Thread::onInterrupt() {
    //need overwrite by child class
}

void _Thread::interruptCheck() {
    pthread_testcancel();
}

void _Thread::yield() {
    pthread_yield();
}

void _Thread::msleep(unsigned long t) {
    usleep(t*1000);
}

int _Thread::updateThreadPrioTable(int policy) {

    int maxPrio = sched_get_priority_max (policy);
    int minPrio = sched_get_priority_min (policy);    
   
    int interval = (maxPrio - minPrio)/HighestPriority;
    for(int i = LowestPriority;i < PriorityMax-1;i++) {
        mPriorityArray[i] = (minPrio/10)*10;
        minPrio += interval;
    }

    mPriorityArray[HighestPriority] = maxPrio;
    return 0;
}

void _Thread::setThreadPriority(int priority) {

    Thread thread = mThreads->get();
    if(thread != nullptr) {
        thread->setPriority(priority);
    }

}

int _Thread::getThreadPriority() {
 
    Thread thread = mThreads->get();
    if(thread != nullptr) {
        return thread->getPriority();
    }

    return -1;
}

int _Thread::setThreadSchedPolicy(int policy) {

    Thread thread = mThreads->get();
    if(thread != nullptr) {
        return thread->setSchedPolicy(policy);
    }

    return -1;
}

int _Thread::getThreadSchedPolicy() {

    Thread thread = mThreads->get();
    if(thread != nullptr) {
        return thread->getSchedPolicy();
    }

    return -1;
}

}
