#ifndef __OBOTCHA_EXECUTORS_HPP__
#define __OBOTCHA_EXECUTORS_HPP__

#include <map>
#include <pthread.h>

#include "LinkedList.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "ThreadScheduledPoolExecutor.hpp"

namespace obotcha {

DECLARE_CLASS(ExecutorBuilder) {

  public:
    _ExecutorBuilder();

    //_ExecutorBuilder *setQueueSize(int v);
    _ExecutorBuilder *setMaxPendingTaskNum(uint32_t);

    //_ExecutorBuilder *setQueueTimeout(long v);
    _ExecutorBuilder *setMaxSubmitTaskWaitTime(uint32_t v);

    //_ExecutorBuilder *setThreadNum(int v);
    _ExecutorBuilder *setDefaultThreadNum(int v);

    _ExecutorBuilder *setMaxThreadNum(int v);

    _ExecutorBuilder *setMinThreadNum(int v);

    //_ExecutorBuilder *setCacheTimeout(long v);
    _ExecutorBuilder *setMaxNoWorkingTime(uint32_t v);

    ThreadPoolExecutor newThreadPool();

    ThreadCachedPoolExecutor newCachedThreadPool();

    ThreadScheduledPoolExecutor newScheduledThreadPool();

    ThreadPriorityPoolExecutor newPriorityThreadPool();

  private:
    static int DefaultMaxNoWorkingTime;
    static int DefaultMaxSubmitTaskWatiTime;

    int mMaxPendingTaskNum;
    int mDefaultThreadNum;
    int mMaxThreadNum;
    int mMinThreadNum;
    uint32_t mMaxNoWorkingTime;
    uint32_t mMaxSubmitTaskWaitTime;

    void updateQueueTimeout(Executor exec);
};

} // namespace obotcha
#endif