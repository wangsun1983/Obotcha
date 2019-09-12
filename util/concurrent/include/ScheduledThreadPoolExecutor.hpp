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
#include "ThreadCachedPoolExecutor.hpp"

using namespace std;

enum ScheduledTaskType {
    ScheduletTaskNormal,
    ScheduletTaskFixRate,
    ScheduletTaskFixedDelay
};

namespace obotcha { 

class _ScheduledThreadPoolTask;
class _ScheduledThreadPoolThread;
class _ScheduledThreadPoolExecutor;

DECLARE_SIMPLE_CLASS(ScheduledTaskWorker) IMPLEMENTS(Runnable){
public:
    _ScheduledTaskWorker(sp<_ScheduledThreadPoolTask>);

    void run();

private:
    sp<_ScheduledThreadPoolTask> mTask;

    sp<_ScheduledThreadPoolThread> mTimeThread;
};


DECLARE_SIMPLE_CLASS(ScheduledThreadPoolTask) {
public:
    friend class _ScheduledTaskWorker;
    friend class _ScheduledThreadPoolThread;
    friend class _ScheduledThreadPoolExecutor;

    _ScheduledThreadPoolTask(FutureTask task,long int interval);

    _ScheduledThreadPoolTask(FutureTask t,
                             long int interval,
                             int type,
                             long int repeatDelay,
                             sp<_ScheduledThreadPoolThread> timethread);

private:
    long int mNextTime;
    
    FutureTask task;

    int mScheduleTaskType;

    long int repeatDelay;

    sp<_ScheduledThreadPoolThread> mTimeThread;
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

    void waitStop(long);

    void onInterrupt();


private:
    ArrayList<ScheduledThreadPoolTask> mDatas;

    ThreadCachedPoolExecutor cachedExecutor;

    ThreadPoolExecutor mExecutorService;
    
    Mutex mDataLock;

    Condition mDataCond;

    Mutex mTimeLock;
    
    Condition mTimeCond;

    Mutex mTerminatedMutex;

    Condition mTerminatedCond;

    ScheduledThreadPoolTask mCurrentTask;

    bool isStop;

    bool isTerminated;
};

DECLARE_SIMPLE_CLASS(ScheduledThreadPoolExecutor) IMPLEMENTS(ScheduledExecutorService) {

public:

	_ScheduledThreadPoolExecutor();

    int shutdown();

    int shutdownNow();

    int execute(Runnable command);

    int awaitTermination(long timeout);

    bool isShutdown();

    bool isTerminated();

    Future submit(Runnable task);

    Future schedule(Runnable command,long delay);

    int getThreadsNum();

    Future scheduleAtFixedRate(Runnable command,
                                long initialDelay,
                                long period);

    Future scheduleWithFixedDelay(Runnable command,
                                long initialDelay,
                                long delay);

    ~_ScheduledThreadPoolExecutor();
    
private:
    ScheduledThreadPoolThread  mTimeThread;

    bool mIsShutDown;

    bool mIsTerminated;

    Mutex mProtectMutex;

    void init(int size,bool isDyn);
};

}
#endif