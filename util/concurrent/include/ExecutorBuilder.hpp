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

#include <any>

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

    _ExecutorBuilder *setMaxPendingTaskNum(int);

    _ExecutorBuilder *setDefaultThreadNum(int v);

    _ExecutorBuilder *setMaxThreadNum(int v);

    _ExecutorBuilder *setMinThreadNum(int v);

    _ExecutorBuilder *setMaxNoWorkingTime(uint32_t v);

    _ExecutorBuilder *setMaxSubmitTaskWaitTime(uint32_t v);

    ThreadPoolExecutor newThreadPool();

    ThreadCachedPoolExecutor newCachedThreadPool();

    ThreadScheduledPoolExecutor newScheduledThreadPool();

    ThreadPriorityPoolExecutor newPriorityThreadPool();

  private:
    static int kDefaultMaxNoWorkingTime;
    static int kDefaultMaxSubmitTaskWatiTime;

    int mMaxPendingTaskNum = st(BlockingLinkedList<std::any>)::kLinkedListSizeInfinite;
    int mDefaultThreadNum = st(System)::AvailableProcessors();
    int mMaxThreadNum =  st(System)::AvailableProcessors() * 2;
    int mMinThreadNum = 1;
    uint32_t mMaxNoWorkingTime = kDefaultMaxNoWorkingTime;
    uint32_t mMaxSubmitTaskWaitTime = 0;
};

} // namespace obotcha
#endif