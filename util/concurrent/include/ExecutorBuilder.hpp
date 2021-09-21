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

    _ExecutorBuilder *setQueueSize(int v);

    _ExecutorBuilder *setThreadNum(int v);

    _ExecutorBuilder *setMaxThreadNum(int v);

    _ExecutorBuilder *setMinThreadNum(int v);

    _ExecutorBuilder *setTimeout(int v);

    ThreadPoolExecutor newThreadPool();

    ThreadCachedPoolExecutor newCachedThreadPool();

    ThreadScheduledPoolExecutor newScheduledThreadPool();

    ThreadPriorityPoolExecutor newPriorityThreadPool();

  private:
    int queuesize;
    int threadnum;
    int maxthreadnum;
    int minthreadnum;
    long timeout;
};

} // namespace obotcha
#endif