#include "ExecutorBuilder.hpp"
#include "System.hpp"

namespace obotcha {

int _ExecutorBuilder::DefaultMaxNoWorkingTime = 10*1000;
int _ExecutorBuilder::DefaultMaxSubmitTaskWatiTime = 10*1000;

_ExecutorBuilder::_ExecutorBuilder() {
    mMaxPendingTaskNum = -1;
    mDefaultThreadNum = st(System)::availableProcessors();
    mMaxThreadNum = st(System)::availableProcessors() * 2;
    mMinThreadNum = 1;
    mMaxNoWorkingTime = DefaultMaxNoWorkingTime;
    mMaxSubmitTaskWaitTime = 0;
}

_ExecutorBuilder *_ExecutorBuilder::setMaxPendingTaskNum(int v) {
    mMaxPendingTaskNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setDefaultThreadNum(int v) {
    mDefaultThreadNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMaxThreadNum(int v) {
    mMaxThreadNum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMinThreadNum(int v) {
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
                                                   mMaxNoWorkingTime);;
}

ThreadScheduledPoolExecutor _ExecutorBuilder::newScheduledThreadPool() {
    return createThreadScheduledPoolExecutor(mMaxPendingTaskNum,
                                                      mMaxSubmitTaskWaitTime);;
}

ThreadPriorityPoolExecutor _ExecutorBuilder::newPriorityThreadPool() {
    return createThreadPriorityPoolExecutor(mMaxPendingTaskNum, 
                                                     mDefaultThreadNum,
                                                     mMaxSubmitTaskWaitTime);
}

} // namespace obotcha