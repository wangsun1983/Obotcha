#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "BlockingQueue.hpp"
#include "String.hpp"

using namespace std;

namespace obotcha {

class _Thread;

enum ThreadPriority {
    IdlePriority,
    LowestPriority,
    LowPriority,
    NormalPriority,
    HighPriority,
    HighestPriority,
};

DECLARE_SIMPLE_CLASS(RecycleThread) {
public:
    _RecycleThread();

    void start();

    void submit(_Thread *t);

    void run();

private:
    Mutex mutex;

    Condition cond;

    pthread_attr_t mAttr;

    pthread_t mTid;

    BlockingQueue<_Thread *> queue;

    bool isRunning;
};

DECLARE_SIMPLE_CLASS(Thread) {

public:
    _Thread(String name,Runnable run);

	_Thread(Runnable run);

    _Thread();

	void start();
	
	void join();

    bool isFinished();

    bool isRunning();

    virtual void run();

    void exit();

    void setPriority(ThreadPriority priority);

    String getName();

    void setName(String name);

    Runnable getRunnable();

    virtual void onInterrupt();

    static void yield();

    //static void sleep(unsigned long);

    static void msleep(unsigned long);
    
    //static void usleep(unsigned long);

    static RecycleThread getRecyleThread();

    ~_Thread();

private:
    static RecycleThread mRecyle;

    Runnable mRunnable;

    pthread_attr_t mThreadAttr;

    pthread_t mPthread;

    String mName;
};

}
#endif