#ifndef __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__

#include <vector>
#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "AutoLock.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"

using namespace std;

namespace obotcha {

class _ThreadCachedPoolExecutor;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutorHandler) IMPLEMENTS(Thread) {

public:
    friend class _ThreadCachedPoolExecutor;
    
    _ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask>,sp<_ThreadCachedPoolExecutor>,long timeout);

    void run();
    
    void stop();

    void onInterrupt();

    bool shutdownTask(FutureTask task);

    bool isIdle();

    ~_ThreadCachedPoolExecutorHandler();

private:

    FutureTask mCurrentTask;

    Mutex mTaskMutex;

    sp<_ThreadCachedPoolExecutor> mServiceExecutor;

    long mThreadTimeout;

    BlockingQueue<FutureTask> mPool;

    static const int HandleIdle;
    static const int HandleBusy;
    static const int HandleDestroy;

    Mutex mStatusMutex;
    int mStatus;
};

DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(ExecutorService)
                                               IMPLEMENTS(FutureTaskStatusListener) {
public:
    friend class _ThreadCachedPoolExecutorHandler;
    friend class _CacheThreadManager;
    friend class _FutureTask;
    friend class _ThreadScheduledPoolExecutor;

	_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout);

    _ThreadCachedPoolExecutor(int maxthreadnum,long timeout);

	_ThreadCachedPoolExecutor();

    int shutdown();

    int execute(Runnable command);

    bool isTerminated();

    void awaitTermination();

    void setAsTerminated();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    int getThreadsNum();

    ~_ThreadCachedPoolExecutor();

private:
    static const int StatusRunning;
    static const int StatusShutDown;
    static const int StatusTerminate;

    static const int DefaultWaitTime;
    static const int DefaultMaxThreadNums;
    static const int DefaultQueueNums;
    
    void onCancel(FutureTask);

    void onThreadComplete(ThreadCachedPoolExecutorHandler);

    void setUpOneIdleThread();

    void submit(FutureTask task);
    
    Mutex mHandlerMutex;
    int threadNum;
    ArrayList<ThreadCachedPoolExecutorHandler> mHandlers;

    std::atomic<int> mStatus;

    void init(int queuesize,int maxthreadnum,int minthreadnum,long timeout);

    long mThreadTimeout;

    int maxThreadNum;

    int minThreadNum;

    int mQueueSize;

    BlockingQueue<FutureTask> mTasks;

};

}
#endif