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
#include "FutureTask.hpp"

namespace obotcha {

class _ThreadCachedPoolExecutor;
class _ThreadScheduledPoolExecutor;

DECLARE_SIMPLE_CLASS(ThreadCachedPoolExecutor) {
public:
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
    enum CachedPoolStatus {
        StatusRunning = 0,
        StatusShutDown,
        StatusTerminate,
    };

    static const int DefaultWaitTime;
    static const int DefaultMaxThreadNums;
    static const int DefaultQueueNums;

    void setUpOneIdleThread();

    void submit(FutureTask task);
    
    Mutex mHandlerMutex;
    int threadNum;
    ArrayList<Thread> mHandlers;

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