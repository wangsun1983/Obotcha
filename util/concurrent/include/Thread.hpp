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

DECLARE_SIMPLE_CLASS(RecycleThread) {
public:
    _RecycleThread();

    void start();

    void submit(sp<_Thread> t);

    void run();

private:
    Mutex mutex;

    Condition cond;

    pthread_attr_t mAttr;

    pthread_t mTid;

    BlockingQueue<sp<_Thread>> queue;

    bool isRunning;
};

DECLARE_SIMPLE_CLASS(Thread) {

public:
    friend class _RecycleThread;

    _Thread(String name,Runnable run);

	_Thread(Runnable run);

    _Thread();

	void start();
	
	void join();

    void join(long millseconds);

    int getStatus();

    virtual void run();

    void exit();

    void setPriority(ThreadPriority priority);

    int getPriority();

    bool setSchedPolicy(int);

    int getSchedPolicy();

    String getName();

    void setName(String name);

    Runnable getRunnable();

    virtual void onInterrupt();

    static void yield();

    static void msleep(unsigned long);

    static RecycleThread getRecyleThread();
        
    static void setThreadPriority(ThreadPriority priority);

    static int getThreadPriority();

    static bool setThreadSchedPolicy(int);

    static int getThreadSchedPolicy();

    ~_Thread();

private:

    int threadPrio2SchePrio(int threadprio);

    int SchePrio2threadPrio(int secheprio);

    int updateThreadPrioTable();

    int mPrioTable[ThreadPriorityMax];

    static RecycleThread mRecyle;

    static ThreadLocal<sp<_Thread>> mLocalThreadLocal;

    static void* localRun(void *th);

    static void removeThread(sp<_Thread>);

    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    pthread_t mPthread;

    int mPolicy;

    String mName;
};

}
#endif