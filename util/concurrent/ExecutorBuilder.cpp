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

#include "ExecutorBuilder.hpp"
#include "System.hpp"

namespace obotcha {

_ExecutorBuilder::_ExecutorBuilder() {
    queuesize = -1;
    threadnum = st(System)::availableProcessors();
    maxthreadnum = st(System)::availableProcessors() * 2;
    minthreadnum = 1;
    queueTimeout = 0;
    timeout = 1000 * 10;
}

_ExecutorBuilder *_ExecutorBuilder::setQueueSize(int v) {
    queuesize = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setThreadNum(int v) {
    threadnum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMaxThreadNum(int v) {
    maxthreadnum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setMinThreadNum(int v) {
    minthreadnum = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setCacheTimeout(long v) {
    timeout = v;
    return this;
}

_ExecutorBuilder *_ExecutorBuilder::setQueueTimeout(long v) {
    queueTimeout = v;
    return this;
}

ThreadPoolExecutor _ExecutorBuilder::newThreadPool() {
    auto executor = createThreadPoolExecutor(queuesize, threadnum);
    updateQueueTimeout(executor);

    return executor;
}

ThreadCachedPoolExecutor _ExecutorBuilder::newCachedThreadPool() {
    auto executor = createThreadCachedPoolExecutor(queuesize, minthreadnum, maxthreadnum,
                                          timeout);
    updateQueueTimeout(executor);

    return executor;
}

ThreadScheduledPoolExecutor _ExecutorBuilder::newScheduledThreadPool() {
    auto executor = createThreadScheduledPoolExecutor(queuesize);
    updateQueueTimeout(executor);

    return executor;
}

ThreadPriorityPoolExecutor _ExecutorBuilder::newPriorityThreadPool() {
    auto executor = createThreadPriorityPoolExecutor(queuesize, threadnum);
    updateQueueTimeout(executor);

    return executor;
}

void _ExecutorBuilder::updateQueueTimeout(Executor exec) {
    if(queueTimeout != 0) {
        exec->setQueueTimeout(queueTimeout);
    }
}

} // namespace obotcha