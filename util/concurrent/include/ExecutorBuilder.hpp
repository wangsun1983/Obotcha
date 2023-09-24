/**
 * @file Executors.cpp
 * @brief Executor Factory
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#ifndef __OBOTCHA_EXECUTORS_HPP__
#define __OBOTCHA_EXECUTORS_HPP__

#include "ThreadCachedPoolExecutor.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "BlockingLinkedList.hpp"
#include "System.hpp"

namespace obotcha {

DECLARE_CLASS(ExecutorBuilder) {

  public:
    _ExecutorBuilder() = default;

    _ExecutorBuilder *setMaxPendingTaskNum(size_t);

    _ExecutorBuilder *setDefaultThreadNum(long v);

    _ExecutorBuilder *setMaxThreadNum(long v);

    _ExecutorBuilder *setMinThreadNum(long v);

    _ExecutorBuilder *setMaxNoWorkingTime(uint32_t v);

    _ExecutorBuilder *setMaxSubmitTaskWaitTime(uint32_t v);

    ThreadPoolExecutor newThreadPool();

    ThreadCachedPoolExecutor newCachedThreadPool();

    ThreadScheduledPoolExecutor newScheduledThreadPool();

    ThreadPriorityPoolExecutor newPriorityThreadPool();

  private:
    static uint32_t kDefaultMaxNoWorkingTime;
    static uint32_t kDefaultMaxSubmitTaskWatiTime;

    size_t mMaxPendingTaskNum = st(Util)::Container::kInfiniteSize;
    long mDefaultThreadNum = st(System)::AvailableProcessors();
    long mMaxThreadNum =  st(System)::AvailableProcessors() * 2;
    int mMinThreadNum = 1;
    uint32_t mMaxNoWorkingTime = kDefaultMaxNoWorkingTime;
    uint32_t mMaxSubmitTaskWaitTime = st(Concurrent)::kWaitForEver;
};

} // namespace obotcha
#endif