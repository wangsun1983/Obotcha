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

DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutorHandler) IMPLEMENTS(Runnable) {

public:

    _ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,long timeout,_ThreadCachedPoolExecutor *h);
    
    Thread mThread;
    
    bool isTerminated();

    void run();
    
    void stop();

    void waitForTerminate();

    void waitForTerminate(long);

    void forceStop();

    void onInterrupt();

private:
    BlockingQueue<FutureTask> mPool;

    ConcurrentQueue<sp<_ThreadCachedPoolExecutorHandler>> mHandlers;

    int state;

    bool isWaitTerminate;

    //pthread_mutex_t wiatIdleMutex;
    //pthread_cond_t wiatIdleCond;
    Mutex mStateMutex;

    Condition mWaitCond;

    bool isWaitIdle;

    long mThreadTimeout;

    mutable volatile bool mStop;

    sp<_ThreadCachedPoolExecutor> mPoolExecutor;
};


DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(ExecutorService) {

public:
    friend class _ThreadCachedPoolExecutorHandler;

    enum CachedExecuteResult {
        success,
        failShutDown,
        failUnknown
    };

	_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout);

    _ThreadCachedPoolExecutor(int maxthreadnum,long timeout);

	_ThreadCachedPoolExecutor();

    int shutdown();

    int shutdownNow();

    int execute(Runnable command);

    bool isShutdown();

    bool isTerminated();

    int awaitTermination();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    int getThreadsNum();

    ~_ThreadCachedPoolExecutor();

private:
    AtomicInteger mIdleThreadNum ;
    
    void increaseIdleThreadNum();

    void decreaseIdleThreadNum();

    bool isOverMinSize();

    void removeHandler(ThreadCachedPoolExecutorHandler h);

    BlockingQueue<FutureTask> mPool;
    
    ConcurrentQueue<ThreadCachedPoolExecutorHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    void init(int queuesize,int maxthreadnum,int minthreadnum,long timeout);

    long mThreadTimeout;

    int maxThreadNum;

    int minThreadNum;

    int mQueueSize;

    Mutex mProtectMutex;
};

}
#endif