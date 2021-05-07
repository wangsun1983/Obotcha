#ifndef __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__
#define __OBOTCHA_THREAD_POOL_EXECUTOR_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ThreadPoolExecutor) {

public:
    friend class _FutureTask;

    _ThreadPoolExecutor(int queuesize,int threadnum);
    
    int shutdown();
    
    template<typename X>
    int execute(sp<X> runnable) {
        if(submit(runnable) != nullptr) {
            return 0;
        }

        return -InvalidStatus;
    }
    
    template< class Function, class... Args >
    int execute( Function&& f, Args&&... args ) {
        return execute(createLambdaRunnable(f,args...));
    }

    bool isShtuDown();
    bool isTerminated();

    void awaitTermination();

    int awaitTermination(long timeout);

    template<typename X>
    Future submit(sp<X> r) {
        FutureTask task = createFutureTask(r);
        if(mPool->enQueueLast(task)){
            return createFuture(task);
        }
        return nullptr;
    }

    template< class Function, class... Args >
    Future submit( Function&& f, Args&&... args ) {
        return submit(createLambdaRunnable(f,args...));
    }

    int getThreadsNum();

    int getQueueSize();

    ~_ThreadPoolExecutor();

private:
    enum LocalStatus {
        Running = 0,
        ShutDown,
    };

    BlockingQueue<FutureTask> mPool;
    
    ArrayList<Thread> mHandlers;

    int mStatus;
};

}
#endif