#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_CLASS(FixRateRunTest1) IMPLEMENTS(Runnable) {
public:
    _FixRateRunTest1(int s) {
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

    ~_FixRateRunTest1() {
        //printf("i am release .......aaaa,p is %x\n",this);
    }

private:
    int sleepTime;
    long startTime;
    long recordStartTime;
    long recordFinishTime;
    ArrayList<Long> v;
};


int fixRateTest() {
    while(1) {
        ThreadScheduledPoolExecutor pool = st(Executors)::newScheduledThreadPool();
        FixRateRunTest1 r = createFixRateRunTest1(3);

        long startRun = st(System)::currentTimeMillis();
        pool->scheduleAtFixedRate(1000,1000,r);
        sleep(15);

        pool->shutdown();
        ArrayList<Long> list = r->getIntervals();
        ListIterator<Long> iterator = list->getIterator();
        while(iterator->hasValue()) {
          Long l = iterator->getValue();
          if(l->toValue() > 5) {
            printf("---[ScheduledThreadPoolExecutor fixRateTest case1],v is %ld [FAIL]--- \n",l->toValue());
            break;
          }
          iterator->next();
        }

        if(list->size() == 0) {
          printf("---[ScheduledThreadPoolExecutor fixRateTest case2] [FAIL]--- \n");
          break;
        }

        long current = st(System)::currentTimeMillis();
        if((r->getStartTime() - startRun) > 1005) {
            printf("---[ScheduledThreadPoolExecutor fixRateTest case3] [FAIL] v is %ld--- \n",current - r->getStartTime());
        }

        printf("---[ScheduledThreadPoolExecutor fixRateTest case4] [Success]--- \n");
        break;
    }

    while(1) {
        ThreadScheduledPoolExecutor pool = st(Executors)::newScheduledThreadPool();
        FixRateRunTest1 r = createFixRateRunTest1(1);

        long startRun = st(System)::currentTimeMillis();
        pool->scheduleAtFixedRate(1000,2000,r);
        sleep(15);

        pool->shutdown();
        ArrayList<Long> list = r->getIntervals();
        ListIterator<Long> iterator = list->getIterator();
        while(iterator->hasValue()) {
          Long l = iterator->getValue();
          if(l->toValue() > 1010 || l->toValue() < 995) {
            printf("---[ScheduledThreadPoolExecutor fixRateTest case5] [FAIL] v is %d--- \n",l->toValue());
            break;
          }
          iterator->next();
        }

        if(list->size() == 0) {
          printf("---[ScheduledThreadPoolExecutor fixRateTest case6] [FAIL]--- \n");
          break;
        }

        long current = st(System)::currentTimeMillis();
        if((r->getStartTime() - startRun) > 1005) {
            printf("---[ScheduledThreadPoolExecutor fixRateTest case7] [FAIL] v is %ld--- \n",current - r->getStartTime());
        }

        printf("---[ScheduledThreadPoolExecutor fixRateTest case8] [Success]--- \n");
        break;
    }

}
