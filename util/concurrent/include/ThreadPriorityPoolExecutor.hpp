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

namespace obotcha {

DECLARE_SIMPLE_CLASS(ThreadPriorityPoolExecutor) {

public:
    enum Priority {
        Low = 0,
        Medium,
        High,
        NoUse
    };

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
        return execute(priority,createLambdaRunnable(f,args...));
    }

    int shutdown();

    bool isShutDown();
    
    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    Future submit(Runnable task);

    template<typename X>
    Future submit(int level,sp<X> r) {
    
        AutoLock l(mTaskMutex);
        if(mStatus== ShutDown) {
            return nullptr;
        }
    
        FutureTask task = createFutureTask(r);
        {
            
            switch(level) {
                case High:
                    mHighPriorityTasks->enQueueLast(task);
                    mTaskCond->notify();
                break;

                case Medium:
                    mMidPriorityTasks->enQueueLast(task);
                    mTaskCond->notify();
                break;

                case Low:
                    mLowPriorityTasks->enQueueLast(task);
                    mTaskCond->notify();
                break;

                default:
                return nullptr;
            }
        }

        return createFuture(task);
    }

    template< class Function, class... Args >
    Future submit(int priority, Function&& f, Args&&... args ) {
        return submit(priority,createLambdaRunnable(f,args...));
    }

    int getThreadsNum();

    ~_ThreadPriorityPoolExecutor();
    
private:
    enum Status {
        Running,
        ShutDown
    };

    Mutex mTaskMutex;
    Condition mTaskCond;
    LinkedList<FutureTask>mHighPriorityTasks;
    LinkedList<FutureTask>mMidPriorityTasks;
    LinkedList<FutureTask>mLowPriorityTasks;
    int mStatus;    
    ArrayList<Thread> mThreads;
};

}
#endif