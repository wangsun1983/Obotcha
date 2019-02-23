#ifndef __SCHEDULE_SERVICE_H__
#define __SCHEDULE_SERVICE_H__

#include <vector>

#include "Object.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "ArrayList.hpp"
#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "ExecutorService.hpp"

using namespace std;

DECLARE_SIMPLE_CLASS(TimeTask) {
public:
    long int millseconds;
    Runnable mRunnable;

    _TimeTask(Runnable runnable,long int interval);
};

DECLARE_SIMPLE_CLASS(TimeThread) EXTENDS(Thread) {

public:
    _TimeThread();

    void onUpdate();

    void addTask(TimeTask v);

    void run();

private:
    ArrayList<TimeTask> mDatas;

    ExecutorService mExecutorService;
    
    Mutex mDataLock;

    Mutex mCondLock;
    
    Condition mCond;
};

DECLARE_SIMPLE_CLASS(ScheduleService) {

public:

	_ScheduleService(int size);

	_ScheduleService();

    int execute(Runnable runnable,long millseconds);

    void shutdown();

    //wait for all the task complete.
    void awaitTermination();

    void awaitTermination(long millseconds);

    ~_ScheduleService();

private:
    ConcurrentQueue<Runnable> mPool;

    TimeThread  mTimeThread;

    bool isShutDown;

    bool isDynamic;

    void init(int size,bool isDyn);
};

#endif