#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <map>
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
#include "AtomicInteger.hpp"

using namespace std;

namespace obotcha {

class _Thread;

enum ThreadPriority {
    ThreadLowestPriority = 0,
    ThreadLowPriority,
    ThreadNormalPriority,
    ThreadHighPriority,
    ThreadHighestPriority,
    ThreadPriorityMax,
};

enum ThreadStatus {
    ThreadNotExist = 0,
    ThreadNotStart,
    ThreadIdle,
    ThreadRunning,
    ThreadWaitExit,
    ThreadComplete
};

enum ThreadSchedPolicy {
    ThreadSchedOTHER = SCHED_NORMAL, //SCHED_NORMAL 0
    ThreadSchedFIFO = SCHED_FIFO,  //SCHED_FIFO 1
    ThreadSchedRR = SCHED_RR,    //SCHED_RR 2
};

DECLARE_SIMPLE_CLASS(ReleaseThread) {

public:
    _ReleaseThread();

    ~_ReleaseThread();

    void sendRelease(Uint64 t);

    void start();

    void stop();

    void run();
    
private:
    ArrayList<Uint64> mThreadPids;
    
    Mutex mutex;

    Condition cond;

    pthread_attr_t mAttr;

    pthread_t mTid;

    AtomicInteger mStartBarrier;
};

DECLARE_SIMPLE_CLASS(KeepAliveThread) {
public:
    _KeepAliveThread();

    void start();

    void drop(pthread_t t);

    void run();

    ~_KeepAliveThread();

    void save(sp<_Thread>);

    sp<_Thread> getSavedThread();

private:
    Mutex mutex;

    Condition cond;

    pthread_attr_t mAttr;

    pthread_t mTid;

    BlockingQueue<Uint64> queue;

    ThreadLocal<sp<_Thread>> mThreadLocal;

    bool isRunning;
    
    //Mutex mDestroyMutex;

    AtomicInteger mStartBarrier;

    sp<_ReleaseThread> mReleaseThread;
};

DECLARE_SIMPLE_CLASS(Thread) {

public:
    friend class _KeepAliveThread;
    
    friend void cleanup(void *th);

    _Thread(String name,Runnable run);

	_Thread(Runnable run);

    _Thread();

	int start();
	
	void join();

    void join(long millseconds);

    int getStatus();

    virtual void run();

    virtual void quit();

    int setPriority(ThreadPriority priority);

    int getPriority();

    int setSchedPolicy(ThreadSchedPolicy);

    int getSchedPolicy();

    String getName();

    //int getThreadStatus();

    //void setThreadStatus(int);

    int setName(String name);

    Runnable getRunnable();

    virtual void onInterrupt();

    static void interruptCheck();
    
    static void yield();

    static void msleep(unsigned long);

    static KeepAliveThread getKeepAliveThread();
        
    static void setThreadPriority(ThreadPriority priority);

    static int getThreadPriority();

    static int setThreadSchedPolicy(ThreadSchedPolicy policy);

    static int getThreadSchedPolicy();

    ~_Thread();

protected:
   pthread_t mPthread;
   
private:
    void initPolicyAndPriority();

    int threadPrio2SchePrio(int threadprio);

    int SchePrio2threadPrio(int secheprio);

    int updateThreadPrioTable(int policy);

    //int mPrioTable[ThreadPriorityMax];

    static KeepAliveThread mKeepAliveThread;

    static HashMap<int,int *> mPriorityTable;

    static void* localRun(void *th);

    //static void cleanup(void *th);

    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    ThreadSchedPolicy mPolicy;

    ThreadPriority mPriority;

    String mName;

    int mStatus;

    //bool mIsWaitExit;

    AtomicInteger bootFlag;

    Mutex mProtectMutex;

    Mutex mJoinMutex;

    Condition mJoinDondtion;
};

}
#endif