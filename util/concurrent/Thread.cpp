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
        AutoLock l(thread->mStatusMutex);
        thread->mStatus = st(Thread)::Complete;
    }

    {

        AutoLock ll(thread->mJoinMutex);
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
    
    {
        AutoLock l(thread->mStatusMutex);
        thread->mStatus = st(Thread)::Running;
    }
    
    thread->bootFlag->orAndGet(1);
    
    pthread_cleanup_push(cleanup, th);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    {
        AutoLock l(thread->mStatusMutex);
        if(thread->mStatus == WaitExit) {
            goto end;
        }
    }

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
        {
            AutoLock l(thread->mStatusMutex);
            thread->mStatus = Complete;
        }

        AutoLock ll(thread->mJoinMutex);
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

    mStatus = NotStart;
    
    bootFlag = createAtomicInteger(0);

    mStatusMutex = createMutex("ThreadStatusMutex");

    mJoinMutex = createMutex("ThreadJoinMutex");

    mJoinDondtion = createCondition();
}

int _Thread::setName(String name) {
    if(!isRunning()) {
        return -InvalidStatus;
    }

    mName = name;
    return pthread_setname_np(mPthread,name->toChars());
}

String _Thread::getName() {
    return mName;
}

_Thread::~_Thread(){
    //this->quit();
}

Runnable _Thread::getRunnable() {
    return mRunnable;
}

void _Thread::run() {
    //child thread can overwrite it.
}

void _Thread::detach() {
    if(!isRunning()) {
        return;
    }
    pthread_detach(getThreadId());
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
    {
        AutoLock l(mStatusMutex);

        if(mStatus != NotStart) {
            return -AlreadyExecute;
        }

        mStatus = Idle;
    }

    pthread_attr_init(&mThreadAttr);
    if(pthread_create(&mPthread, &mThreadAttr, localRun, this)!= 0) {
        {  
            AutoLock l(mStatusMutex);
            mStatus = ErrorStatus;
        }
        return -1;
    } 

    while(bootFlag->orAndGet(0) == 0) {
        st(Thread)::yield();
    }

    return 0;
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
    if(!isRunning()) {
        return;
    }

    while(1) {
        if(mStatus == Idle) {
            usleep(1000*10);
            continue;
        }

        pthread_cancel(mPthread);
        break;
    }
}

int _Thread::getPriority() {
    int policy = getSchedPolicy();
    const int min_prio = sched_get_priority_min(policy);
    const int max_prio = sched_get_priority_max(policy);
    if (min_prio == -1 || max_prio == -1) {
        return -InvalidStatus;
    }

    if (max_prio - min_prio <= 2) {
        return -InvalidStatus;
    }

    sched_param param;
    pthread_attr_getschedparam(&mThreadAttr, &param);
    const int top_prio = max_prio - 1;
    const int low_prio = min_prio + 1;
    if(param.sched_priority == low_prio) {
        return kLowPriority;
    } else if(param.sched_priority == (low_prio + top_prio - 1) / 2) {
        return kNormalPriority;
    } else if(param.sched_priority == std::max(top_prio - 2, low_prio)) {
        return kHighPriority;
    } else if(param.sched_priority == std::max(top_prio - 1, low_prio)) {
        return kHighestPriority;
    } else if(param.sched_priority == top_prio) {
        return kRealtimePriority;
    }

    return -1;
}

int _Thread::setPriority(int priority) {
    if(!isRunning()) {
        return -InvalidStatus;
    }

    int policy = getSchedPolicy();
    const int min_prio = sched_get_priority_min(policy);
    const int max_prio = sched_get_priority_max(policy);
    if (min_prio == -1 || max_prio == -1) {
        return -InvalidStatus;
    }

    if (max_prio - min_prio <= 2) {
        return -InvalidStatus;
    }

    sched_param param;
    const int top_prio = max_prio - 1;
    const int low_prio = min_prio + 1;
    switch (priority) {
        case kLowPriority:
        param.sched_priority = low_prio;
        break;
        case kNormalPriority:
        // The -1 ensures that the kHighPriority is always greater or equal to
        // kNormalPriority.
        param.sched_priority = (low_prio + top_prio - 1) / 2;
        break;
        case kHighPriority:
        param.sched_priority = std::max(top_prio - 2, low_prio);
        break;
        case kHighestPriority:
        param.sched_priority = std::max(top_prio - 1, low_prio);
        break;
        case kRealtimePriority:
        param.sched_priority = top_prio;
        break;
    }

    if(pthread_setschedparam(mPthread, policy, &param) != 0) {
        return -InvalidStatus;
    }

    return 0;
}

int _Thread::setSchedPolicy(int policy) {
    if(!isRunning()) {
        return -InvalidStatus;
    }

    if(pthread_attr_setschedpolicy(&mThreadAttr, policy)!=0) {
        return -1;
    }

    return 0;
}

int _Thread::getSchedPolicy() {
    int policy = SchedOther;
    if(pthread_attr_getschedpolicy(&mThreadAttr, &policy) != 0) {
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

bool _Thread::isRunning() {
    AutoLock l(mStatusMutex);
    return mStatus == Running;
}

}
