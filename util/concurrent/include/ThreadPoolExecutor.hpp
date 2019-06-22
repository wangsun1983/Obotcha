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

DECLARE_SIMPLE_CLASS(ThreadPoolExecutorHandler) IMPLEMENTS(Runnable) {

public:

    _ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool);
    
    bool isTerminated();

    void run();
    
    void stop();

    void waitForTerminate();

    void waitForTerminate(long);

    void forceStop();

    void onInterrupt();

private:
    BlockingQueue<FutureTask> mPool;

    int state;

    bool mIdleWait;

    Mutex mStateMutex;

    Condition mWaitCond;

    bool isWaitTerminate;

    mutable volatile bool mStop;

    Thread mThread;
};


DECLARE_SIMPLE_CLASS(ThreadPoolExecutor) IMPLEMENTS(ExecutorService) {

public:
    enum ExecuteResult {
        success,
        failShutDown,
        failUnknown
    };

	_ThreadPoolExecutor(int queuesize,int threadnum);

	_ThreadPoolExecutor();

    int shutdown();

    int shutdownNow();

    int execute(Runnable command);

    bool isShutdown();

    bool isTerminated();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    int getThreadsNum();

    ~_ThreadPoolExecutor();

private:
    BlockingQueue<FutureTask> mPool;
    
    ConcurrentQueue<ThreadPoolExecutorHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    //bool isDynamic;
    int mThreadNum;

    void init(int queuesize,int threadnum);
};

}
#endif