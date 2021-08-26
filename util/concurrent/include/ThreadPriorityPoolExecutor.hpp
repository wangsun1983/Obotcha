#ifndef __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__
#define __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "ArrayList.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Error.hpp"
#include "LinkedList.hpp"
#include "Executor.hpp"

namespace obotcha {

DECLARE_CLASS(ThreadPriorityPoolExecutor) IMPLEMENTS(Executor){

public:
    _ThreadPriorityPoolExecutor(int capacity,int threadnum);

    template<typename X>
    int executeWithInTime(long timeout,int level,sp<X> r) {
        if(submit(timeout,level,r) == nullptr) {
            return -InvalidStatus;
        }

        return 0;
    }

    template<typename X>
    int execute(int level,sp<X> r) {
        return executeWithInTime(0,level,r);
    }

    template< class Function, class... Args >
    int executeWithInTime(long timeout,int priority, Function&& f, Args&&... args ) {
        return execute(timeout,priority,createLambdaRunnable(f,args...));
    }

    template< class Function, class... Args >
    int executeWithInTime(int priority, Function&& f, Args&&... args ) {
        return execute(0,priority,createLambdaRunnable(f,args...));
    }

    int shutdown();

    bool isShutDown();
    
    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    
    template<typename X>
    Future submit(int timeout,int level,sp<X> r) {
        return submitWithInTime(0,level,r);
    }

    template<typename X>
    Future submitWithInTime(int timeout,int level,sp<X> r) {
        AutoLock l(mTaskMutex);
        if(mStatus == ShutDown) {
            return nullptr;
        }
    
        ExecutorTask task = createExecutorTask(r);
        {
            
            switch(level) {
                case High:
                    if(mCapacity != -1 && mHighPriorityTasks->size() == mCapacity) {
                        notFull->wait(mTaskMutex,timeout);
                    }
                    mHighPriorityTasks->putLast(task);
                    notEmpty->notify();
                break;

                case Medium:
                    if(mCapacity != -1 && mMidPriorityTasks->size() == mCapacity) {
                        notFull->wait(mTaskMutex,timeout);
                    }
                    mMidPriorityTasks->putLast(task);
                    notEmpty->notify();
                break;

                case Low:
                    if(mCapacity != -1 && mLowPriorityTasks->size() == mCapacity) {
                        notFull->wait(mTaskMutex,timeout);
                    }
                    mLowPriorityTasks->putLast(task);
                    notEmpty->notify();
                break;

                default:
                return nullptr;
            }
        }

        return createFuture(task);
    }

    template< class Function, class... Args >
    Future submitWithInTime(long timeout,int priority, Function&& f, Args&&... args ) {
        return submitWithInTime(timeout,priority,createLambdaRunnable(f,args...));
    }

    template< class Function, class... Args >
    Future submit(int priority, Function&& f, Args&&... args ) {
        return submitWithInTime(0,priority,createLambdaRunnable(f,args...));
    }

    int getThreadsNum();

    ~_ThreadPriorityPoolExecutor();
    
private:
    enum Status {
        Running,
        ShutDown
    };

    Mutex mTaskMutex;
    Condition notFull;
    Condition notEmpty;
    LinkedList<ExecutorTask>mHighPriorityTasks;
    LinkedList<ExecutorTask>mMidPriorityTasks;
    LinkedList<ExecutorTask>mLowPriorityTasks;

    int mStatus;    
    int mCapacity;

    ArrayList<Thread> mThreads;
};

}
#endif