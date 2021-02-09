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

    template<typename X>
    int execute(sp<X> r) {
        if(submit(r) == nullptr) {
            return -InvalidStatus;
        }
        return 0;
    }

    template< class Function, class... Args >
    int execute( Function&& f, Args&&... args ) {
        execute(createLambdaRunnable(f,args...));
    }

    bool isTerminated();

    void awaitTermination();
    
    int awaitTermination(long timeout);

    template <typename X>
    Future submit(sp<X> r) {
        if(mStatus != StatusRunning) {
            return nullptr;
        }

        FutureTask task = createFutureTask(r);
        Future future = createFuture(task);
        submit(task);
        return future; 
    }

    template< class Function, class... Args >
    Future submit( Function&& f, Args&&... args ) {
        return submit(createLambdaRunnable(f,args...));
    }

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