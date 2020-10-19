#ifndef __OBOTCHA_THREAD_H__
#define __OBOTCHA_THREAD_H__

#include <pthread.h>
#include <map>
#include <atomic>
#include <cstdint>
#include <linux/sched.h>

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "BlockingQueue.hpp"
#include "String.hpp"
#include "ThreadLocal.hpp"
#include "Uint64.hpp"
#include "Atomic.hpp"

namespace obotcha {

class _Thread;

DECLARE_SIMPLE_CLASS(Thread) {

public:

    friend void cleanup(void *th);

    friend void doThreadExit(_Thread *thread);

    _Thread(String name,Runnable run);

	_Thread(Runnable run);

    _Thread();

	int start();
	
	void join();

    int join(long millseconds);

    int getStatus();

    virtual void run();

    virtual void quit();

    virtual void onComplete();

    int setPriority(int priority);

    int getPriority();

    int setSchedPolicy(int);

    int getSchedPolicy();

    pthread_t getThreadId();

    String getName();

    int setName(String name);

    Runnable getRunnable();

    void detach();

    virtual void onInterrupt();

    static void interruptCheck();
    
    static void yield();

    static void msleep(unsigned long);

    static void setThreadPriority(int priority);

    static int getThreadPriority();

    static int setThreadSchedPolicy(int policy);

    static int getThreadSchedPolicy();

    const static int LowPriority = 1;
    const static int NormalPriority = 2;
    const static int HighPriority = 3;
    const static int HighestPriority = 4;
    const static int RealtimePriority = 5;

    const static int SchedOther = SCHED_NORMAL; //SCHED_NORMAL 0
    const static int SchedFifo = SCHED_FIFO;  //SCHED_FIFO 1
    const static int SchedRr = SCHED_RR; //SCHED_RR 2

    const static int NotStart = 1;
    const static int Idle = 2;
    const static int Running = 3;
    const static int Complete = 5;
    const static int ErrorStatus = 6;

    ~_Thread();

protected:
   pthread_t mPthread;
   
private:

    static void* localRun(void *th);
    
    bool isRunning();
    
    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    String mName;
    
    Mutex mStatusMutex;

    int mStatus;

    Atomic<int> bootFlag;

    Mutex mJoinMutex;

    Condition mJoinDondtion;
};

}
#endif