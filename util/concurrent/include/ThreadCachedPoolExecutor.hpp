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
#include "ConcurrentHashMap.hpp"
#include "ConcurrentQueue.hpp"

namespace obotcha {

class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(Executor) {
  public:
    friend class _ThreadScheduledPoolExecutor;

    _ThreadCachedPoolExecutor(int queuesize = -1, int minthreadnum = 1, int maxthreadnum = 4,
                              long timeout = 10 * 1000);

    int shutdown();

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    //void submitTask(ExecutorTask task, long interval = 0);

    int getThreadsNum();

    int getTasksNum();

    ~_ThreadCachedPoolExecutor();

  private:
    void setUpOneIdleThread();
    Future submitRunnable(Runnable r);
    Future submitTask(ExecutorTask task); 
    //Future poolSubmit(Runnable r, long interval = 0);

    Mutex mMutex;

    int threadNum;

    ConcurrentQueue<Thread> mHandlers;

    long mThreadTimeout;

    int maxThreadNum;

    int minThreadNum;

    BlockingLinkedList<ExecutorTask> mTasks;

    AtomicInteger mIdleNum;

    std::atomic_int handlerId;
    
    ConcurrentHashMap<int,ExecutorTask> mRunningTasks;
};

} // namespace obotcha
#endif