#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "ThreadLocal.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

//------------ReleaseThread-----------------
static void* freethreadmem(void *th) {
    _ReleaseThread *thread = static_cast<_ReleaseThread *>(th);
    thread->run();
    return nullptr;
}

_ReleaseThread::_ReleaseThread() {
    mutex = createMutex("ReleaseThreadMutex");

    cond = createCondition();

    mThreadPids = createArrayList<Uint64>();

    mStartBarrier = createAtomicInteger(0);

    mTid = 0;
}

_ReleaseThread::~_ReleaseThread() {
    //printf("_ReleaseThread release \n");
    //Uint64 poison;
    //mThreadPids->add(poison);
    //pthread_join(mTid,nullptr);
    stop();
}

void _ReleaseThread::stop() {
    Uint64 poison;
    //printf("release thread start \n");
    sendRelease(poison);
    //printf("release thread trace \n");
    pthread_join(mTid,nullptr);
    //printf("release thread trace2 \n");
}

void _ReleaseThread::sendRelease(Uint64 t) {
    AutoMutex ll(mutex);
    mThreadPids->add(t);
    cond->notify();
}

void _ReleaseThread::start() {

    AutoMutex l(mutex);
    pthread_attr_init(&mAttr);
    pthread_create(&mTid, &mAttr, freethreadmem, this);
        
    while(mStartBarrier->orAndGet(0) == 0) {
        //wait
    }
}


void _ReleaseThread::run() {
    mStartBarrier->orAndGet(1);

    while(1) {
        Uint64 tid = nullptr;

        {   
            //printf("_ReleaseThread run1 \n");
            AutoMutex ll(mutex);
            int size = mThreadPids->size();
            if(size == 0) {
                cond->wait(mutex);
                continue;
            }
            tid = mThreadPids->remove(0);
            if(tid == nullptr) {
                break;
            }
        }

        long time = st(System)::currentTimeMillis();
        pthread_join(tid->toValue(),nullptr);
        //printf("release join is %ld \n",st(System)::currentTimeMillis() - time);
    }
}

//------------KeepAliveThread---------------//
static void* recycle(void *th) {
    ////printf("recyle 1 \n");
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    _KeepAliveThread *thread = static_cast<_KeepAliveThread *>(th);
    ////printf("recyle 2 \n");
    thread->run();
    ////printf("recyle 3 \n");
    return nullptr;
}

_KeepAliveThread::_KeepAliveThread() {
    mutex = createMutex("RecyleThreadMutex");
    queue = createBlockingQueue<Uint64>();
    isRunning = false;
    mThreadLocal = createThreadLocal<sp<_Thread>>();
    mStartBarrier = createAtomicInteger(0);
    mReleaseThread = createReleaseThread();
}

void _KeepAliveThread::start() {
    if(isRunning) {
        return;
    }

    AutoMutex l(mutex);
    if(!isRunning) {
        mReleaseThread->start();

        pthread_attr_init(&mAttr);
        pthread_create(&mTid, &mAttr, recycle, this);
        
        while(mStartBarrier->orAndGet(0) == 0) {
            //wait
        }
        isRunning = true;
    }
}

void _KeepAliveThread::run() {
    ////printf("keep alive trace \n");
    ThreadLocal<Thread> tLocal = mThreadLocal;
    BlockingQueue<Uint64> mQueue = queue;
    mStartBarrier->orAndGet(1);
    while(1) {
        ////printf("keep alive trace2\n");
        Uint64 t = mQueue->deQueueFirst();
        ////printf("keep alive trace3 \n");
        if(t == nullptr) {
            return;
        }
        mReleaseThread->sendRelease(t);
        ////printf("keep alive trace4 \n");
        tLocal->remove(t->toValue());
        ////printf("keep alive trace5 \n");
    }
}

void _KeepAliveThread::save(sp<_Thread> s) {
    mThreadLocal->set(s->mPthread,s);
}

sp<_Thread> _KeepAliveThread::getSavedThread() {
    return mThreadLocal->get();
}

void _KeepAliveThread::drop(pthread_t t){
    queue->enQueueLast(createUint64(t));
}

_KeepAliveThread::~_KeepAliveThread() {
    ////printf("~keepalivethread 1 \n");
    mThreadLocal->clear();
    ////printf("~keepalivethread 2 \n");
    queue->destroy();

    mReleaseThread->stop();
    ////printf("~keepalivethread 3 \n");
    //pthread_cancel(mTid);
    ////printf("~keepalivethread 4 \n");
}

//------------Thread Stack function---------------//
void cleanup(void *th) {
    //printf("onInterrupt \n");
    _Thread *thread = static_cast<_Thread *>(th);
    if(thread->getRunnable() != nullptr) {
        //printf("onInterrupt 1\n");
        thread->getRunnable()->onInterrupt();
    } else {
        //printf("onInterrupt 2\n");
        thread->onInterrupt();
    }
    thread->mStatus = ThreadComplete;
    _Thread::getKeepAliveThread()->drop(thread->mPthread);
}

//------------Thread---------------//
KeepAliveThread _Thread::mKeepAliveThread = createKeepAliveThread();
HashMap<int,int *> _Thread::mPriorityTable = createHashMap<int,int *>();

void* _Thread::localRun(void *th) {
    //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, nullptr);
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    _Thread *thread = static_cast<_Thread *>(th);
    //printf("localRun \n");
    KeepAliveThread mKAThread = mKeepAliveThread; 
    sp<_Thread> localThread;
    localThread.set_pointer(thread);
    mKeepAliveThread->save(localThread);
    thread->mStatus = ThreadRunning;
    thread->bootFlag->orAndGet(1);
    
    pthread_cleanup_push(cleanup, th);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    if(thread->mStatus == ThreadWaitExit) {
        ////printf("go to exit \n");
        goto end;
    }
    //pthread_testcancel();
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);

    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);
    thread->initPolicyAndPriority();
    thread->setSchedPolicy(thread->mPolicy);
    thread->setPriority(thread->mPriority);
    if(thread->mName != nullptr) {
        pthread_setname_np(thread->mPthread,thread->mName->toChars());
    }
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);

    if(thread->mRunnable != nullptr) {
        thread->mRunnable->run();
        thread->mRunnable = nullptr;
    } else {
        ////printf("localRun1 \n");
        thread->run();
    }
    
end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    pthread_cleanup_pop(0);
    //printf("local complete \n");
    thread->mStatus = ThreadComplete;

    mKAThread->drop(localThread->mPthread);
    localThread.remove_pointer();
    return nullptr;
}


_Thread::_Thread():_Thread(nullptr,nullptr) {
}

_Thread::_Thread(Runnable run):_Thread{nullptr,run} {
}

_Thread::_Thread(String name,Runnable run){
    if(name != nullptr) {
        mName = name;    
    }
    
    if(run != nullptr) {
        mRunnable = run;
    }

    mKeepAliveThread->start();
    
    mPolicy = ThreadSchedOTHER;
    mPriority = ThreadLowPriority;
    mStatus = ThreadNotStart;
    bootFlag = createAtomicInteger(0);
    mProtectMutex = createMutex("ThreadProtectMutex");

}

int _Thread::setName(String name) {
    switch(mStatus) {
        case ThreadIdle:
        case ThreadNotStart:
            return -NotStart;

        case ThreadComplete:
            return -AlreadyComplete;
    }

    mName = name;
    return pthread_setname_np(mPthread,name->toChars());
}

String _Thread::getName() {
    return mName;
}

_Thread::~_Thread(){
    this->quit();
}

Runnable _Thread::getRunnable() {
    return mRunnable;
}

void _Thread::run() {
    //child thread can overwrite it.
}                                                                                                    

int _Thread::start() {
    //pthread_create(&mPthread, &mThreadAttr, localRun, this);
    //if we use sp or declare a thread on stack
    //eg.
    //{
    //   Thread t1 = new Thread(new Runnable(setThreadSchedPolicy) {xxxxxx});
    //   t1->start();
    //}
    //when we leave the life circle,the thread is still running
    //the release may cause the corruption.
    //we should incStrong.after the thread complete,
    //we force decStrong to release;
    //incStrong(0);
    //sp<_Thread> localThread;
    //localThread.set_pointer(this);
    if(mStatus != ThreadNotStart) {
        return -AlreadyExecute;
    }

    AutoMutex l(mProtectMutex);

    if(mStatus != ThreadNotStart) {
        return -AlreadyExecute;
    }

    mStatus = ThreadIdle;
    pthread_attr_init(&mThreadAttr);
    pthread_create(&mPthread, &mThreadAttr, localRun, this);
    while(bootFlag->orAndGet(0) == 0) {
        st(Thread)::yield();
    }
    return 0;
}

void _Thread::initPolicyAndPriority() {
    int policy = ThreadSchedOTHER;
    pthread_attr_getschedpolicy(&mThreadAttr,&policy);
    updateThreadPrioTable(policy);
}

void _Thread::join() {
    pthread_join(mPthread,(void **) nullptr);
}

void _Thread::join(long timeInterval) {
    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    pthread_timedjoin_np(mPthread,nullptr,&ts);
}

int _Thread::getStatus() {
    return mStatus;
}

void _Thread::quit() {
    //printf("thread exit start,status is %d  \n",mStatus);
    if(mStatus == ThreadComplete||mStatus == ThreadNotStart||mStatus == ThreadWaitExit) {
        return;
    }
    //printf("thread exit \n");
    AutoMutex l(mProtectMutex);
    //printf("thread exit1 \n");
    if(mStatus == ThreadComplete||mStatus == ThreadNotStart) {
        mStatus = ThreadComplete;
        return;
    }else if(mStatus == ThreadWaitExit) {
        return;
    }
    ////printf("thread exit2 \n");
    if(mStatus == ThreadIdle) {
        mStatus = ThreadWaitExit;
        while(1) {
            join(100);
            if(mStatus == ThreadRunning) {
                //printf("thread exit3 \n");
                pthread_cancel(mPthread);
                //mStatus = ThreadComplete;
                return;
            } else if(mStatus == ThreadComplete) {
                return;
            }
        }
        
        return;
    }
    //printf("thread exit4 \n");
    mStatus = ThreadComplete;
    int ret = pthread_cancel(mPthread);
    //printf("pthread cancel ret is %d,mPthread is %x \n",ret,mPthread);
    //ret = pthread_join(mPthread,nullptr);
    //////printf("pthread2 cancel ret is %d,mPthread is %x \n",ret,mPthread);
}

int _Thread::setPriority(ThreadPriority priority) {
    switch(mStatus) {
        case ThreadIdle:
        case ThreadNotStart:
            return -NotStart;

        case ThreadComplete:
            return -AlreadyComplete;
    }

    if(mPolicy == ThreadSchedPolicy::ThreadSchedOTHER) {
        return -NotSupport;
    }
    
    mPriority = priority;
    
    int schedPrio = mPriorityTable->get(mPolicy)[priority];
    struct sched_param param;
    pthread_attr_getschedparam(&mThreadAttr, &param);

    param.sched_priority = schedPrio;
    return pthread_attr_setschedparam(&mThreadAttr, &param);
}

int _Thread::getPriority() {
    struct sched_param param;
    if(mStatus != ThreadRunning) {
        return -NotStart;
    }

    int rs = pthread_attr_getschedparam(&mThreadAttr, &param);
    if(rs == 0) {
        return SchePrio2threadPrio(param.__sched_priority);
    }

    return -1;
}

int _Thread::setSchedPolicy(ThreadSchedPolicy policy) {
    
    switch(mStatus) {
        case ThreadIdle:
        case ThreadNotStart:
            return -NotStart;

        case ThreadComplete:
            return -AlreadyComplete;
    }

    if(policy != ThreadSchedOTHER
        &&policy != ThreadSchedFIFO
        &&policy != ThreadSchedRR) {
        return -NotSupport;
    }

    int rs = pthread_attr_setschedpolicy(&mThreadAttr, policy);
    if(rs != 0) {
        return -1;
    }

    mPolicy = policy;
    updateThreadPrioTable(policy);
    if(rs == 0) {
        return 0;
    }

    return -1;

}

int _Thread::getSchedPolicy() {
    if(mStatus != ThreadRunning) {
        return -NotStart;
    }

    int policy = ThreadSchedOTHER;
    int rs = pthread_attr_getschedpolicy(&mThreadAttr, &policy);
    if(rs != 0) {
        return -1;
    }
    return policy;
}

void _Thread::onInterrupt() {
    //need overwrite by child class
    ////printf("thread onInterrupt !!!!!!\n");
}

void _Thread::interruptCheck() {
    pthread_testcancel();
}

void _Thread::yield() {
    pthread_yield();
}

void _Thread::msleep(unsigned long t) {
    usleep(t*1000);
}

int _Thread::threadPrio2SchePrio(int threadprio) {
    return mPriorityTable->get(mPolicy)[threadprio];
}

int _Thread::SchePrio2threadPrio(int schedPrio) {
    int index = ThreadLowestPriority;
    int *table = mPriorityTable->get(mPolicy);

    for(;index < ThreadPriorityMax;index++) {
        if(table[index] >= schedPrio) {
            break;
        }
    }

    if(index == 0) {
        return ThreadLowestPriority;
    }

    return index--;
}

int _Thread::updateThreadPrioTable(int policy) {

    int *table = mPriorityTable->get(policy);
    if(table != nullptr) {
        return 0;
    }

    int maxPrio = sched_get_priority_max (policy);
    int minPrio = sched_get_priority_min (policy);
    
    table = new int[ThreadPriorityMax];
   
    int interval = (maxPrio - minPrio)/ThreadHighestPriority;
    for(int i = ThreadLowestPriority;i < ThreadPriorityMax-1;i++) {
        table[i] = (minPrio/10)*10;
        minPrio += interval;
    }

    table[ThreadHighestPriority] = maxPrio;
    mPriorityTable->put(policy,table);
    return 0;
}

void _Thread::setThreadPriority(ThreadPriority priority) {
    Thread thread = mKeepAliveThread->getSavedThread();
    if(thread != nullptr) {
        thread->setPriority(priority);
    }
}

int _Thread::getThreadPriority() {
    Thread thread = mKeepAliveThread->getSavedThread();
    if(thread != nullptr) {
        return thread->getPriority();
    }

    return -1;
}

int _Thread::setThreadSchedPolicy(ThreadSchedPolicy policy) {
    Thread thread = mKeepAliveThread->getSavedThread();
    if(thread != nullptr) {
        return thread->setSchedPolicy(policy);
    }
    return -1;
}

int _Thread::getThreadSchedPolicy() {
    Thread thread = mKeepAliveThread->getSavedThread();
    if(thread != nullptr) {
        return thread->getSchedPolicy();
    }
    return -1;
}

KeepAliveThread _Thread::getKeepAliveThread(){
    return mKeepAliveThread;
}

}
