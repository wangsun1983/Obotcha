#include <stdio.h>
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

    isNotifed = false;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    //printf("_ThreadCachedPoolExecutorHandler release ,addr is %llx \n",this);
    mCurrentTask = nullptr;
    ////printf("_ThreadCachedPoolExecutorHandler release ,mCacheManager count  is %d\n",mCacheManager->getStrongCount());
    mCacheManager.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    //printf("_ThreadCachedPoolExecutorHandler start call quit \n");
    quit();
}

void _ThreadCachedPoolExecutorHandler::doTask(FutureTask task) {
    mCurrentTask = task;
    isNotifed = true;
    mTaskCondition->notify();
}

void _ThreadCachedPoolExecutorHandler::run() {
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);

    while(!mStop) {
        //long start = st(System)::currentTimeMillis();

        ////printf("cached pool current time is %ld,mThreadTimeout is %ld\n",st(System)::currentTimeMillis(),mThreadTimeout);
        {
            AutoMutex ll(mTaskWaitMutex);
            if(mCurrentTask == nullptr) {
                ////printf("start wait \n");

                if(mCacheManager->idleNotify(h) != CachedNotifySuccess) {
                    goto end;
                }

                int result = mTaskCondition->wait(mTaskWaitMutex,mThreadTimeout);
                if(result == NotifyByTimeout) {
                    goto end;
                }
                isNotifed = true;
            }
        }

        if(isNotifed) {
            if(mCacheManager->busyNotify(h)) {                
                goto end;
            }
        }
        
        
        if(mCurrentTask != nullptr) {
            if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
                mCurrentTask = nullptr;
                continue;
            }

            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                ////printf("_ThreadCachedPoolExecutorHandler start run1 \n");
                r->run();
                ////printf("_ThreadCachedPoolExecutorHandler start run2 \n");
            }

            mCurrentTask->onComplete();
            mCurrentTask = nullptr;

        }

        //start stealing
        {
            AutoMutex ll(mTaskMutex);
            if(mPool->size() != 0) {
                mCurrentTask = mPool->deQueueFirst();
                isNotifed = false;
            }
        }
    }
        

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    //printf("thread complete %llx \n",this);
    if(mCacheManager != nullptr) {
        mCacheManager->completeNotify(h);
        mCacheManager.remove_pointer();
    }
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    //printf("ThreadCachedPoolExecutorHandler onInterrupt \n");
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        //printf("ThreadCachedPoolExecutorHandler onInterrupt,call interrupt r is %llx \n",r.get_pointer());
        if(r != nullptr) {
            r->onInterrupt();
        }

        mCurrentTask = nullptr;
    }

    state = terminateState;

    ////printf("ThreadCachedPoolExecutorHandler onInterrupt2 \n");
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);
    mCacheManager->completeNotify(h);
    mCacheManager.remove_pointer();
}

bool _ThreadCachedPoolExecutorHandler::shutdownTask(FutureTask task) {
    //printf("shutdown task \n");
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        //printf("shutdown task trace1 \n");
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
    //printf("thread cached pool executor shutdown start\n");
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    mCacheManager->release();
    //printf("thread cached pool executor shutdown end,thread sum is %d \n",mCacheManager->getThreadSum());
    if(mCacheManager->getThreadSum() != 0) {
        //mCacheManager.remove_pointer();
    } else {
        mCacheManager->removeExecutor();
    }

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
    return mCacheManager->isTerminated();
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
    return size;
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }
    //printf("submit1 this count is %d \n",this->getStrongCount());
    FutureTaskStatusListener listener;
    listener.set_pointer(this);
    //printf("submit2 this count is %d \n",this->getStrongCount());
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    //printf("submit3 this count is %d \n",this->getStrongCount());
    Future future = createFuture(task);
    //printf("submit4 this count is %d \n",this->getStrongCount());
    
    mCacheManager->bindTask(task);
    //printf("submit5 this count is %d \n",this->getStrongCount());

    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        throw InitializeException(createString("ThreadCachedPool"));
    }

    mProtectMutex = createMutex("ThreadCachedMutex");
    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;
    mIsTerminated = false;
    mIsShutDown = false;
    
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");

    ThreadCachedPoolExecutor t;
    t.set_pointer(this);
    mCacheManager = createCacheThreadManager(queuesize,minthreadnum,maxthreadnum,mThreadTimeout,t);
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
    //printf("release thread pool \n");
    //shutdown();
    if(!mIsShutDown) {
        throw ExecutorDestructorException("ThreadCachedPoolExecutor destruct error");
    }
}


//------------------CacheThreadManager------------------
_CacheThreadManager::_CacheThreadManager(int queueSize,int minThreadNum,int maxThreadNum,int waitTimeout,ThreadCachedPoolExecutor executor) {

    mQueuesize = queueSize;

    mMinThreadNum = minThreadNum;

    mMaxThreadNum = maxThreadNum;

    mWaitTimeout = waitTimeout;

    mIsTerminated = false;

    if(mQueuesize == -1) {
        mFutureTasks = createBlockingQueue<FutureTask>();
    } else {
        mFutureTasks = createBlockingQueue<FutureTask>(queueSize);
    }

    mIdleHandlerMutex = createMutex("CacheIdleHandlerMutex");

    mRunningHandlerMutex = createMutex("CacheRunningHandlerMutex");

    mFutureTaskMutex = createMutex("FutureTaskMutex");

    mWaitTermMutex = createMutex("WaitTermMutex");

    mCompleteNotifyMutex = createMutex("CompleteNotifyMutex");

    mWaitTermCond = createCondition();

    mIdleHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mRunningHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mCreatingHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();
    mCreatingHandlerMutex = createMutex("creatingMutex");

    mReleaseMutex = createMutex("CacheThreadReleaseMutex");
    mIsRelease = false;

    mExecutor = executor;
    
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

    ////printf("m count is %d \n",m->getStrongCount());
}

_CacheThreadManager::_CacheThreadManager():_CacheThreadManager(-1,
                                                               0,
                                                               DEFAULT_CACHED_MAX_THREAD_NUMS,
                                                               DEFAULT_CACHED_THREAD_WAIT_TIME,
                                                               nullptr) {
    //TODO nothing
}

_CacheThreadManager::~_CacheThreadManager() {
    //printf("=================== cacheThread manager release!!!!!!!!!!!!!!! ================ \n");
}

void _CacheThreadManager::bindTask(FutureTask task) {

    //check wether
    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return;
        }
    }
    
    //printf("bindTask mIdleHandlers->size() is %d \n",mIdleHandlers->size());
    {
        AutoMutex ll(mIdleHandlerMutex);
        if(mIdleHandlers->size() != 0) {
            //printf("bindTask trace2 \n");
            ThreadCachedPoolExecutorHandler handler = mIdleHandlers->removeAt(0);
            handler->doTask(task);
            return;
        } 
    }

    {
        int currentThreadNum = this->getThreadSum();
        //printf("bindTask trace3 currentThreadNum is %d,mMaxThreadNum is %d \n",currentThreadNum,mMaxThreadNum);
        AutoMutex ll(mRunningHandlerMutex);
        
        if(currentThreadNum < mMaxThreadNum) {
            CacheThreadManager m;
            m.set_pointer(this);
            ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mFutureTasks,
                    mFutureTaskMutex,
                    m,
                    mWaitTimeout);
            {
                AutoMutex ll2(mCreatingHandlerMutex);
                mCreatingHandlers->add(handler);
            }

            handler->doTask(task);
            ////printf("create handler addr is %llx \n",handler.get_pointer());
            handler->start();

            return;
        }
    }
    
    mFutureTasks->enQueueLast(task);
}

int _CacheThreadManager::idleNotify(ThreadCachedPoolExecutorHandler handler) {

    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return CachedNotifyFailAlreadyRelease;
        }
    }

    {
        AutoMutex ll(mCreatingHandlerMutex);
        //printf("idleNotify add creating handler : %llx \n",handler.get_pointer());
        mCreatingHandlers->remove(handler);
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //printf("idleNotify add idle handler : %llx \n",handler.get_pointer());
        mRunningHandlers->remove(handler);
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        //printf("idleNotify add busy handler : %llx \n",handler.get_pointer());
        mIdleHandlers->add(handler);
    }

    return 0;
}

int _CacheThreadManager::busyNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return CachedNotifyFailAlreadyRelease;
        }
    }

    {
        AutoMutex ll(mCreatingHandlerMutex);
        //printf("busyNotify add creating handler : %llx \n",handler.get_pointer());
        mCreatingHandlers->remove(handler);
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        //printf("busyNotify add idle handler : %llx \n",handler.get_pointer());
        mIdleHandlers->remove(handler);
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //printf("busyNotify add busy handler : %llx \n",handler.get_pointer());
        mRunningHandlers->add(handler);
    }
}

bool _CacheThreadManager::isTerminated() {
    return mIsTerminated;
}

int _CacheThreadManager::awaitTermination(long timeout) {
    //printf("CacheThreadManager start await Termination start \n");
    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease && getThreadSum() == 0) {
            return NotifyByThread;
        }
    }

    //printf("CacheThreadManager start await Termination trace1 \n");
    AutoMutex ll(mWaitTermMutex);
    if(mIsTerminated) {
        return NotifyByThread;
    }
    //printf("CacheThreadManager start await Termination trace2 \n");
    
    if(NotifyByTimeout == mWaitTermCond->wait(mWaitTermMutex,timeout)) {
        return NotifyByTimeout;
    }
    
    //printf("CacheThreadManager start await Termination trace3 \n");
    return NotifyByThread;
}

void _CacheThreadManager::completeNotify(ThreadCachedPoolExecutorHandler h) {
    //printf("completeNotify thread finish addr is %llx \n",h.get_pointer());

    int removeCreatingResult = -1;
    int removeIdleResult = -1;
    int removeRunningResult = -1;
    {
        AutoMutex ll(mCreatingHandlerMutex);
        removeCreatingResult = mCreatingHandlers->remove(h);
        //printf("removeCreatingResult is %d \n",removeCreatingResult);
        if(removeCreatingResult >= 0) {
            goto end;
        }
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        removeIdleResult = mIdleHandlers->remove(h);
        //printf("removeIdleResult is %d \n",removeIdleResult);
        if(removeIdleResult >= 0) {
            goto end;
        }
    }

    {
        AutoMutex ll(mRunningHandlerMutex);

        //printf("complete notify2 size is %d,h count is %d \n",mRunningHandlers->size(),h->getStrongCount());

        removeRunningResult = mRunningHandlers->remove(h);
        //printf("complete notify3 ret is %d,size is %d,h count is %d \n",removeRunningResult,mRunningHandlers->size(),h->getStrongCount());
        if(removeRunningResult >= 0) {
            //{
            //    AutoMutex ll(mWaitTermMutex);
            //    mIsTerminated->set(true);
            //    mWaitTermCond->notifyAll();
            //}

            //mExecutor->finishWaitTerminate();
            //mExecutor.remove_pointer();
            goto end;
        }
    }

    goto exit;

end:
    if(getThreadSum() == 0) {
        //printf("complete notify remove pointer \n");
        if(mIsTerminated) {
            goto exit;
        }

        AutoMutex ll(mCompleteNotifyMutex);
        if(mIsTerminated) {
            goto exit;
        }

        //printf("complete notify remove executor pointer \n");
        if(mIsRelease) {
            mIsTerminated = true;
            mWaitTermCond->notifyAll();
            if(mExecutor != nullptr) {
                //mExecutor->finishWaitTerminate();
                mExecutor.remove_pointer();
            }
        }
    }

exit:
    //printf("my count is %d \n",this->getStrongCount());
    return;
}

void _CacheThreadManager::release() {
    //printf("_cacheThreadmanager release \n");
    if(mIsRelease) {
        return;
    }

    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return;
        }

        mIsRelease = true;
    }

    //mFutureTasks->clear();

    {
        AutoMutex ll(mCreatingHandlerMutex);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mCreatingHandlers->getIterator();
        //printf("_cacheThreadmanager release_0,creating size is %d \n",mCreatingHandlers->size());
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            //printf("cached manager stop creating thread is %llx \n",h.get_pointer());
            h->stop();
            list->next();
        }
        //printf("_cacheThreadmanager release_0_2 \n");
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //printf("_cacheThreadmanager release_0 \n");
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        //printf("_cacheThreadmanager release_1,running size is %d \n",mRunningHandlers->size());
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            //printf("cached manager stop addr is %llx \n",h.get_pointer());
            h->stop();
            list->next();
        }
        //printf("_cacheThreadmanager release_2 \n");

        //mRunningHandlers->clear();
    }
    //printf("_cacheThreadmanager release_1,remove idle task \n");
    {
        AutoMutex ll(mIdleHandlerMutex);
        //mIdleHandlers->add(handler);
        //printf("_cacheThreadmanager release_1,idle size is %d \n",mIdleHandlers->size());
        ListIterator<ThreadCachedPoolExecutorHandler> list = mIdleHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }

        //mIdleHandlers->clear();
    }
    //printf("_cacheThreadmanager release_2 complete\n");
    //wangsl
    {
        AutoMutex ll(mFutureTaskMutex);
        while(mFutureTasks->size() != 0) {
            FutureTask removeTask = mFutureTasks->deQueueLast();
            Runnable r = removeTask->getRunnable();
            if(r != nullptr) {
                r->onInterrupt();
            }
        }
        //printf("release mFutureTasks size is %d \n",mFutureTasks->size());
    }
    //wangsl
}

void _CacheThreadManager::removeExecutor() {
    if(mExecutor != nullptr) {
        mExecutor.remove_pointer();
    }
}

int _CacheThreadManager::getThreadSum() {
    int sum = 0;
    {
        AutoMutex ll0(mCreatingHandlerMutex);
        AutoMutex ll1(mIdleHandlerMutex);
        AutoMutex ll2(mRunningHandlerMutex);
        sum += mCreatingHandlers->size(); 
        sum += mRunningHandlers->size();
        //printf("calc mRunningHandlers->size() is %d \n",mRunningHandlers->size());
        sum += mIdleHandlers->size();
        //printf("calc mIdleHandlers->size() is %d \n",mIdleHandlers->size());
    }

    return sum;
}

void _CacheThreadManager::cancelTask(FutureTask task) {
    //printf("remove task trace1 \n");
    if(mFutureTasks->remove(task)) {
        //printf("remove task trace2 \n");
        return;
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        ThreadCachedPoolExecutorHandler h = nullptr;
        while(list->hasValue()) {
            h = list->getValue();
            //printf("remove task trace3 \n");
            if(h->shutdownTask(task)) {
                break;
            }
            list->next();
        }
    }
}


}
