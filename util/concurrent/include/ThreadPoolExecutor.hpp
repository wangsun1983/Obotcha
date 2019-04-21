#ifndef __THREAD_POOL_EXECUTOR_HPP__
#define __THREAD_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"

using namespace std;

namespace obotcha {
enum State {
    idleState,
    busyState,
    illegalState,
};

DECLARE_SIMPLE_CLASS(ThreadPoolExecutorHandler) IMPLEMENTS(Runnable) {

public:

    _ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool);
    
    Thread mThread;
    
    bool isIdle();

    void run();
    
    void stop();

    void waitForIdle();

    void forceStop();

private:
    BlockingQueue<FutureTask> mPool;

    int state;

    bool mIdleWait;

    //pthread_mutex_t wiatIdleMutex;
    //pthread_cond_t wiatIdleCond;
    Mutex mStateMutex;

    Condition mWaitCond;

    bool isWaitIdle;

    mutable volatile bool mStop;
};


DECLARE_SIMPLE_CLASS(ThreadPoolExecutor) IMPLEMENTS(ExecutorService) {

public:
    enum ExecuteResult {
        success,
        failShutDown,
        failUnknown
    };

	_ThreadPoolExecutor(int size);

	_ThreadPoolExecutor();

    void shutdown();

    void shutdownNow();

    void execute(Runnable command);

    bool isShutdown();

    bool isTerminated();

    bool awaitTermination(long timeout);

    Future submit(Runnable task);

    //~_ThreadPoolExecutor();

private:
    BlockingQueue<FutureTask> mPool;
    
    ConcurrentQueue<ThreadPoolExecutorHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    //bool isDynamic;

    void init(int size);
};

}
#endif