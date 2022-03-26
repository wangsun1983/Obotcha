#ifndef __OBOTCHA_THREAD_H__
#define __OBOTCHA_THREAD_H__

#include <atomic>
#include <cstdint>
#include <linux/sched.h>
#include <map>
#include <pthread.h>
#include <thread>

#include "AtomicInteger.hpp"
#include "Condition.hpp"
#include "InterruptedException.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "ThreadLocal.hpp"

namespace obotcha {

class _Thread;

DECLARE_CLASS(Thread) {

  public:
    // friend void doThreadExit(sp<Thread> thread);
    _Thread();

    template <typename X> _Thread(sp<X> run) { threadInit(nullptr, run); }

    // We should not use C++ reference in Lambda function.
    // The count of pointer will not be increased if we pass
    // param by reference .
    template <class Function, class... Args>
    _Thread(Function && f, Args && ... args) : _Thread() {
        mRunnable = createLambdaRunnable(f, args...);
    }

    int start();

    int join(long millseconds = 0);

    int getStatus();

    virtual void run();

    virtual void onComplete();

    int setPriority(int priority);

    int getPriority();

    int setSchedPolicy(int);

    int getSchedPolicy();

    pthread_t getThreadId();

    String getName();

    int setName(String name);

    Runnable getRunnable();

    int detach();

    void interrupt();

    static void yield();

    //static void msleep(unsigned long = 0);
    static void sleep(unsigned long = 0);

    //static void interruptableSleep(unsigned long = 0);

    static void setThreadPriority(int priority);

    static int getThreadPriority();

    static int setThreadSchedPolicy(int policy);

    static int getThreadSchedPolicy();

    static Thread current();

    enum ThreadPriority {
        Low = 1,
        Normal,
        High,
        Highest,
        Realtime,
        MaxPriority
    };

    enum SchedType {
        Other = SCHED_NORMAL, // SCHED_NORMAL 0
        Fifo = SCHED_FIFO,    // SCHED_FIFO 1
        RR = SCHED_RR,        // SCHED_RR 2
    };

    enum ThreadStatus {
        NotStart = 1,
        Idle,
        WaitingStart, // for lambda
        Running,
        Interrupting,
        Complete,
        Error,
    };

    ~_Thread();

  protected:
    pthread_t mPthread;

  private:
    static void *localRun(void *th);
    static void doThreadExit(_Thread *);

    bool isRunning();

    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    String mName;

    mutable volatile int mStatus;

    static String DefaultThreadName;

    Condition mSleepCondition;

    Mutex mMutex;

    Condition mJoinCondition;

    void _threadSleep(unsigned long millseconds);
    void _threadInit(String name, Runnable run);

    //save thread local to prevent pool being realsed before all thread exit!!
    ThreadLocal<Thread> mPoolObj; 
};

} // namespace obotcha
#endif