#include "ExecutorBuilder.hpp"
#include "System.hpp"

namespace obotcha {

uint32_t _ExecutorBuilder::kDefaultMaxNoWorkingTime = 10*1000;
uint32_t _ExecutorBuilder::kDefaultMaxSubmitTaskWatiTime = 10*1000;

_ExecutorBuilder *_ExecutorBuilder::setMaxPendingTaskNum(size_t v) {
    mMaxPendingTaskNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setDefaultThreadNum(long v) {
    mDefaultThreadNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMaxThreadNum(long v) {
    mMaxThreadNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMinThreadNum(long v) {
    mMinThreadNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMaxNoWorkingTime(uint32_t v) {
    mMaxNoWorkingTime = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMaxSubmitTaskWaitTime(uint32_t v) {
    mMaxSubmitTaskWaitTime = v;
    return this;
}

ThreadPoolExecutor _ExecutorBuilder::newThreadPool() {
    return createThreadPoolExecutor(mMaxPendingTaskNum, 
                                    mDefaultThreadNum,
                                    mMaxSubmitTaskWaitTime);
}

ThreadCachedPoolExecutor _ExecutorBuilder::newCachedThreadPool() {
    return createThreadCachedPoolExecutor(mMaxPendingTaskNum, 
                                                   mMaxThreadNum, 
                                                   mMinThreadNum,
                                                   mMaxSubmitTaskWaitTime,
                                                   mMaxNoWorkingTime);
}

ThreadScheduledPoolExecutor _ExecutorBuilder::newScheduledThreadPool() {
    return createThreadScheduledPoolExecutor(mMaxPendingTaskNum,
                                                      mMaxSubmitTaskWaitTime);
}

ThreadPriorityPoolExecutor _ExecutorBuilder::newPriorityThreadPool() {
    return createThreadPriorityPoolExecutor(mMaxPendingTaskNum, 
                                                     mDefaultThreadNum,
                                                     mMaxSubmitTaskWaitTime);
}

} // namespace obotcha