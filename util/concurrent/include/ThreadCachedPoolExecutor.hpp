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
enum State {
    idleState,
    busyState,
    illegalState,
};

class _ThreadCachedPoolExecutor;

DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutorHandler) IMPLEMENTS(Runnable) {

public:

    _ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,long timeout,_ThreadCachedPoolExecutor *h);
    
    Thread mThread;
    
    bool isIdle();

    void run();
    
    void stop();

    void waitForIdle();

    void forceStop();

private:
    BlockingQueue<FutureTask> mPool;

    ConcurrentQueue<sp<_ThreadCachedPoolExecutorHandler>> mHandlers;

    int state;

    bool mIdleWait;

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
    enum CachedExecuteResult {
        success,
        failShutDown,
        failUnknown
    };

	_ThreadCachedPoolExecutor(int size,long timeout);

	_ThreadCachedPoolExecutor();

    void shutdown();

    void shutdownNow();

    void execute(Runnable command);

    bool isShutdown();

    bool isTerminated();

    bool awaitTermination(long timeout);

    Future submit(Runnable task);

    void removeHandler(ThreadCachedPoolExecutorHandler h);

    //~_ThreadPoolExecutor();

private:
    BlockingQueue<FutureTask> mPool;
    
    ConcurrentQueue<ThreadCachedPoolExecutorHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    //bool isDynamic;

    void init(int size,long timeout);

    long mThreadTimeout;

    int mPoolCapcity;

};

}
#endif