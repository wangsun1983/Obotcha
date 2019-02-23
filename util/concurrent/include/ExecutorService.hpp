#ifndef __EXCUTE_SERVICE_H__
#define __EXCUTE_SERVICE_H__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"


using namespace std;

enum State {
    idleState,
    busyState,
    illegalState,
};

DECLARE_SIMPLE_CLASS(ExecutorServiceHandler) IMPLEMENTS(Runnable) {

public:

    _ExecutorServiceHandler(BlockingQueue<Runnable> pool);
    
    Thread mThread;
    
    bool isIdle();

    void run();
    
    void stop();

    void waitForIdle();

private:
    BlockingQueue<Runnable> mPool;

    int state;

    bool mIdleWait;

    //pthread_mutex_t wiatIdleMutex;
    //pthread_cond_t wiatIdleCond;
    Mutex mStateMutex;

    Condition mWaitCond;

    bool isWaitIdle;

    mutable volatile bool mStop;
};


DECLARE_SIMPLE_CLASS(ExecutorService) {

public:
    enum ExecuteResult {
        success,
        failShutDown,
        failUnknown
    };

	_ExecutorService(int size);

	_ExecutorService();

    int execute(Runnable runnable);

    void shutdown();

    //wait for all the task complete.
    void awaitTermination();

    void awaitTermination(long millseconds);

    ~_ExecutorService() {
    }

private:
    BlockingQueue<Runnable> mPool;
    
    ConcurrentQueue<ExecutorServiceHandler> mHandlers;

    bool isShutDown;

    bool isDynamic;

    void init(int size,bool isDyn);
};

#endif