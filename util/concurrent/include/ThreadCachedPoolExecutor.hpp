#ifndef __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_CACHED_POOL_EXECUTOR_HPP__

#include <atomic>

#include "Object.hpp"
#include "BlockingLinkedList.hpp"
#include "Executor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Thread.hpp"
#include "ConcurrentHashMap.hpp"
#include "ConcurrentQueue.hpp"

namespace obotcha {

class _ThreadScheduledPoolExecutor;

DECLARE_CLASS(ThreadCachedPoolExecutor) IMPLEMENTS(Executor) {
  public:
    friend class _ThreadScheduledPoolExecutor;

    _ThreadCachedPoolExecutor(int maxPendingTaskNum, 
                              int maxThreadNum, 
                              int minThreadNum,
                              uint32_t maxSubmitTaskWaittime,
                              uint32_t maxNoWorkingTime);

    int shutdown();

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    int getPendingTaskNum();
    
    int getExecutingThreadNum();

    ~_ThreadCachedPoolExecutor();

  private:
    void setUpOneIdleThread();
    Future submitTask(ExecutorTask task); 
    void onRemoveTask(ExecutorTask task);

    Mutex mMutex;

    int threadNum;

    ConcurrentQueue<Thread> mHandlers;

    BlockingLinkedList<ExecutorTask> mTasks;

    AtomicInteger mIdleNum;

    std::atomic_int handlerId;
    
    ConcurrentHashMap<int,ExecutorTask> mRunningTasks;
};

} // namespace obotcha
#endif