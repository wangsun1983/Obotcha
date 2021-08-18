#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "ThreadScheduledPoolExecutor.hpp"

using namespace obotcha;

DECLARE_CLASS(FixDelayRunTest1) IMPLEMENTS(Runnable) {
public:
    _FixDelayRunTest1(int s) {
      startTime = 0;
      recordFinishTime = 0;
      v = createArrayList<Long>();
      sleepTime = s;
    }

    void run() {
        if(startTime == 0) {
          startTime = st(System)::currentTimeMillis();
        }

        if(recordFinishTime != 0) {
          long interval = st(System)::currentTimeMillis() - recordFinishTime;
          v->add(createLong(interval));
        }

        sleep(sleepTime);

        recordFinishTime = st(System)::currentTimeMillis();
    }

    ArrayList<Long> getIntervals() {
      return v;
    }

    long getStartTime() {
      return startTime;
    }

    ~_FixDelayRunTest1() {
        //printf("i am release .......aaaa,p is %x\n",this);
    }

private:
    int sleepTime;
    long startTime;
    long recordStartTime;
    long recordFinishTime;
    ArrayList<Long> v;
};


int fixDelayTest() {
    while(1) {
        ThreadScheduledPoolExecutor pool = st(Executors)::newScheduledThreadPool();
        FixDelayRunTest1 r = createFixDelayRunTest1(3);

        long startRun = st(System)::currentTimeMillis();
        pool->scheduleWithFixedDelay(1000,1000,r);
        sleep(15);

        pool->shutdown();
        ArrayList<Long> list = r->getIntervals();
        ListIterator<Long> iterator = list->getIterator();
        while(iterator->hasValue()) {
          Long l = iterator->getValue();
          if(l->toValue() > 1005 || l->toValue() < 995) {
            printf("---[ScheduledThreadPoolExecutor fixDelayTest case1] [FAIL]--- \n");
            break;
          }
          iterator->next();
        }

        if(list->size() == 0) {
          printf("---[ScheduledThreadPoolExecutor fixDelayTest case2] [FAIL]--- \n");
          break;
        }

        long current = st(System)::currentTimeMillis();
        if((r->getStartTime() - startRun) > 1005) {
            printf("---[ScheduledThreadPoolExecutor fixDelayTest case3] [FAIL] v is %ld--- \n",current - r->getStartTime());
        }

        printf("---[ScheduledThreadPoolExecutor fixDelayTest case4] [Success]--- \n");
        break;
    }

    while(1) {
        ThreadScheduledPoolExecutor pool = st(Executors)::newScheduledThreadPool();
        FixDelayRunTest1 r = createFixDelayRunTest1(1);

        long startRun = st(System)::currentTimeMillis();
        pool->scheduleAtFixedRate(1000,2000,r);
        sleep(15);

        pool->shutdown();
        ArrayList<Long> list = r->getIntervals();
        ListIterator<Long> iterator = list->getIterator();
        while(iterator->hasValue()) {
          Long l = iterator->getValue();
          if(l->toValue() > 1005 || l->toValue() < 995) {
            printf("---[ScheduledThreadPoolExecutor fixDelayTest case5] [FAIL] v is %d--- \n",l->toValue());
            break;
          }
          iterator->next();
        }

        if(list->size() == 0) {
          printf("---[ScheduledThreadPoolExecutor fixDelayTest case6] [FAIL]--- \n");
          break;
        }

        long current = st(System)::currentTimeMillis();
        if((r->getStartTime() - startRun) > 1010) {
            printf("---[ScheduledThreadPoolExecutor fixDelayTest case7] [FAIL] v is %ld--- \n",r->getStartTime() - startRun);
        }

        printf("---[ScheduledThreadPoolExecutor fixDelayTest case8] [Success]--- \n");
        break;
    }

}
