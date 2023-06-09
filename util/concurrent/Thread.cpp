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
#include "AtomicInteger.hpp"
#include "Inspect.hpp"

namespace obotcha {

static ThreadLocal<Thread> mThreads = createThreadLocal<Thread>();
static AtomicInteger threadCount = createAtomicInteger(0);
String _Thread::DefaultThreadName = createString("thread_");

void _Thread::doThreadExit(_Thread *thread) {
    Synchronized(thread->mMutex) {
        thread->mRunnable = nullptr;
        thread->mStatus = st(Thread)::Complete;
        thread->mJoinCondition->notifyAll();
    }
    pthread_detach(thread->getThreadId());
    mThreads->remove(thread->getThreadId());
}

//------------Thread---------------//
void *_Thread::localRun(void *th) {
    _Thread *thread = static_cast<_Thread *>(th);
    mThreads->set(thread->getThreadId(), AutoClone(thread));
    pthread_setname_np(thread->mPthread, thread->mName->toChars());
    Synchronized(thread->mMutex) {
        thread->mStatus = st(Thread)::Running;
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
    Inspect(!isRunning(),-1);
    mName = name;
    return -pthread_setname_np(mPthread, name->toChars());
}

void _Thread::_threadInit(String name, Runnable run) {
    mName =
        (name == nullptr)
            ? DefaultThreadName->append(createString(threadCount->addAndGet(1)))
            : name;

    mRunnable = run;
    mStatus = NotStart;
    mMutex = createMutex();
    mSleepCondition = createCondition();
    mJoinCondition = createCondition();
    mPoolRef = mThreads;
}

String _Thread::getName() { 
    return mName; 
}

_Thread::~_Thread() {
    // do nothing
}

Runnable _Thread::getRunnable() { 
    return mRunnable; 
}

void _Thread::run() {
    // child thread can overwrite it.
}

int _Thread::detach() {
    Inspect(!isRunning(),0);
    return -pthread_detach(getThreadId());
}

int _Thread::start() {
    Synchronized(mMutex) {
        Inspect(mStatus != NotStart,-EALREADY);
        mStatus = Idle;
    }

    pthread_attr_init(&mThreadAttr);
    if(pthread_create(&mPthread, &mThreadAttr, localRun, this) != 0) {
        mStatus = Error;
        return -errno;
    }

    while (getStatus() == Idle) {
        yield();
    }

    return 0;
}

int _Thread::join(long timeInterval) {
    while (getStatus() == Idle) {
        yield();
    }

    AutoLock l(mMutex);
    if (mStatus == Running || mStatus == Interrupting) {
        return mJoinCondition->wait(mMutex, timeInterval);
    }
    return -EALREADY;
}

int _Thread::getStatus() {
    AutoLock l(mMutex);
    return mStatus;
}

void _Thread::onComplete() {
    // Do nothing
}

int _Thread::getPriority() {
    Inspect(!isRunning(),-1);

    int policy = getSchedPolicy();
    Inspect(policy == SCHED_NORMAL,-EOPNOTSUPP);

    const int min_prio = sched_get_priority_min(policy);
    const int max_prio = sched_get_priority_max(policy);

    Inspect(min_prio == -1 || max_prio == -1 || max_prio - min_prio <= 2,-1);

    sched_param param;
    int rc = pthread_attr_getschedparam(&mThreadAttr, &param);
    if (rc != 0) {
        return -rc;
    }

    const int top_prio = max_prio - 1;
    const int low_prio = min_prio + 1;
    if (param.sched_priority == low_prio) {
        return Low;
    } else if (param.sched_priority == (low_prio + top_prio - 1) / 2) {
        return Normal;
    } else if (param.sched_priority == std::max(top_prio - 2, low_prio)) {
        return High;
    } else if (param.sched_priority == std::max(top_prio - 1, low_prio)) {
        return Highest;
    } else if (param.sched_priority == top_prio) {
        return Realtime;
    }

    return -1;
}

int _Thread::SetPriority(int priority) {
    auto current = st(Thread)::current();
    return current->setPriority(priority);
}

int _Thread::setPriority(int priority) {
    Inspect(!isRunning(),-1);

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
    case Low:
        param.sched_priority = low_prio;
        break;
    case Normal:
        // The -1 ensures that the kHighPriority is always greater or equal to
        // kNormalPriority.
        param.sched_priority = (low_prio + top_prio - 1) / 2;
        break;
    case High:
        param.sched_priority = std::max(top_prio - 2, low_prio);
        break;
    case Highest:
        param.sched_priority = std::max(top_prio - 1, low_prio);
        break;
    case Realtime:
        param.sched_priority = top_prio;
        break;
    }
    
    return pthread_setschedparam(mPthread, policy, &param);
}

int _Thread::setSchedPolicy(int policy) {
    Inspect(!isRunning(),-1);
    return pthread_attr_setschedpolicy(&mThreadAttr, policy);
}


int _Thread::getSchedPolicy() {
    Inspect(!isRunning(),-1);

    int policy = Other;
    if (pthread_attr_getschedpolicy(&mThreadAttr, &policy) != 0) {
        return -1;
    }
    return policy;
}

pthread_t _Thread::getThreadId() { 
    return mPthread; 
}

void _Thread::yield() { 
    //Based on the documentation the pthread_yield function is deprecated. https://lwn.net/Articles/864920/
    //The function pthread_yield has been deprecated; programs should use
    //the equivalent standard function sched_yield instead.
    //pthread_yield();->use  -D_GNU_SOURCE
    sched_yield(); 
}

void _Thread::sleep(unsigned long millseconds) {
    Thread thread = mThreads->get();
    if(thread == nullptr) {
        usleep(1000 * millseconds);
    } else {
        thread->_threadSleep(millseconds);
    }
}

Thread _Thread::current() { 
    return mThreads->get(); 
}

bool _Thread::isRunning() {
    AutoLock l(mMutex);
    return mStatus == Running;
}

void _Thread::_threadSleep(unsigned long interval) {
    AutoLock l(mMutex);
    Panic(mStatus != Running,IllegalStateException,"thread status is illegal!!!");
    if(mSleepCondition->wait(mMutex, interval) == 0) {
        Trigger(InterruptedException, "thread interrupt while sleeping!!!");
    }
}

void _Thread::interrupt() {
    AutoLock l(mMutex);
    if (mStatus == Running) {
        mStatus = Interrupting;
        mSleepCondition->notifyAll();
        mJoinCondition->notifyAll();
        if(mRunnable != nullptr) {
            mRunnable->onInterrupt();
        }
    }
}

} // namespace obotcha
