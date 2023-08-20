/**
 * @file ThreadPoolExecutor.hpp
 * @brief An ThreadPool that executes each submitted task using
 *        one of possibly several pooled threads, normally configured
 *        using ExecutorBuilder factory methods.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2022-10-19
 * @license none
 * @history
 */

#ifndef __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__

#include "Object.hpp"
#include "BlockingLinkedList.hpp"
#include "Executor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Thread.hpp"
#include "List.hpp"

namespace obotcha {

DECLARE_CLASS(ThreadPoolExecutor) IMPLEMENTS(Executor) {

public:
    friend class _ExecutorTask;

    _ThreadPoolExecutor(int maxPendingTaskNum,
                        int defalutThreadNum,
                        uint32_t maxSubmitTaskWaitTime);

    int shutdown() final;

    bool isTerminated() override;

    int awaitTermination(long timeout = 0) final;

    int getPendingTaskNum() override;
    
    int getExecutingThreadNum() override;

    ~_ThreadPoolExecutor() override;

private:
    Future submitTask(ExecutorTask task) override;
    
    BlockingLinkedList<ExecutorTask> mPendingTasks;

    ArrayList<Thread> mHandlers;

    Mutex mRunningTaskMutex;

    List<ExecutorTask> mRunningTasks;

    void onRemoveTask(ExecutorTask task) override;
};

} // namespace obotcha
#endif