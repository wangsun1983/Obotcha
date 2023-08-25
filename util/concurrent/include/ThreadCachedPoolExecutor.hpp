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
#include "AtomicNumber.hpp"

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

    int shutdown() final;

    bool isTerminated() override;

    int awaitTermination(long timeout = 0) final;

    int getPendingTaskNum() override;
    
    int getExecutingThreadNum() override;

    ~_ThreadCachedPoolExecutor() override;

  private:
    void setUpOneIdleThread();
    Future submitTask(ExecutorTask task) override; 
    void onRemoveTask(ExecutorTask task) override;

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