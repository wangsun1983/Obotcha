#ifndef __THREAD_CACHED_POOL_EXECUTOR_HPP__
#define __THREAD_CACHED_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "AtomicInteger.hpp"

using namespace std;

namespace obotcha {

class _ThreadCachedPoolExecutor;
class _CacheThreadManager;

DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutorHandler) IMPLEMENTS(Thread) {

public:

    _ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask>,sp<_CacheThreadManager>,long timeout);
        
    bool isTerminated();

    void run();
    
    void stop();

    void doTask(FutureTask);

    void onInterrupt();

    //void onExecutorDestroy();

    bool shutdownTask(FutureTask task);

    ~_ThreadCachedPoolExecutorHandler();

private:
    int state;

    //-------------------------
    FutureTask mCurrentTask;

    Mutex mTaskWaitMutex;

    Condition mTaskCondition;
    //-------------------------

    sp<_CacheThreadManager> mCacheManager;

    Mutex mHandlerMutex;

    Condition mWaitCond;

    long mThreadTimeout;

    mutable volatile bool mStop;

    BlockingQueue<FutureTask> mPool;

    bool isNotifed;
};

DECLARE_SIMPLE_CLASS(CacheThreadManager) {
    
public:
    _CacheThreadManager(int queueSize,int minThreadNum,int maxThreadNum,int waittimeout,sp<_ThreadCachedPoolExecutor> executor);

    _CacheThreadManager();

    ~_CacheThreadManager();

    void bindTask(FutureTask);

    int idleNotify(ThreadCachedPoolExecutorHandler);

    int busyNotify(ThreadCachedPoolExecutorHandler);

    void completeNotify(ThreadCachedPoolExecutorHandler);
    //-----------
    int awaitTermination(long timeout);

    bool isTerminated();

    void release();

    void removeExecutor();

    int getThreadSum();

    void cancelTask(FutureTask task);

private:
    ArrayList<ThreadCachedPoolExecutorHandler> mIdleHandlers;
    Mutex mIdleHandlerMutex;

    ArrayList<ThreadCachedPoolExecutorHandler> mRunningHandlers;
    Mutex mRunningHandlerMutex;

    ArrayList<ThreadCachedPoolExecutorHandler> mCreatingHandlers;
    Mutex mCreatingHandlerMutex;

    Mutex mCompleteNotifyMutex;

    BlockingQueue<FutureTask> mFutureTasks;

    sp<_ThreadCachedPoolExecutor> mExecutor;

    Mutex mFutureTaskMutex;
    
    bool mIsTerminated;

    int mQueuesize;

    int mMinThreadNum;

    int mMaxThreadNum;

    int mWaitTimeout;

    Mutex mWaitTermMutex;

    Condition mWaitTermCond;

    mutable volatile bool mIsRelease;

    Mutex mReleaseMutex;

    Mutex mThreadNumMutex;

    int mThreadNum;
};


DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(ExecutorService)
                                               IMPLEMENTS(FutureTaskStatusListener) {

public:
    friend class _ThreadCachedPoolExecutorHandler;
    friend class _CacheThreadManager;
    friend class _FutureTask;

	_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout);

    _ThreadCachedPoolExecutor(int maxthreadnum,long timeout);

	_ThreadCachedPoolExecutor();

    int shutdown();

    int execute(Runnable command);

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    int getThreadsNum();

    ~_ThreadCachedPoolExecutor();


private:
    void onCancel(FutureTask);
    
    bool isOverMinSize();

    void removeHandler(ThreadCachedPoolExecutorHandler h);
    
    AtomicInteger mIdleThreadNum ;
    
    Mutex mHandlerMutex;
    
    ArrayList<ThreadCachedPoolExecutorHandler> mHandlers;

    //ArrayList<ThreadCachedPoolExecutorHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    void init(int queuesize,int maxthreadnum,int minthreadnum,long timeout);

    long mThreadTimeout;

    int maxThreadNum;

    int minThreadNum;

    int mQueueSize;

    Mutex mProtectMutex;

    CacheThreadManager mCacheManager;
};

}
#endif