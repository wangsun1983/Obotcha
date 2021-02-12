/**
 * @file Executors.cpp
 * @brief Executor Factory 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Executors.hpp"
#include "Thread.hpp"


namespace obotcha {

ThreadPoolExecutor _Executors::newFixedThreadPool(int queue_size,int thread_num) {
    return createThreadPoolExecutor(queue_size,thread_num);
}

ThreadPoolExecutor _Executors::newFixedThreadPool(int thread_num) {
    return createThreadPoolExecutor(-1,thread_num);
}

ThreadPoolExecutor _Executors::newSingleThreadExecutor(int queue_size) {
    return createThreadPoolExecutor(queue_size,1);
}

ThreadPriorityPoolExecutor _Executors::newPriorityThreadPool(int thread_num) {
    return createThreadPriorityPoolExecutor(thread_num);
}

ThreadPriorityPoolExecutor _Executors::newPriorityThreadPool(){
    return createThreadPriorityPoolExecutor();
}

ThreadCachedPoolExecutor _Executors::newCachedThreadPool(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    return createThreadCachedPoolExecutor(queuesize,minthreadnum,maxthreadnum,timeout);
}

ThreadCachedPoolExecutor _Executors::newCachedThreadPool(int maxthreadnum,long timeout) {
    return createThreadCachedPoolExecutor(maxthreadnum,timeout);
}

ThreadCachedPoolExecutor _Executors::newCachedThreadPool() {
    return createThreadCachedPoolExecutor();
}

ThreadScheduledPoolExecutor _Executors::newSingleThreadScheduledExecutor() {
    //TODO
    return nullptr;
}

ThreadScheduledPoolExecutor _Executors::newScheduledThreadPool() {
    return createThreadScheduledPoolExecutor();
}


}