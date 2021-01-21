#ifndef __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "AtomicInteger.hpp"

namespace obotcha {

class _ThreadPoolExecutor;

DECLARE_SIMPLE_CLASS(ThreadPoolExecutorHandler) IMPLEMENTS(Thread) {

public:

    _ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool);
    
    bool isTerminated();

    void run();

    void onInterrupt();

    bool shutdownTask(FutureTask);

    ~_ThreadPoolExecutorHandler();

private:
    BlockingQueue<FutureTask> mPool;

    //Mutex mStateMutex;

    FutureTask mCurrentTask;
};


DECLARE_SIMPLE_CLASS(ThreadPoolExecutor) IMPLEMENTS(ExecutorService) 
                                         IMPLEMENTS(FutureTaskStatusListener) {

public:

    friend class _ThreadPoolExecutorHandler;
    friend class _FutureTask;

	_ThreadPoolExecutor(int queuesize,int threadnum);

    _ThreadPoolExecutor(int threadnum);

	_ThreadPoolExecutor();

    int shutdown();

    int execute(Runnable command);

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    void setAsTerminated();

    Future submit(Runnable task);

    int getThreadsNum();

    int getQueueSize();

    ~_ThreadPoolExecutor();

private:
    enum LocalStatus {
        Idle = 0,
        Running,
        ShutDown,
        Terminated
    };

    static const int DefaultThreadNum;

    void onCancel(FutureTask);

    BlockingQueue<FutureTask> mPool;
    
    ArrayList<ThreadPoolExecutorHandler> mHandlers;

    //Mutex mStatusMutex;

    Mutex mHandlersMutex;

    //bool mIsShutDown;

    //bool mIsTerminated;
    AtomicInteger mStatus;

    int mThreadNum;

    void init(int queuesize,int threadnum);
};

}
#endif