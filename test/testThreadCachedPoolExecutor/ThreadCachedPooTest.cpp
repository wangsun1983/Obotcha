#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"

using namespace obotcha;

extern int normalTest();
extern int numTest();
extern int releaseTest();


DECLARE_SIMPLE_CLASS(LocalRunnable) IMPLEMENTS(Runnable) {
public:
   void run() {
      printf("myruntest 5 trace1 \n");
      sleep(10);
      //printf("myruntest 5 trace3 \n");
   }
};


int main() {
    //ExecutorService pool = st(Executors)::newCachedThreadPool();
    //pool->submit(createLocalRunnable());
    //pool->submit(createLocalRunnable());
    //pool->submit(createLocalRunnable());
    //sleep(1);
    //pool->shutdown();
    //sleep(1);

    //printf("pool2 thread num is %d \n",pool->getThreadsNum());
    

    normalTest();
    
    //numTest();
    //releaseTest();
    sleep(10);



}
