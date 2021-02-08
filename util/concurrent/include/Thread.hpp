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

namespace obotcha {

class _Thread;

DECLARE_SIMPLE_CLASS(Thread) {

public:

    friend void cleanup(void *th);

    friend void doThreadExit(_Thread *thread);
    _Thread();
    
    template<typename X>
	_Thread(sp<X> run) {
        threadInit(nullptr,run);
    }

    template< class Function, class... Args >
    _Thread( Function&& f, Args&&... args ):_Thread() {
        pthread_barrier_init(&mLamdaBarrier,NULL, 2);
        mLambdaThread = new std::thread([this,&f,&args...] {
            lambdaEnter(this);
            pthread_barrier_wait(&mLamdaBarrier);
            mStatus->set(st(Thread)::Running);
            f(std::forward<Args>(args)...);
            lambdaEnter(this);
        });
        while(mStatus->get() == NotStart){pthread_yield();}
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

    enum ThreadPriority {
        LowPriority = 1,
        NormalPriority,
        HighPriority,
        HighestPriority,
        RealtimePriority,
        MaxPriority
    };

    enum SchedType {
        SchedOther = SCHED_NORMAL, //SCHED_NORMAL 0
        SchedFifo = SCHED_FIFO,  //SCHED_FIFO 1
        SchedRr = SCHED_RR, //SCHED_RR 2
    };

    enum ThreadStatus {
        NotStart = 1,
        Idle,
        WaitingStart, //for lambda
        Running,
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
    
    AtomicInteger mStatus;
    
    static String DefaultThreadName;

    Mutex mSleepMutex;

    Condition mSleepCondition;

    Mutex mJoinMutex;

    Condition mJoinCondition;

    pthread_barrier_t mLamdaBarrier;

    void threadSleep(unsigned long millseconds);
    void threadInit(String name,Runnable run);

    void lambdaEnter(_Thread *);
    void lambdaQuit(_Thread *);

    std::thread *mLambdaThread;
};

}
#endif