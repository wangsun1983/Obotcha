#ifndef __OBOTCHA_THREAD_H__
#define __OBOTCHA_THREAD_H__

#include <pthread.h>
#include <map>
#include <atomic>
#include <cstdint>
#include <linux/sched.h>
#include <thread>

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ThreadLocal.hpp"
#include "AtomicInteger.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

class _Thread;

DECLARE_SIMPLE_CLASS(Thread) {

public:
    friend class _Condition;

    friend void doThreadExit(_Thread *thread);
    _Thread();
    
    template<typename X>
	_Thread(sp<X> run) {
        threadInit(nullptr,run);
    }

    template< class Function, class... Args >
    _Thread( Function&& f, Args&&... args ):_Thread() {
        mRunnable = createLambdaRunnable(f,args...);
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

    static void sleep(unsigned long = 0);

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
        Other = SCHED_NORMAL, //SCHED_NORMAL 0
        Fifo = SCHED_FIFO,  //SCHED_FIFO 1
        RR = SCHED_RR, //SCHED_RR 2
    };

    enum ThreadStatus {
        NotStart = 1,
        Idle,
        WaitingStart, //for lambda
        Running,
        Interrupting,
        Complete,
        Error,
    };

    ~_Thread();

protected:
    pthread_t mPthread;
   
private:

    static void* localRun(void *th);
    
    bool isRunning();
    
    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    String mName;
    
    mutable volatile int mStatus;
    
    static String DefaultThreadName;

    Condition mSleepCondition;

    Mutex mMutex;

    Condition mJoinCondition;

    void threadSleep(unsigned long millseconds);
    void threadInit(String name,Runnable run);
};

}
#endif