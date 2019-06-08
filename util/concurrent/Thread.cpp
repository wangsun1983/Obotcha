#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "ThreadLocal.hpp"

namespace obotcha {

//------------KeepAliveThread---------------//
static void* recycle(void *th) {
    _KeepAliveThread *thread = static_cast<_KeepAliveThread *>(th);
    thread->run();
    return nullptr;
}

_KeepAliveThread::_KeepAliveThread() {
    printf("_RecycleThread start \n");
    mutex = createMutex("RecyleThreadMutex");
    cond = createCondition();
    queue = createBlockingQueue<Thread>();
    isRunning = false;
    mThreadLocal = createThreadLocal<sp<_Thread>>();
    //mDestroyMutex = createMutex("RecyleThreadMutex");
    mDestroyBarrier = 0;
}

void _KeepAliveThread::start() {
    printf("RecyleThread start \n");

    AutoMutex l(mutex);
    printf("RecyleThread start2 \n");
    if(!isRunning) {
        pthread_create(&mTid, &mAttr, recycle, this);
        isRunning = true;
    }
}

void _KeepAliveThread::run() {
    printf("RecyleThread run \n");
    //mDestroyMutex->lock();
    if(mDestroyBarrier == 1) {
        //mDestroyMutex->unlock();
        return;
    }

    ThreadLocal<Thread> tLocal = mThreadLocal;
    BlockingQueue<Thread> mQueue = queue;
    //mDestroyMutex->unlock();

    while(1) {
        Thread t = mQueue->deQueueFirst();
        printf("remove thread \n");
        //t->decStrong(0);
        //TODO
        //printf("remove thread 1,t count is %d, t addr is %x \n",t->getStrongCount(),t.get_pointer());
        if(t == nullptr) {
            return;
        }

        //st(Thread)::removeThread(t);
        //printf("remove thread 2,t count is %d, t addr is %x \n",t->getStrongCount(),t.get_pointer());
      
        //printf("remove thread 2,t count is %d \n",t->getStrongCount());
        tLocal->remove(t->mPthread);
    }
}

void _KeepAliveThread::save(sp<_Thread> s) {
    mThreadLocal->set(s->mPthread,s);
}

sp<_Thread> _KeepAliveThread::getSavedThread() {
    mThreadLocal->get();
}

void _KeepAliveThread::drop(Thread t){
    //printf("submit trace1,thread count is %d \n",t->getStrongCount());
    queue->enQueueLast(t);
    //printf("submit trace2,thread count is %d \n",t->getStrongCount());
}

_KeepAliveThread::~_KeepAliveThread() {
    //this->exit();
    //mDestroyMutex->lock();
    mDestroyBarrier = 1;
    //mDestroyMutex->unlock();

    pthread_cancel(mTid);
}

//------------Thread Stack function---------------//
static void cleanup(void *th)
{
    printf("clean up \n");
    _Thread *thread = static_cast<_Thread *>(th);
    thread->onInterrupt();
    if(thread->getRunnable() != nullptr) {
        thread->getRunnable()->onInterrupt();
    }

    Thread recyleTh;
    recyleTh.set_pointer(thread);

    _Thread::getKeepAliveThread()->drop(recyleTh);
}

//------------Thread---------------//
KeepAliveThread _Thread::mKeepAliveThread = createKeepAliveThread();
//ThreadLocal<Thread> _Thread::mLocalThreadLocal = createThreadLocal<Thread>();

void* _Thread::localRun(void *th) {
    _Thread *thread = static_cast<_Thread *>(th);

    KeepAliveThread mKAThread = mKeepAliveThread;
    //printf("localrun start ,thread count is %d \n",thread->getStrongCount());
    //put to mthread again
    sp<_Thread> localThread;
    localThread.set_pointer(thread);
    //mLocalThreadLocal->set(thread->mPthread,localThread);
    mKeepAliveThread->save(localThread);

    thread->initPolicyAndPriority();

    //setpriority
    thread->setSchedPolicy(thread->mPolicy);
    thread->setPriority(thread->mPriority);
    
    pthread_cleanup_push(cleanup, thread);
    if(thread->mRunnable != nullptr) {
        thread->mRunnable->run();
        thread->mRunnable = nullptr;
    } else {
        thread->run();
    }
    

    //printf("localrun trace1,thread count is %d \n",thread->getStrongCount());
    //Thread recyleTh;
    //recyleTh.set_pointer(thread);
    

    //printf("localrun trace2,thread count is %d \n",thread->getStrongCount());
    pthread_cleanup_pop(0);
    mKAThread->drop(localThread);

    return nullptr;
}

_Thread::_Thread(Runnable run) {
    mKeepAliveThread->start();
	mRunnable = run;
}

_Thread::_Thread(String name,Runnable run) {
    printf("thread create 1 \n");
    mName = name;
    printf("thread create 2 \n");
    mKeepAliveThread->start();
    printf("thread create 3 \n");
    mRunnable = run;
    printf("thread create 4 \n");
}

void _Thread::setName(String name) {
    mName = name;
    pthread_setname_np(mPthread,name->toChars());
}

String _Thread::getName() {
    return mName;
}

_Thread::_Thread() {
    //Nothing
    mPolicy = ThreadSchedOTHER;
    mPriority = ThreadLowPriority;
}

_Thread::~_Thread(){
    //Nothing
    //if(mName != nullptr) {
    //  printf("thread destroy name is %s \n",mName->toChars());    
    //} else{
    //  printf("thread destroy \n");  
    //}
}

Runnable _Thread::getRunnable() {
    return mRunnable;
}

void _Thread::run() {
    //child thread can overwrite it.
}																									

void _Thread::start() {
    //pthread_create(&mPthread, &mThreadAttr, localRun, this);
    //if we use sp or declare a thread on stack
    //eg.
    //{
    //   Thread t1 = new Thread(new Runnable() {xxxxxx});
    //   t1->start();
    //}
    //when we leave the life circle,the thread is still running
    //the release may cause the corruption.
    //we should incStrong.after the thread complete,
    //we force decStrong to release;
    //incStrong(0);
    //sp<_Thread> localThread;
    //localThread.set_pointer(this);
    
    pthread_attr_init(&mThreadAttr);
    pthread_create(&mPthread, &mThreadAttr, localRun, this);

    //mLocalThreadLocal->set(mPthread,localThread);
}

void _Thread::initPolicyAndPriority() {
    int policy = ThreadSchedOTHER;
    pthread_attr_getschedpolicy(&mThreadAttr,&policy);
    printf("mPolicy is %d \n",mPolicy);
    updateThreadPrioTable(policy);
}

void _Thread::join() {
	pthread_join(mPthread,(void **) nullptr);
}

void _Thread::join(long timeInterval) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;

    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);

    pthread_timedjoin_np(mPthread,nullptr,&ts);
}

int _Thread::getStatus() {
    int pthread_kill_err = 0;
    
    pthread_kill_err = pthread_kill(mPthread,0);
    if(pthread_kill_err == ESRCH) {
        return ThreadNotExist;
    }
    
    return ThreadRunning;
}


void _Thread::exit() {
    pthread_cancel(mPthread);
}

int _Thread::setPriority(ThreadPriority priority) {
    mPriority = priority;
    
    int schedPrio = mPrioTable[priority];
    printf("setPriority is %d \n",schedPrio);
    struct sched_param param;
    pthread_attr_getschedparam(&mThreadAttr, &param);

    param.sched_priority = schedPrio;
    return pthread_attr_setschedparam(&mThreadAttr, &param);
}

int _Thread::getPriority() {
    struct sched_param param;
    int rs = pthread_attr_getschedparam(&mThreadAttr, &param);
    if(rs == 0) {
        return SchePrio2threadPrio(param.__sched_priority);
    }

    return -1;
}

int _Thread::setSchedPolicy(ThreadSchedPolicy policy) {
    
    if(policy != ThreadSchedOTHER
        &&policy != ThreadSchedFIFO
        &&policy != ThreadSchedRR) {
        return -ThreadFailUnknowPolicy;
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
    int policy = ThreadSchedOTHER;
    int rs = pthread_attr_getschedpolicy(&mThreadAttr, &policy);
    if(rs != 0) {
        return -1;
    }
    return policy;
}

void _Thread::onInterrupt() {
    //need overwrite by child class
}


void _Thread::yield() {
    pthread_yield();
}

void _Thread::msleep(unsigned long t) {
    usleep(t*1000);
}

int _Thread::threadPrio2SchePrio(int threadprio) {
    return mPrioTable[threadprio];
}

int _Thread::SchePrio2threadPrio(int schedPrio) {
    int index = ThreadLowestPriority;

    for(;index < ThreadPriorityMax;index++) {
        if(mPrioTable[index] >= schedPrio) {
            break;
        }
    }

    if(index == 0) {
        return ThreadLowestPriority;
    }

    return index--;
}

int _Thread::updateThreadPrioTable(int policy) {
    int maxPrio = sched_get_priority_max (policy);
    int minPrio = sched_get_priority_min (policy);

    printf("updateThreadPrioTable start,max is %d,min is %d \n",maxPrio,minPrio);

    int interval = (maxPrio - minPrio)/ThreadHighestPriority;
    for(int i = ThreadLowestPriority;i < ThreadPriorityMax;i++) {
        mPrioTable[i] = (minPrio/10)*10;
        printf("mPrioTable[%d] is %d \n",mPrioTable[i],i);
        minPrio += interval;
    }

    mPrioTable[ThreadHighestPriority] = maxPrio;
    
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
}

bool _Thread::setThreadSchedPolicy(ThreadSchedPolicy policy) {
    Thread thread = mKeepAliveThread->getSavedThread();
    return thread->setSchedPolicy(policy);
}

int _Thread::getThreadSchedPolicy() {
    Thread thread = mKeepAliveThread->getSavedThread();
    return thread->getSchedPolicy();
}

KeepAliveThread _Thread::getKeepAliveThread(){
    return mKeepAliveThread;
}

}