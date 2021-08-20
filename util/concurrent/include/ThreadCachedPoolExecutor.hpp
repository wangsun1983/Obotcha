#ifndef __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__

#include <vector>
#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "AutoLock.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorTask.hpp"
#include "Executor.hpp"

namespace obotcha {

class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(Executor){
public:
    friend class _ThreadScheduledPoolExecutor;
    
    _ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout = 10*1000);

    int shutdown();

    template<typename X>
    int execute(sp<X> r) {
        if(poolSubmit(r) == nullptr) {
            return -InvalidStatus;
        }
        return 0;
    }

    template< class Function, class... Args >
    int execute( Function&& f, Args&&... args ) {
        return execute(createLambdaRunnable(f,args...));
    }

    bool isShutDown();

    bool isTerminated();

    void awaitTermination();
    
    int awaitTermination(long timeout);

    template <typename X>
    Future submit(sp<X> r) {
        return poolSubmit(r);
    }

    template< class Function, class... Args >
    Future submit( Function&& f, Args&&... args ) {
        return poolSubmit(createLambdaRunnable(f,args...));
    }

    int getThreadsNum();

    int getTasksNum();

    ~_ThreadCachedPoolExecutor();

private:
    void setUpOneIdleThread();

    Future poolSubmit(Runnable r);
    
    Mutex mMutex;

    int threadNum;
    
    ArrayList<Thread> mHandlers;

    int mStatus;

    long mThreadTimeout;

    int maxThreadNum;

    int minThreadNum;

    BlockingLinkedList<ExecutorTask> mTasks;

    AtomicInteger mIdleNum;
};

}
#endif