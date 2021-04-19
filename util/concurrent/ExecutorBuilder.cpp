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
    maxthreadnum = st(System)::availableProcessors()*2;
    minthreadnum = 2;
    timeout = 1000*16;
}

_ExecutorBuilder* _ExecutorBuilder::setQueueSize(int v) {
    queuesize = v;
    return this;
}

_ExecutorBuilder* _ExecutorBuilder::setThreadNum(int v) {
    threadnum = v;
    return this;
}

_ExecutorBuilder* _ExecutorBuilder::setMaxThreadNum(int v) {
    maxthreadnum = v;
    return this;
}

_ExecutorBuilder* _ExecutorBuilder::setMinThreadNum(int v) {
    minthreadnum = v;
    return this;
}

_ExecutorBuilder* _ExecutorBuilder::setTimeout(int v) {
    timeout = v;
    return this;
}

ThreadPoolExecutor _ExecutorBuilder::newThreadPool() {
    return createThreadPoolExecutor(queuesize,threadnum);
}

ThreadCachedPoolExecutor _ExecutorBuilder::newCachedThreadPool() {
    return createThreadCachedPoolExecutor(queuesize,minthreadnum,maxthreadnum,timeout);
}

ThreadScheduledPoolExecutor _ExecutorBuilder::newScheduledThreadPool() {
    return createThreadScheduledPoolExecutor();
}

ThreadPriorityPoolExecutor _ExecutorBuilder::newPriorityThreadPool() {
    return createThreadPriorityPoolExecutor(threadnum);
}

}