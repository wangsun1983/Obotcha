#ifndef __SCHEDULED_THREAD_POOL_EXECUTOR_HPP__
#define __SCHEDULED_THREAD_POOL_EXECUTOR_HPP__

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
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "ScheduledExecutorService.hpp"

using namespace std;

namespace obotcha {

DECLARE_SIMPLE_CLASS(ScheduledTaskWorker) IMPLEMENTS(Runnable){
public:
    _ScheduledTaskWorker(FutureTask);
    void run();

private:
    FutureTask mTask;
};


DECLARE_SIMPLE_CLASS(ScheduledThreadPoolTask) {
public:
    _ScheduledThreadPoolTask(FutureTask task,long int interval);

    long int millseconds;
    
    FutureTask task;    
};

DECLARE_SIMPLE_CLASS(ScheduledThreadPoolThread) EXTENDS(Thread) {

public:
    friend class _ScheduledThreadPoolExecutor;

    _ScheduledThreadPoolThread();

    void onUpdate();

    void addTask(ScheduledThreadPoolTask v);

    void run();

    void stop();

    void forceStop();

    void waitStop(long timeout);


private:
    ArrayList<ScheduledThreadPoolTask> mDatas;

    ThreadPoolExecutor mExecutorService;
    
    Mutex mDataLock;

    Condition mDataCond;

    Mutex mTimeLock;
    
    Condition mTimeCond;

    Mutex mTerminatedMutex;

    Condition mTerminatedCond;

    bool isStop;

    bool isTerminated;
};

DECLARE_SIMPLE_CLASS(ScheduledThreadPoolExecutor) IMPLEMENTS(ScheduledExecutorService) {

public:

	//_ScheduledThreadPoolExecutor(int size);

	_ScheduledThreadPoolExecutor();

    void shutdown();

    void shutdownNow();

    void execute(Runnable command);

    bool awaitTermination(long timeout);

    bool isShutdown();

    bool isTerminated();

    Future submit(Runnable task);

    Future schedule(Runnable command,long delay);

    Future scheduleAtFixedRate(Runnable command,
                                long initialDelay,
                                long period);

    Future scheduleWithFixedDelay(Runnable command,
                                long initialDelay,
                                long delay);
private:
    //ConcurrentQueue<FutureTask> mPool;

    ScheduledThreadPoolThread  mTimeThread;

    bool mIsShutDown;

    //bool mIsTerminated;

    void init(int size,bool isDyn);
};

}
#endif