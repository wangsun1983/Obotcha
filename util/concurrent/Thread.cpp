/**
 * @file Thread.hpp
 * @brief A thread is a thread of execution in a program.
 *        Every thread has a priority. Threads with higher priority are
 *        executed in preference to threads with lower priority. Each thread
 *        may or may not also be marked as a daemon.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

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

static const ThreadLocal<Thread> gThreads = ThreadLocal<Thread>::New();
static const AtomicInteger gThreadCount = AtomicInteger::New(0);
String _Thread::DefaultThreadName = String::New("thread_");

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
            ? DefaultThreadName->append(String::New(gThreadCount->addAndGet(1)))
            : name;

    mRunnable = run;
    mStatus = st(Concurrent)::Status::NotStart;
    mMutex = Mutex::New();
    mSleepCondition = Condition::New();
    mJoinCondition = Condition::New();
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

/**
 * Start a thread.
 *
 * This method first checks the thread's status to ensure it has not been started yet. If the thread is already started,
 * it returns -1. Then, it sets the thread's status to idle, indicating that the thread is ready but not running yet.
 * Next, it initializes the thread attributes and attempts to create a new thread. If the thread creation fails,
 * it sets the thread's status to error and returns the corresponding error code.
 * Finally, it waits for the thread to start running by checking the thread's status in a loop until it is no longer idle.
 *
 * @return 0 if the thread starts successfully; otherwise, the corresponding error code (negative).
 */
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

/**
 * Waits for the thread to finish execution.
 *
 * This function attempts to wait for the current thread to complete its execution.
 * If the thread is currently idle, it waits in a loop until the thread is no longer idle.
 * Once the thread starts running or is interrupted, it uses a condition variable to wait
 * for the thread to finish or be interrupted.
 *
 * @param timeInterval Specifies the time interval(ms) to wait,if timeInterval is st(Concurrent)::kWaitForEver(0), it waits indefinitely.
 * @return Returns 0 if the thread successfully joins; returns -EALREADY if the thread has already finished or been interrupted.
 */
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

/**
 * @brief Puts the current thread to sleep for a specified duration.
 * 
 * This function causes the current thread to sleep for a given number of milliseconds.
 * It first attempts to retrieve the current thread object from the global thread manager.
 * If it fails to retrieve the thread object or if the thread object is null,
 * it calls the system-level sleep function. Otherwise, it calls the thread's own sleep method.
 * 
 * @param millseconds The duration to sleep in milliseconds.
 * @note this sleep can be interrupted by other threads(use function:interrupt()).
 */
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
