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
#include "HashMap.hpp"

using namespace std;

enum ScheduledTaskType {
    ScheduletTaskNormal, //normal schedule task
    ScheduletTaskFixRate, //loop time record from task start
    ScheduletTaskFixedDelay //loop time record from task complete
};

namespace obotcha { 

class _ScheduledThreadPoolTask;
class _ScheduledThreadPoolThread;
class _ScheduledThreadPoolExecutor;

DECLARE_SIMPLE_CLASS(ScheduledTaskWorker) IMPLEMENTS(Runnable){
public:
    friend class _ScheduledThreadPoolThread;

    _ScheduledTaskWorker(sp<_ScheduledThreadPoolTask>,sp<_ScheduledThreadPoolThread>);
    
    ~_ScheduledTaskWorker();

    void run();

    void onInterrupt();

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
                             long int initialdelay,
                             int type,
                             long int repeatDelay,
                             sp<_ScheduledThreadPoolThread> timethread);                             

    ~_ScheduledThreadPoolTask();                     
                   

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

    _ScheduledThreadPoolThread(ThreadCachedPoolExecutor m);

    ~_ScheduledThreadPoolThread();

    void onUpdate();

    void addTask(ScheduledThreadPoolTask v);

    void run();

    void stop();

    void waitForTerminate();

    void waitForTerminate(long);

    void onInterrupt();

    void onTaskFinished(Runnable);

    void stopTask(FutureTask);

private:
    ArrayList<ScheduledThreadPoolTask> mDatas;

    ThreadCachedPoolExecutor cachedExecutor;
    
    Mutex mFuturesMutex;
    HashMap<Runnable,Future> mFutures;

    //ThreadPoolExecutor mExecutorService;
    
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

DECLARE_SIMPLE_CLASS(ScheduledThreadPoolExecutor) IMPLEMENTS(ScheduledExecutorService)
                                                  IMPLEMENTS(FutureTaskStatusListener) {

public:

	_ScheduledThreadPoolExecutor();

    ~_ScheduledThreadPoolExecutor();

    int shutdown();

    int execute(Runnable command);

    void awaitTermination();

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

    void onCancel(FutureTask);                        

private:
    ScheduledThreadPoolThread  mTimeThread;

    ThreadCachedPoolExecutor mCachedExecutor;

    bool mIsShutDown;

    bool mIsTerminated;

    Mutex mProtectMutex;

    void init(int size,bool isDyn);
};

}
#endif