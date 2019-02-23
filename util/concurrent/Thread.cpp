
#include <unistd.h>

#include "Thread.hpp"
#include "AutoMutex.hpp"

//------------RecyleThread---------------//
static void* recycle(void *th) {
    _RecycleThread *thread = static_cast<_RecycleThread *>(th);
    thread->run();
    return nullptr;
}

_RecycleThread::_RecycleThread() {
    mutex = createMutex();
    cond = createCondition();
    queue = createBlockingQueue<_Thread *>();
    isRunning = false;
}

void _RecycleThread::start() {
    if(!isRunning) {
        pthread_create(&mTid, &mAttr, recycle, this);
    }

    isRunning = true;
}

void _RecycleThread::run() {
    while(1) {
        Thread t = queue->deQueueFirst();
        //t->exit();
        t->decStrong(0);
    }
}

void _RecycleThread::submit(_Thread *t){
    queue->enQueueLast(t);
}

//------------Thread Stack function---------------//
static void cleanup(void *th)
{
    _Thread *thread = static_cast<_Thread *>(th);
    thread->onInterrupt();
    if(thread->getRunnable() != nullptr) {
        thread->getRunnable()->onInterrupt();
    }

    _Thread::getRecyleThread()->submit(thread);
}

//------------Thread---------------//
RecycleThread _Thread::mRecyle = createRecycleThread();

static void* localRun(void *th) {
    _Thread *thread = static_cast<_Thread *>(th);
    thread->run();
    return nullptr;
}

_Thread::_Thread(Runnable run) {
	//pthread_attr_init(&mThreadAttr);
    //if(mRecyle.m_ptr == nullptr) {
    //    printf("creat recyle \n");
    //    mRecyle = createRecycleThread();
    mRecyle->start();
    //}
	mRunnable = run;
}

_Thread::_Thread() {
    //Nothing
}

_Thread::~_Thread(){
    //TODO
}

void _Thread::onInterrupt() {
    //mRunnable->onInterrupt();
}

Runnable _Thread::getRunnable() {
    return mRunnable;
}

void _Thread::run() {
    pthread_cleanup_push(cleanup, this);
	if(mRunnable != nullptr) {
    	mRunnable->run();
    }
    mRecyle->submit(this);
    pthread_cleanup_pop(0);
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
    incStrong(0);
    //mThread = new std::thread(localRun, this);
    //mTid = mThread->native_handle();
    pthread_create(&mPthread, &mThreadAttr, localRun, this);
}

void _Thread::join() {
	pthread_join(mPthread,(void **) NULL);
    //mThread->join();
}

bool _Thread::isFinished() {
    //TODO
    return false;
}

bool _Thread::isRunning() {
    //TODO
    return false;
}


void _Thread::exit() {
    pthread_cancel(mPthread);
}

void setPriority(ThreadPriority priority) {
    //TODO
}


void _Thread::yield() {
    pthread_yield();
}

void _Thread::sleep(unsigned long t) {
    sleep(t);
}

void _Thread::msleep(unsigned long t) {
    usleep(t*1000);
}
    
void _Thread::usleep(unsigned long t) {
    usleep(t*1000);
}

RecycleThread _Thread::getRecyleThread(){
    return mRecyle;
}

