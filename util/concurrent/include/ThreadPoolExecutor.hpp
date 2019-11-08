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

class _ThreadPoolExecutor;

DECLARE_SIMPLE_CLASS(ThreadPoolExecutorHandler) IMPLEMENTS(Runnable) {

public:

    _ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool,sp<_ThreadPoolExecutor> executor);
    
    bool isTerminated();

    void run();
    
    void stop();

    void waitForTerminate();

    void waitForTerminate(long);

    void onInterrupt();

    bool shutdownTask(FutureTask);

    ~_ThreadPoolExecutorHandler();

private:
    BlockingQueue<FutureTask> mPool;

    int state;

    bool mIdleWait;

    Mutex mStateMutex;

    Condition mWaitCond;

    bool isWaitTerminate;

    FutureTask mCurrentTask;

    mutable volatile bool mStop;

    Thread mThread;

    sp<_ThreadPoolExecutor> mExecutor;

    Mutex mExecutorMutex;
};


DECLARE_SIMPLE_CLASS(ThreadPoolExecutor) IMPLEMENTS(ExecutorService) 
                                         IMPLEMENTS(FutureTaskStatusListener) {

public:

    friend class _ThreadPoolExecutorHandler;

	_ThreadPoolExecutor(int queuesize,int threadnum);

	_ThreadPoolExecutor();

    int shutdown();

    int execute(Runnable command);

    bool isShutdown();

    bool isTerminated();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    int getThreadsNum();

    void onCancel(FutureTask);

    ~_ThreadPoolExecutor();

private:
    void onCompleteNotify(ThreadPoolExecutorHandler h);

    BlockingQueue<FutureTask> mPool;
    
    Mutex mHandlersMutex;
    ArrayList<ThreadPoolExecutorHandler> mHandlers;

    bool mIsShutDown;

    bool mIsTerminated;

    //bool isDynamic;
    int mThreadNum;

    void init(int queuesize,int threadnum);

    Mutex mProtectMutex;

    Mutex mWaitMutex;

    Condition mWaitCondition;
};

}
#endif