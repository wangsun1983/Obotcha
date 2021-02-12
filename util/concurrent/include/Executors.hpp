#ifndef __OBOTCHA_EXECUTORS_HPP__
#define __OBOTCHA_EXECUTORS_HPP__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "LinkedList.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Executors) {

public:
    static ThreadPoolExecutor newFixedThreadPool(int queue_size,int thread_num);
    static ThreadPoolExecutor newFixedThreadPool(int thread_num);

    static ThreadPoolExecutor newSingleThreadExecutor(int queue_size);
    
    static ThreadCachedPoolExecutor newCachedThreadPool(int queue_size,int maxthreadnum,int minthreadnum,long timeout);
    static ThreadCachedPoolExecutor newCachedThreadPool(int maxthreadnum,long timeout);
    static ThreadCachedPoolExecutor newCachedThreadPool();


    static ThreadScheduledPoolExecutor newSingleThreadScheduledExecutor();
    static ThreadScheduledPoolExecutor newScheduledThreadPool();

    static ThreadPriorityPoolExecutor newPriorityThreadPool(int thread_num);
    static ThreadPriorityPoolExecutor newPriorityThreadPool();
    
};

}
#endif