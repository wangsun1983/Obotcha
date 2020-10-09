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
#include "Thread.hpp"
#include "ArrayList.hpp"
#include "FutureTask.hpp"

using namespace std;

enum ScheduledTaskType {
    ScheduletTaskNormal = 0, //normal schedule task
    ScheduletTaskFixRate, //loop time record from task start
    ScheduletTaskFixedDelay //loop time record from task complete
};

namespace obotcha { 

class _WaitingTask;
class _ScheduledThreadPoolThread;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(WaitingTask) EXTENDS(FutureTask){
public:
    friend class _ScheduledTaskWorker;
    friend class _ScheduledThreadPoolThread;
    friend class _ThreadScheduledPoolExecutor;

    _WaitingTask(int,Runnable);
    _WaitingTask(int,Runnable,FutureTaskStatusListener);

    void init(long int interval,int type,int repeat);
    void setExecutor(_ThreadScheduledPoolExecutor *);

    //~_WaitingTask();

    void onComplete();
    
    sp<_WaitingTask> parent;
    sp<_WaitingTask> left; //smaller or equal 
    sp<_WaitingTask> right; //larger                 
private:
    long int mNextTime;
    int mScheduleTaskType;
    long int repeatDelay;
    _ThreadScheduledPoolExecutor *mExecutor;
};

DECLARE_SIMPLE_CLASS(ThreadScheduledPoolExecutor) IMPLEMENTS(ScheduledExecutorService)
                                                  IMPLEMENTS(FutureTaskStatusListener)
                                                  IMPLEMENTS(Thread) {

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

    Future scheduleAtFixedRate(Runnable r,
                                long initialDelay,
                                long period);

    Future scheduleWithFixedDelay(Runnable r,
                                long initialDelay,
                                long delay);

    int getThreadsNum();

    void addWaitingTask(WaitingTask);
    WaitingTask getWaitingTask();

    void onCancel(FutureTask);                        

private:
    //ScheduledThreadPoolThread  mTimeThread;
    void run();

    WaitingTask newFixedRateWaitingTask(Runnable command,
                                long initialDelay,
                                long period);

    WaitingTask newFixedDelayWaitingTask(Runnable command,
                                long initialDelay,
                                long delay);

    ThreadCachedPoolExecutor mCachedExecutor;

    bool mIsShutDown;

    bool mIsTerminated;

    Mutex mStatusMutex;

    void init(int size,bool isDyn);

    Mutex mTaskMutex;
    WaitingTask mRoot;
    Condition mTaskWaitCond; 
};

}
#endif