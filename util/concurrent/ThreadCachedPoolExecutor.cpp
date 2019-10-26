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
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"

namespace obotcha {

#define DEFAULT_CACHED_THREAD_WAIT_TIME 15*1000
#define DEFAULT_CACHED_MAX_THREAD_NUMS 4
#define DEFAULT_CACHED_QUEUE_NUMS 32    

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   Mutex taskMutex,
                                                                   CacheThreadManager manager, 
                                                                   long timeout)
                                                                         :mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         mTaskMutex(taskMutex),
                                                                         mCacheManager(manager){
    mWaitCond = createCondition();

    mTaskWaitMutex = createMutex();

    mTaskCondition = createCondition();
    
    mThreadTimeout = timeout;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    printf("_ThreadCachedPoolExecutorHandler release ,addr is %llx \n",this);
    mCurrentTask = nullptr;
    //printf("_ThreadCachedPoolExecutorHandler release ,mCacheManager count  is %d\n",mCacheManager->getStrongCount());
    mCacheManager.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    printf("_ThreadCachedPoolExecutorHandler start call quit \n");
    quit();
}

void _ThreadCachedPoolExecutorHandler::doTask(FutureTask task) {
    mCurrentTask = task;
    mTaskCondition->notify();
}

void _ThreadCachedPoolExecutorHandler::run() {
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);

    while(!mStop) {
        //long start = st(System)::currentTimeMillis();

        //printf("cached pool current time is %ld,mThreadTimeout is %ld\n",st(System)::currentTimeMillis(),mThreadTimeout);

        {
            AutoMutex ll(mTaskWaitMutex);
            if(mCurrentTask == nullptr) {
                //printf("start wait \n");
                mCacheManager->idleNotify(h);

                int result = mTaskCondition->wait(mTaskWaitMutex,mThreadTimeout);
                if(result == NotifyByTimeout) {
                    goto end;
                }
            }
        }

        mCacheManager->busyNotify(h);
        
        if(mCurrentTask != nullptr) {
            if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
                mCurrentTask = nullptr;
                continue;
            }

            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                printf("_ThreadCachedPoolExecutorHandler start run1 \n");
                r->run();
                printf("_ThreadCachedPoolExecutorHandler start run2 \n");
            }

            mCurrentTask = nullptr;
        }

        //start stealing
        {
            AutoMutex ll(mTaskMutex);
            if(mPool->size() != 0) {
                mCurrentTask = mPool->deQueueFirst();
            }
        }
    }
        

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    printf("thread complete %llx \n",this);
    mCacheManager->completeNotify(h);
    mCacheManager.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    printf("ThreadCachedPoolExecutorHandler onInterrupt \n");
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }

        mCurrentTask = nullptr;
    }

    state = terminateState;

    //printf("ThreadCachedPoolExecutorHandler onInterrupt2 \n");
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);
    mCacheManager->completeNotify(h);
    mCacheManager.remove_pointer();
}

bool _ThreadCachedPoolExecutorHandler::shutdownTask(FutureTask task) {
    printf("shutdown task \n");
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        printf("shutdown task trace1 \n");
        stop();
        return true;
    }

    return false;
}

bool _ThreadCachedPoolExecutorHandler::isTerminated() {
    return state == terminateState;
}

//---------------ThreadCachedPoolExecutor ---------------------
_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    init(queuesize,minthreadnum,maxthreadnum,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int maxthreadnum,long timeout) {
    init(-1,0,maxthreadnum,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor() {
    init(-1,0,DEFAULT_CACHED_MAX_THREAD_NUMS,DEFAULT_CACHED_THREAD_WAIT_TIME);
}

int _ThreadCachedPoolExecutor::shutdown(){
    printf("thread cached pool executor shutdown start\n");
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    mCacheManager->release();
    printf("thread cached pool executor shutdown end \n");
    return 0;
}

int _ThreadCachedPoolExecutor::execute(Runnable r) {
    
    if(submit(r) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

bool _ThreadCachedPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return false;
}

int _ThreadCachedPoolExecutor::awaitTermination() {
    return awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }
    //printf("start1 awaittermination %ld \n",st(System)::currentTimeMillis());
    if(mCacheManager->awaitTermination(millseconds) == NotifyByTimeout) {
        return -WaitTimeout;
    }
    //printf("start2 awaittermination %ld \n",st(System)::currentTimeMillis());
 
    mIsTerminated = true;
    return 0;
}

int _ThreadCachedPoolExecutor::getThreadsNum() {
    int size = mCacheManager->getThreadSum();
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    Future future = createFuture(task);
    
    mCacheManager->bindTask(task);

    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        throw createInitializeException(createString("ThreadCachedPool"));
    }

    mProtectMutex = createMutex("ThreadCachedMutex");
    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;
    mIsTerminated = false;
    mIsShutDown = false;
    
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");

    mCacheManager = createCacheThreadManager(queuesize,minthreadnum,maxthreadnum,mThreadTimeout);
}

bool _ThreadCachedPoolExecutor::isOverMinSize() {
    return mHandlers->size() > minThreadNum;
}

void _ThreadCachedPoolExecutor::onCancel(FutureTask task) {
    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    if(mCacheManager != nullptr) {
        mCacheManager->cancelTask(task);
    }
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    printf("release thread pool \n");
    //shutdown();
    if(!mIsShutDown) {
        throw createExecutorDestructorException("ThreadCachedPoolExecutor destruct error");
    }
}


//------------------CacheThreadManager------------------
_CacheThreadManager::_CacheThreadManager(int queueSize,int minThreadNum,int maxThreadNum,int waitTimeout) {

    mQueuesize = queueSize;

    mMinThreadNum = minThreadNum;

    mMaxThreadNum = maxThreadNum;

    mWaitTimeout = waitTimeout;

    if(mQueuesize == -1) {
        mFutureTasks = createBlockingQueue<FutureTask>();
    } else {
        mFutureTasks = createBlockingQueue<FutureTask>(queueSize);
    }

    mIdleHandlerMutex = createMutex("CacheIdleHandlerMutex");

    mRunningHandlerMutex = createMutex("CacheRunningHandlerMutex");

    mFutureTaskMutex = createMutex("FutureTaskMutex");

    mWaitTermMutex = createMutex("WaitTermMutex");

    mWaitTermCond = createCondition();

    mIdleHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mRunningHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();
    
    //for(int count = 0;count <minThreadNum;count++) {
    //    CacheThreadManager m;
    //    m.set_pointer(this);

    //    ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
    //                mFutureTasks,
    //                mFutureTaskMutex,
    //                m,
    //                mWaitTimeout);
    //    handler->start();
    //    mIdleHandlers->add(handler); 
    //}

    //printf("m count is %d \n",m->getStrongCount());
}

_CacheThreadManager::_CacheThreadManager():_CacheThreadManager(-1,
                                                               0,
                                                               DEFAULT_CACHED_MAX_THREAD_NUMS,
                                                               DEFAULT_CACHED_THREAD_WAIT_TIME) {
    //TODO nothing
}

_CacheThreadManager::~_CacheThreadManager() {
    printf("=================== cacheThread manager release!!!!!!!!!!!!!!! ================ \n");
}

void _CacheThreadManager::bindTask(FutureTask task) {
    //printf("bindTask trace1 \n");
    {
        AutoMutex ll(mIdleHandlerMutex);
        if(mIdleHandlers->size() != 0) {
            //printf("bindTask trace2 \n");
            ThreadCachedPoolExecutorHandler handler = mIdleHandlers->remove(0);
            handler->doTask(task);
            return;
        } 
    }

    {
        int currentThreadNum = this->getThreadSum();
        //printf("bindTask trace3 currentThreadNum is %d \n",currentThreadNum);
        if(currentThreadNum < mMaxThreadNum) {
            CacheThreadManager m;
            m.set_pointer(this);
            ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mFutureTasks,
                    mFutureTaskMutex,
                    m,
                    mWaitTimeout);

            printf("create handler addr is %llx \n",handler.get_pointer());
            handler->start();
            handler->doTask(task);
            return;
        }
    }

    mFutureTasks->enQueueLast(task);
}

void _CacheThreadManager::idleNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoMutex ll(mRunningHandlerMutex);
        printf("idleNotify add idle handler : %llx \n",handler.get_pointer());
        mRunningHandlers->remove(handler);
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        printf("idleNotify add busy handler : %llx \n",handler.get_pointer());
        mIdleHandlers->add(handler);
    }
}

void _CacheThreadManager::busyNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoMutex ll(mIdleHandlerMutex);
        printf("busyNotify add idle handler : %llx \n",handler.get_pointer());
        mIdleHandlers->remove(handler);
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        printf("busyNotify add busy handler : %llx \n",handler.get_pointer());
        mRunningHandlers->add(handler);
    }
}

int _CacheThreadManager::awaitTermination(long timeout) {
    {
        AutoMutex ll(mRunningHandlerMutex);
        if(mRunningHandlers->size() == 0) {
            return NotifyByThread;
        }
    }

    AutoMutex ll(mWaitTermMutex);
    if(timeout == 0) {
        mWaitTermCond->wait(mWaitTermMutex);
    } else {
        if(NotifyByTimeout == mWaitTermCond->wait(mWaitTermMutex,timeout)) {
            return NotifyByTimeout;
        }
    }

    return NotifyByThread;
}

void _CacheThreadManager::completeNotify(ThreadCachedPoolExecutorHandler h) {

    printf("completeNotify thread finish addr is %llx \n",h.get_pointer());

    {
        AutoMutex ll(mIdleHandlerMutex);
        if(mIdleHandlers->remove(h) > 0) {
            printf("complete notify1 \n");
            return;
        }
    }

    {
        AutoMutex ll(mRunningHandlerMutex);

        printf("complete notify2 size is %d,h count is %d \n",mRunningHandlers->size(),h->getStrongCount());

        int ret = mRunningHandlers->remove(h);
        printf("complete notify3 ret is %d,size is %d,h count is %d \n",ret,mRunningHandlers->size(),h->getStrongCount());

        if(mRunningHandlers->size() == 0) {
            mWaitTermCond->notifyAll();
        }
    }

    printf("my count is %d \n",this->getStrongCount());
}

void _CacheThreadManager::release() {
    printf("_cacheThreadmanager release \n");
    {
        AutoMutex ll(mRunningHandlerMutex);
        printf("_cacheThreadmanager release_0 \n");
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        printf("_cacheThreadmanager release_1 \n");
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            printf("cached manager stop addr is %llx \n",h.get_pointer());
            h->stop();
            
            list->next();
        }
        printf("_cacheThreadmanager release_2 \n");

        //mRunningHandlers->clear();
    }
    printf("_cacheThreadmanager release_1 \n");
    {
        AutoMutex ll(mIdleHandlerMutex);
        //mIdleHandlers->add(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mIdleHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }

        //mIdleHandlers->clear();
    }
    printf("_cacheThreadmanager release_2 \n");
    //wangsl
    //{
    //    AutoMutex ll(mFutureTaskMutex);
    //    while(mFutureTasks->size() != 0) {
    //        FutureTask removeTask = mFutureTasks->deQueueLast();
    //        Runnable r = removeTask->getRunnable();
    //        if(r != nullptr) {
    //            r->onInterrupt();
    //        }
    //    }
    //}
    //wangsl
}

int _CacheThreadManager::getThreadSum() {
    int sum = 0;
    {
        AutoMutex ll(mRunningHandlerMutex);
        sum += mRunningHandlers->size();
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        sum += mIdleHandlers->size();
    }

    return sum;
}

void _CacheThreadManager::cancelTask(FutureTask task) {
    printf("remove task trace1 \n");
    if(mFutureTasks->remove(task)) {
        printf("remove task trace2 \n");
        return;
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        ThreadCachedPoolExecutorHandler h = nullptr;
        while(list->hasValue()) {
            h = list->getValue();
            printf("remove task trace3 \n");
            if(h->shutdownTask(task)) {
                break;
            }
            list->next();
        }
    }
}


}
