#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "System.hpp"

static int id = 0;

namespace obotcha {
_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitTerminate(false){
    mStateMutex = createMutex("ThreadPoolExeHandlerMutex");
    mWaitCond = createCondition();

    mThread = createThread(this);

    mThread->start();
}

void _ThreadPoolExecutorHandler::forceStop() {
    mThread->exit();
    mStop = true;
}

void _ThreadPoolExecutorHandler::onInterrupt() {
    AutoMutex l(mStateMutex);
    state = terminateState;
    if(isWaitTerminate) {
        printf("notify trace \n");
        mWaitCond->notify();
        isWaitTerminate = false;
    }
}

void _ThreadPoolExecutorHandler::run() {
    while(!mStop) {
        //printf("_ThreadPoolExecutorHandler trace1 \n");
        FutureTask task = mPool->deQueueFirst();
        printf("_ThreadPoolExecutorHandler trace2 \n");
        if(task == nullptr) {
            return;
        }
        //printf("executor thred name is %s \n",mThread->getName()->toChars());
        {
            AutoMutex l(mStateMutex);
            state = busyState;
            if(task->getType() == FUTURE_TASK_SUBMIT) {
                task->onRunning();
            }
        }
        printf("_ThreadPoolExecutorHandler trace3 \n");
        Runnable runnable = task->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
        printf("_ThreadPoolExecutorHandler trace4 \n");
        {
            AutoMutex l(mStateMutex);
            state = idleState;

            if(task->getType() == FUTURE_TASK_SUBMIT) {
                task->onComplete();
            }
        }
        //printf("_ThreadPoolExecutorHandler trace5 \n");
    }
    //printf("_ThreadPoolExecutorHandler trace6 \n");
    {
        AutoMutex l(mStateMutex);
        state = terminateState;
        printf("_ThreadPoolExecutorHandler trace7 \n");
        if(isWaitTerminate) {
            printf("notify trace \n");
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }
}

void _ThreadPoolExecutorHandler::waitForTerminate() {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadPoolExecutorHandler::waitForTerminate(long interval) {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    //printf("waitForTerminate status is %d \n",state);
    if(state == busyState) {
        mWaitCond->wait(mStateMutex,interval);
    }
}

void _ThreadPoolExecutorHandler::stop() {
    mStop = true;
}

bool _ThreadPoolExecutorHandler::isTerminated() {
    return state == terminateState;
}

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    init(queuesize,threadnum);
}

_ThreadPoolExecutor::_ThreadPoolExecutor() {
    init(-1,1);
}

void _ThreadPoolExecutor::init(int queuesize,int threadnum) {
    if(queuesize > 0) {
        mPool = createBlockingQueue<FutureTask>(queuesize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    mHandlers = createConcurrentQueue<ThreadPoolExecutorHandler>();

    mThreadNum = threadnum;

    for(int i = 0; i < threadnum;i++) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool);
        mHandlers->enQueueLast(h);
    }

    mIsTerminated = false;
    mIsShutDown = false;
}

int _ThreadPoolExecutor::execute(Runnable runnable) {
    if(mIsShutDown ||mIsTerminated) {
        return -ExecutorFailAlreadyDestroy;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_NORMAL,runnable);

    mPool->enQueueLast(task);
}

int _ThreadPoolExecutor::shutdown() {
    if(mIsShutDown ||mIsTerminated) {
        return -ExecutorFailAlreadyDestroy;
    }

    mIsShutDown = true;
    int size = mHandlers->size();
    printf("shutdown trace1,mHandlers is %d \n",size);
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->stop();
    }

    printf("shutdown trace2 \n");
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }
    printf("shutdown trace3 \n");
    mPool->clear();
    printf("shutdown trace4 \n");

    return 0;
}

int _ThreadPoolExecutor::shutdownNow() {
    if(mIsShutDown ||mIsTerminated) {
        return -ExecutorFailAlreadyDestroy;
    }

    mIsShutDown = true;
    int size = mHandlers->size();
    printf("mHandlers size is %d \n",size);
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->forceStop();
    }

    printf("before mPool size is %d \n",mPool->size());
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }

    printf("after mPool size is %d \n",mPool->size());

    mIsTerminated = true;

    return 0;
}

Future _ThreadPoolExecutor::submit(Runnable r) {
    if(mIsShutDown||mIsTerminated) {
        return nullptr;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);
    printf("submit 1 \n");
    mPool->enQueueLast(task);
    printf("submit 2 \n");
    return future;
}

bool _ThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    if(mIsTerminated) {
        return true;
    }

    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        if(!mHandlers->get(i)->isTerminated()) {
            return false;
        }
    }

    mIsTerminated = true;
    return mIsTerminated;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
    printf("awaitTermination trace1 \n");
    if(!mIsShutDown) {
        printf("awaitTermination trace1_1 \n");
        return -ExecutorFailIsRunning;
    }

    if(mIsTerminated) {
        printf("awaitTermination trace1_2 \n");
        return 0;
    }

    printf("awaitTermination trace2 \n");
    int size = mHandlers->size();

    if(millseconds == 0) {
        for(int i = 0;i < size;i++) {
            mHandlers->get(i)->waitForTerminate();
        }
        mIsTerminated = true;
        return 0;
    } else {
        printf("awaitTermination trace3 \n");
        for(int i = 0;i < size;i++) {
            long current = st(System)::currentTimeMillis();
            if(millseconds >= 0) {
                printf("awaitTermination trace3_1,millseconds is %ld \n",millseconds);
                mHandlers->get(i)->waitForTerminate(millseconds);
                printf("awaitTermination trace3_2 \n");
            } else {
                break;
            }
            millseconds -= (st(System)::currentTimeMillis() - current);
        }

        if(millseconds <= 0) {
            return -ExecutorFailWaitTimeout;
        }
        printf("awaitTermination trace4 \n");
    }

    return 0;
}

int _ThreadPoolExecutor::getThreadsNum() {
    return mThreadNum;
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    //printf("_ThreadPoolExecutor destroy \n");
    shutdownNow();
}

}
