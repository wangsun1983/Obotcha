#ifndef __OBOTCHA_EXECUTORS_HPP__
#define __OBOTCHA_EXECUTORS_HPP__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "LinkedList.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ExecutorBuilder) {

public:
    _ExecutorBuilder();

    _ExecutorBuilder* setQueueSize(int v);

    _ExecutorBuilder* setThreadNum(int v);

    _ExecutorBuilder* setMaxThreadNum(int v);

    _ExecutorBuilder* setMinThreadNum(int v);

    _ExecutorBuilder* setTimeout(int v);

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

}
#endif