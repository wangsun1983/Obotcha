#ifndef __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"
#include "Executor.hpp"

namespace obotcha {

DECLARE_CLASS(ThreadPoolExecutor) IMPLEMENTS(Executor) {

public:
    friend class _ExecutorTask;

    _ThreadPoolExecutor(int capacity,int threadnum);
    
    int shutdown();
    
    template<typename X>
    int execute(sp<X> runnable) {
       return executeWithInTime(0,runnable);
    }

    template<typename X>
    int executeWithInTime(long timeout,sp<X> runnable) {
        if(submitWithInTime(timeout,runnable) != nullptr) {
            return 0;
        }

        return -InvalidStatus;
    }
    
    template< class Function, class... Args >
    int execute( Function&& f, Args&&... args ) {
        return executeWithInTime(0,createLambdaRunnable(f,args...));
    }

    template< class Function, class... Args >
    int executeWithInTime(long timeout, Function&& f, Args&&... args ) {
        return executeWithInTime(timeout,createLambdaRunnable(f,args...));
    }

    bool isShtuDown();
    bool isTerminated();

    int awaitTermination(long timeout = 0);

    template<typename X>
    Future submit(sp<X> r) {
        return submitWithInTime(0,r);
    }

    template<typename X>
    Future submitWithInTime(long timeout,sp<X> r) {
        {
            AutoLock l(mMutex);
            if(mStatus == ShutDown) {
                return nullptr;
            }
        }
        ExecutorTask task = createExecutorTask(r);
        if(mPool->putLast(task,timeout)){
            return createFuture(task);
        }
        return nullptr;
    }

    template< class Function, class... Args >
    Future submit( Function&& f, Args&&... args ) {
        return submitWithInTime(0,createLambdaRunnable(f,args...));
    }

    template< class Function, class... Args >
    Future submitWithInTime(long time, Function&& f, Args&&... args ) {
        return submitWithInTime(time,createLambdaRunnable(f,args...));
    }

    int getThreadsNum();

    int getTasksNum();

    ~_ThreadPoolExecutor();

private:

    BlockingLinkedList<ExecutorTask> mPool;
    
    ArrayList<Thread> mHandlers;

    Mutex mMutex;
    int mStatus;
};

}
#endif