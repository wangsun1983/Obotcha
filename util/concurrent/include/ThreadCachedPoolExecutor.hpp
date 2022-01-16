#ifndef __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__

#include <atomic>
#include <vector>

#include "AutoLock.hpp"
#include "BlockingLinkedList.hpp"
#include "Executor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "HashMap.hpp"

namespace obotcha {

class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(Executor) {
  public:
    friend class _ThreadScheduledPoolExecutor;

    _ThreadCachedPoolExecutor(int queuesize, int minthreadnum, int maxthreadnum,
                              long timeout = 10 * 1000);

    int shutdown();

    template <typename X> int execute(sp<X> r) {
        if (poolSubmit(r) == nullptr) {
            return -InvalidStatus;
        }
        return 0;
    }

    template <typename X> int executeWithInTime(long timeout, sp<X> r) {
        if (poolSubmit(r, timeout) == nullptr) {
            return -InvalidStatus;
        }
        return 0;
    }

    template <class Function, class... Args>
    int execute(Function && f, Args && ... args) {
        return execute(createLambdaRunnable(f, args...));
    }

    template <class Function, class... Args>
    int executeWithInTime(long timeout, Function &&f, Args &&... args) {
        return execute(timeout, createLambdaRunnable(f, args...));
    }

    bool isShutDown();

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    template <typename X> Future submit(sp<X> r) { return poolSubmit(r); }

    template <typename X> Future submitWithInTime(long timeout, sp<X> r) {
        return poolSubmit(r, timeout);
    }

    template <class Function, class... Args>
    Future submit(Function && f, Args && ... args) {
        return poolSubmit(createLambdaRunnable(f, args...));
    }

    template <class Function, class... Args>
    Future submitWithInTime(long timeout, Function &&f, Args &&... args) {
        return poolSubmit(createLambdaRunnable(f, args...), timeout);
    }

    void submitTask(ExecutorTask task, long interval = 0);

    int getThreadsNum();

    int getTasksNum();

    ~_ThreadCachedPoolExecutor();

  private:
    void setUpOneIdleThread();

    Future poolSubmit(Runnable r, long interval = 0);

    Mutex mMutex;

    int threadNum;

    ArrayList<Thread> mHandlers;

    int mStatus;

    long mThreadTimeout;

    int maxThreadNum;

    int minThreadNum;

    BlockingLinkedList<ExecutorTask> mTasks;

    AtomicInteger mIdleNum;

    std::atomic_int handlerId;
    
    Mutex mRunningTaskMutex;
    HashMap<Integer,ExecutorTask> mRunningTasks;
};

} // namespace obotcha
#endif