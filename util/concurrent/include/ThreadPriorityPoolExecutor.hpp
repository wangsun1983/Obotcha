#ifndef __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__
#define __OBOTCHA_THREAD_PRIORITY_POOL_EXECUTOR_SERVICE_H__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Error.hpp"
#include "LinkedList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(PriorityTask) EXTENDS(FutureTask) {
public:
    _PriorityTask(int,Runnable);

    int priority;
};

DECLARE_SIMPLE_CLASS(ThreadPriorityPoolExecutor) {

public:
    friend class _PriorityPoolThread;
    enum Priority {
        PriorityLow = 0,
        PriorityMedium,
        PriorityHigh,
        PriorityNoUse
    };

    _ThreadPriorityPoolExecutor();

    _ThreadPriorityPoolExecutor(int threadnum);

    int execute(Runnable command);

    template<typename X>
    int execute(int level,sp<X> r) {
        if(submit(level,r) == nullptr) {
            return -InvalidStatus;
        }

        return 0;
    }

    template< class Function, class... Args >
    int execute(int priority, Function&& f, Args&&... args ) {
        if(submit(priority,createLambdaRunnable(f,args...)) == nullptr){
            return -InvalidStatus;
        };
        return 0;
    }

    int shutdown();

    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    template<typename X>
    Future submit(int level,sp<X> task) {
        {
            AutoLock l(mStatusMutex);
            
            if(isShutDown) {
                return nullptr;
            }
        }

        PriorityTask prioTask = createPriorityTask(level,task);
        {
            AutoLock l(mTaskMutex);
            switch(prioTask->priority) {
                case PriorityHigh:
                    mHighPriorityTasks->enQueueLast(prioTask);
                    mTaskCond->notify();
                break;

                case PriorityMedium:
                    mMidPriorityTasks->enQueueLast(prioTask);
                    mTaskCond->notify();
                break;

                case PriorityLow:
                    mLowPriorityTasks->enQueueLast(prioTask);
                    mTaskCond->notify();
                break;
            }
        }

        return createFuture(prioTask);
    }

    template< class Function, class... Args >
    Future submit(int priority, Function&& f, Args&&... args ) {
        return submit(priority,createLambdaRunnable(f,args...));
    }

    int getThreadsNum();

    ~_ThreadPriorityPoolExecutor();
    
private:
    Mutex mTaskMutex;
    Condition mTaskCond;
    LinkedList<PriorityTask>mHighPriorityTasks;
    LinkedList<PriorityTask>mMidPriorityTasks;
    LinkedList<PriorityTask>mLowPriorityTasks;

    int mThreadNum;

    Mutex mStatusMutex;

    bool isShutDown;

    bool isTermination;
    
    Mutex mThreadMutex;
    ArrayList<Thread> mThreads;

    Mutex mWaitMutex;
    
    Condition mWaitCondition;
};

}
#endif