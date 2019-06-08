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
    ThreadNotExist,
    ThreadRunning,
};

enum ThreadSchedPolicy {
    ThreadSchedOTHER = SCHED_NORMAL, //SCHED_NORMAL 0
    ThreadSchedFIFO = SCHED_FIFO,  //SCHED_FIFO 1
    ThreadSchedRR = SCHED_RR,    //SCHED_RR 2
};

enum ThreadFailReason {
    ThreadFailUnknowPolicy = 200,
    ThreadFailNoPrioritySupport,
    
};

DECLARE_SIMPLE_CLASS(KeepAliveThread) {
public:
    _KeepAliveThread();

    void start();

    void drop(sp<_Thread> t);

    void run();

    ~_KeepAliveThread();

    void save(sp<_Thread>);

    sp<_Thread> getSavedThread();

private:
    Mutex mutex;

    Condition cond;

    pthread_attr_t mAttr;

    pthread_t mTid;

    BlockingQueue<sp<_Thread>> queue;

    ThreadLocal<sp<_Thread>> mThreadLocal;

    bool isRunning;
    
    //Mutex mDestroyMutex;

    int mDestroyBarrier;
};

DECLARE_SIMPLE_CLASS(Thread) {

public:
    friend class _KeepAliveThread;

    _Thread(String name,Runnable run);

	_Thread(Runnable run);

    _Thread();

	void start();
	
	void join();

    void join(long millseconds);

    int getStatus();

    virtual void run();

    void exit();

    int setPriority(ThreadPriority priority);

    int getPriority();

    int setSchedPolicy(ThreadSchedPolicy);

    int getSchedPolicy();

    String getName();

    void setName(String name);

    Runnable getRunnable();

    virtual void onInterrupt();

    static void yield();

    static void msleep(unsigned long);

    static KeepAliveThread getKeepAliveThread();
        
    static void setThreadPriority(ThreadPriority priority);

    static int getThreadPriority();

    static bool setThreadSchedPolicy(ThreadSchedPolicy policy);

    static int getThreadSchedPolicy();

    ~_Thread();

private:
    void initPolicyAndPriority();

    int threadPrio2SchePrio(int threadprio);

    int SchePrio2threadPrio(int secheprio);

    int updateThreadPrioTable(int policy);

    int mPrioTable[ThreadPriorityMax];

    static KeepAliveThread mKeepAliveThread;

    static void* localRun(void *th);

    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    pthread_t mPthread;

    ThreadSchedPolicy mPolicy;

    ThreadPriority mPriority;

    String mName;
};

}
#endif