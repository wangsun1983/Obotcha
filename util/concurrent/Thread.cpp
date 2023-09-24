#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "InterruptedException.hpp"
#include "IllegalStateException.hpp"
#include "Synchronized.hpp"
#include "AtomicNumber.hpp"
#include "Inspect.hpp"
#include "System.hpp"

namespace obotcha {

static const ThreadLocal<Thread> gThreads = createThreadLocal<Thread>();
static const AtomicInteger gThreadCount = createAtomicInteger(0);
String _Thread::DefaultThreadName = createString("thread_");

void _Thread::doThreadExit(_Thread *thread) {
    Synchronized(thread->mMutex) {
        thread->mRunnable = nullptr;
        thread->mStatus = st(Concurrent)::Status::Complete;
        thread->mJoinCondition->notifyAll();
    }
    pthread_detach(thread->getThreadId());
    gThreads->remove(thread->getThreadId());
}

//------------Thread---------------//
void *_Thread::localRun(void *th) {
    auto thread = static_cast<_Thread *>(th);
    gThreads->set(thread->getThreadId(), AutoClone(thread));
    pthread_setname_np(thread->mPthread, thread->mName->toChars());
    Synchronized(thread->mMutex) {
        thread->mStatus = st(Concurrent)::Status::Running;
    }

    (thread->mRunnable == nullptr) ? thread->run() : thread->mRunnable->run();
    thread->onComplete();
    doThreadExit(thread);
    return nullptr;
}

_Thread::_Thread() { 
    _threadInit(nullptr, nullptr); 
}

int _Thread::setName(String name) {
    Inspect(!isRunning(),-1)
    mName = name;
    return -pthread_setname_np(mPthread, name->toChars());
}

void _Thread::_threadInit(String name, Runnable run) {
    mName =
        (name == nullptr)
            ? DefaultThreadName->append(createString(gThreadCount->addAndGet(1)))
            : name;

    mRunnable = run;
    mStatus = st(Concurrent)::Status::NotStart;
    mMutex = createMutex();
    mSleepCondition = createCondition();
    mJoinCondition = createCondition();
    mPoolRef = gThreads;
}

String _Thread::getName() { 
    return mName; 
}

Runnable _Thread::getRunnable() { 
    return mRunnable; 
}

void _Thread::run() {
    // child thread can overwrite it.
}

int _Thread::detach() {
    Inspect(!isRunning(),0)
    return -pthread_detach(getThreadId());
}

int _Thread::start() {
    Synchronized(mMutex) {
        Inspect(mStatus != st(Concurrent)::Status::NotStart,-EALREADY)
        mStatus = st(Concurrent)::Status::Idle;
    }

    pthread_attr_init(&mThreadAttr);
    if(pthread_create(&mPthread, &mThreadAttr, localRun, this) != 0) {
        mStatus = st(Concurrent)::Status::Error;
        return -errno;
    }

    while (getStatus() == st(Concurrent)::Status::Idle) {
        Yield();
    }

    return 0;
}

int _Thread::join(long timeInterval) {
    while (getStatus() == st(Concurrent)::Status::Idle) {
        Yield();
    }

    AutoLock l(mMutex);
    if (mStatus == st(Concurrent)::Status::Running 
        || mStatus == st(Concurrent)::Status::Interrupt) {
        return mJoinCondition->wait(mMutex, timeInterval);
    }
    return -EALREADY;
}

st(Concurrent)::Status _Thread::getStatus() const {
    AutoLock l(mMutex);
    return mStatus;
}

void _Thread::onComplete() {
    // Do nothing
}

st(Thread)::Priority _Thread::getPriority() {
    Inspect(!isRunning(),st(Thread)::Priority::Error)

    int policy = getSchedPolicy();
    Inspect(policy == SCHED_NORMAL,st(Thread)::Priority::Error)

    const int min_prio = sched_get_priority_min(policy);
    const int max_prio = sched_get_priority_max(policy);

    Inspect(min_prio == -1 || max_prio == -1 || max_prio - min_prio <= 2,
            st(Thread)::Priority::Error)

    sched_param param;
    if (int rc = pthread_attr_getschedparam(&mThreadAttr, &param);
        rc != 0) {
        return st(Thread)::Priority::Error;
    }

    const int top_prio = max_prio - 1;
    const int low_prio = min_prio + 1;
    if (param.sched_priority == low_prio) {
        return st(Thread)::Priority::Low;
    } else if (param.sched_priority == (low_prio + top_prio - 1) / 2) {
        return st(Thread)::Priority::Normal;
    } else if (param.sched_priority == std::max(top_prio - 2, low_prio)) {
        return st(Thread)::Priority::High;
    } else if (param.sched_priority == std::max(top_prio - 1, low_prio)) {
        return st(Thread)::Priority::Highest;
    } else if (param.sched_priority == top_prio) {
        return st(Thread)::Priority::Realtime;
    }

    return st(Thread)::Priority::Error;
}

int _Thread::SetPriority(st(Thread)::Priority priority) {
    auto current = st(Thread)::Current();
    return current->setPriority(priority);
}

int _Thread::setPriority(st(Thread)::Priority priority) {
    Inspect(!isRunning(),-1)

    int policy = getSchedPolicy();
    if (policy == SCHED_NORMAL) {
        return -EOPNOTSUPP;
    }

    const int min_prio = sched_get_priority_min(policy);
    const int max_prio = sched_get_priority_max(policy);
    if (min_prio == -1 || max_prio == -1 ||max_prio - min_prio <= 2) {
        return -1;
    }

    sched_param param;
    const int top_prio = max_prio - 1;
    const int low_prio = min_prio + 1;
    switch (priority) {
        case st(Thread)::Priority::Low:
            param.sched_priority = low_prio;
            break;
        case st(Thread)::Priority::Normal:
            // The -1 ensures that the kHighPriority is always greater or equal to
            // kNormalPriority.
            param.sched_priority = (low_prio + top_prio - 1) / 2;
            break;
        case st(Thread)::Priority::High:
            param.sched_priority = std::max(top_prio - 2, low_prio);
            break;
        case st(Thread)::Priority::Highest:
            param.sched_priority = std::max(top_prio - 1, low_prio);
            break;
        case st(Thread)::Priority::Realtime:
            param.sched_priority = top_prio;
            break;
        case st(Thread)::Priority::Error:
            return -1;
    }
    
    return pthread_setschedparam(mPthread, policy, &param);
}

int _Thread::setSchedPolicy(_Thread::SchedType policy) {
    Inspect(!isRunning(),-1)
    return pthread_attr_setschedpolicy(&mThreadAttr, policy);
}

_Thread::SchedType _Thread::getSchedPolicy() {
    Inspect(!isRunning(),_Thread::SchedType::Err)

    int policy = 0;
    if (pthread_attr_getschedpolicy(&mThreadAttr, &policy) != 0) {
        return _Thread::SchedType::Err;
    }
    return static_cast<_Thread::SchedType>(policy);
}

pthread_t _Thread::getThreadId() const{ 
    return mPthread; 
}

void _Thread::Yield() { 
    //Based on the documentation the pthread_Yield function is deprecated. 
    //https://lwn.net/Articles/864920/
    //The function pthread_Yield has been deprecated; programs should use
    //the equivalent standard function sched_Yield instead.
    //pthread_Yield();->use  -D_GNU_SOURCE
    sched_yield(); 
}

void _Thread::Sleep(unsigned int millseconds) {
    Thread thread = gThreads->get();
    if(thread == nullptr) {
        st(System)::Sleep(millseconds);
    } else {
        thread->_threadSleep(millseconds);
    }
}

Thread _Thread::Current() { 
    return gThreads->get(); 
}

bool _Thread::isRunning() {
    AutoLock l(mMutex);
    return mStatus == st(Concurrent)::Status::Running;
}

void _Thread::_threadSleep(unsigned long interval) {
    AutoLock l(mMutex);
    Panic(mStatus != st(Concurrent)::Status::Running,IllegalStateException,"thread status is illegal!!!")
    if(mSleepCondition->wait(mMutex, interval) == 0) {
        Trigger(InterruptedException, "thread interrupt while sleeping!!!")
    }
}

void _Thread::interrupt() {
    AutoLock l(mMutex);
    if (mStatus == st(Concurrent)::Status::Running) {
        mStatus = st(Concurrent)::Status::Interrupt;
        mSleepCondition->notifyAll();
        mJoinCondition->notifyAll();
        if(mRunnable != nullptr) {
            mRunnable->onInterrupt();
        }
    }
}

} // namespace obotcha
