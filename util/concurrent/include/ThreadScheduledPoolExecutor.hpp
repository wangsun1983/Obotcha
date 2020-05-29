#ifndef __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_SCHEDULED_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "ArrayList.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
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

class _WaitingTask;
class _ScheduledThreadPoolThread;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(ScheduledTaskWorker) IMPLEMENTS(Runnable){
public:
    friend class _ScheduledThreadPoolThread;

    _ScheduledTaskWorker(sp<_WaitingTask>,sp<_ScheduledThreadPoolThread>);
    
    ~_ScheduledTaskWorker();

    void run();

    void onInterrupt();

private:
    sp<_WaitingTask> mTask;

    sp<_ScheduledThreadPoolThread> mTimeThread;
};


DECLARE_SIMPLE_CLASS(WaitingTask) {
public:
    friend class _ScheduledTaskWorker;
    friend class _ScheduledThreadPoolThread;
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(FutureTask task,long int interval);

    _WaitingTask(FutureTask t,
                             long int initialdelay,
                             int type,
                             long int repeatDelay);                             

    ~_WaitingTask();                     
                   

private:
    long int mNextTime;
    
    FutureTask task;

    int mScheduleTaskType;

    long int repeatDelay;

    sp<_ScheduledThreadPoolThread> mTimeThread;
};

DECLARE_SIMPLE_CLASS(ScheduledThreadPoolThread) EXTENDS(Thread) {

public:
    friend class _ThreadScheduledPoolExecutor;

    _ScheduledThreadPoolThread(ThreadCachedPoolExecutor m);

    ~_ScheduledThreadPoolThread();

    void onUpdate();

    void addTask(WaitingTask v);

    void run();

    void stop();

    void waitForTerminate();

    void waitForTerminate(long);

    void onInterrupt();

    void onTaskFinished(Runnable);

    void stopTask(FutureTask);

private:
    //wangsl
    std::vector<long> mWaitingTimes;
    HashMap<long,ArrayList<WaitingTask>> mWaitingTasks;
    //ArrayList<WaitingTask> mWaitingTasks;
    //wangsl

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

    Mutex mTaskMutex;

    ArrayList<WaitingTask> mCurrentTask;
    long mCurrentTaskTime;

    bool isStop;

    bool isTerminated;
    //TODO
    //std::_Rb_tree_node<WaitingTask> node;
};

DECLARE_SIMPLE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(ScheduledExecutorService)
                                                  IMPLEMENTS(FutureTaskStatusListener) {

public:

	_ThreadScheduledPoolExecutor();

    ~_ThreadScheduledPoolExecutor();

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