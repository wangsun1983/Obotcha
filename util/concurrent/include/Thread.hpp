#ifndef __OBOTCHA_THREAD_H__
#define __OBOTCHA_THREAD_H__

#include <linux/sched.h>
#include <pthread.h>

#include "Object.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"
#include "String.hpp"
#include "ThreadLocal.hpp"
#include "Concurrent.hpp"

namespace obotcha {

class _Thread;

DECLARE_CLASS(Thread) {
  public:
    enum class Priority {
        Low = 1,
        Normal,
        High,
        Highest,
        Realtime,
        Error
    };

    enum SchedType {
        Other = SCHED_NORMAL, // SCHED_NORMAL 0
        Fifo = SCHED_FIFO,    // SCHED_FIFO 1
        RR = SCHED_RR,        // SCHED_RR 2
        Err = -1,
    };

    _Thread();

    template <typename X> 
    explicit _Thread(sp<X> run) { 
      _threadInit(nullptr, run); 
    }

    // We should not use C++ reference in Lambda function.
    // The count of pointer will not be increased if we pass
    // param by reference .
    template <class Function, class... Args>
    _Thread(Function f, Args... args) : _Thread() {
        mRunnable = createLambdaRunnable(f, args...);
    }

    int start();

    int join(long millseconds = 0);

    st(Concurrent)::Status getStatus() const;

    virtual void run();

    virtual void onComplete();

    int setPriority(st(Thread)::Priority);

    st(Thread)::Priority getPriority();

    int setSchedPolicy(SchedType);

    SchedType getSchedPolicy();

    pthread_t getThreadId() const;

    String getName();

    int setName(String name);

    Runnable getRunnable();

    int detach();

    void interrupt();

    static void Yield();

    static void Sleep(unsigned int = 0);

    static Thread Current();

    static int SetPriority(st(Thread)::Priority);

    ~_Thread() override = default;

  protected:
    pthread_t mPthread;

  private:
    static void *localRun(void *th);
    static void doThreadExit(_Thread *);

    bool isRunning();

    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    String mName;

    std::atomic<st(Concurrent)::Status> mStatus;

    static String DefaultThreadName;

    Condition mSleepCondition;

    Mutex mMutex;

    Condition mJoinCondition;

    void _threadSleep(unsigned long millseconds);
    void _threadInit(String name, Runnable run);

    //save thread local to prevent pool being realsed 
    //before all thread exit!!
    ThreadLocal<Thread> mPoolRef; 
};

} // namespace obotcha
#endif