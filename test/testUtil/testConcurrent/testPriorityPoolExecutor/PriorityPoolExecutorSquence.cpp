#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ThreadPriorityPoolExecutor.hpp"

using namespace obotcha;

int startValue = 0;
int Sequence1 = 0;
int Sequence2 = 0;
int Sequence3 = 0;
int Sequence4 = 0;
int Sequence5 = 0;

DECLARE_CLASS(SequenceTestIdle) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("test0 \n");
        sleep(10);
        //printf("test0_2 \n");
    }
};

DECLARE_CLASS(SequenceTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("test1111111, startValue is %d \n",startValue);
        sleep(1);
        Sequence1 = startValue;
        startValue++;
    }
};

DECLARE_CLASS(SequenceTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("test2 \n");
        Sequence2 = startValue;
        startValue++;

    }
};

DECLARE_CLASS(SequenceTest3) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("test3 \n");
        Sequence3 = startValue;
        startValue++;

    }
};

#if 0
DECLARE_CLASS(SequenceTest4) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("test4 \n");
        Sequence4 = startValue;
        startValue++;
    }
};

DECLARE_CLASS(SequenceTest5) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("test5 \n");
        Sequence5 = startValue;
        startValue++;
    }
};
#endif

int testSequence() {
    while(1) {
        ThreadPriorityPoolExecutor pool = st(Executors)::newPriorityThreadPool(1);
        pool->submit(st(ThreadPriorityPoolExecutor)::PriorityHigh,createSequenceTestIdle());
        sleep(1);
        pool->submit(st(ThreadPriorityPoolExecutor)::PriorityLow,createSequenceTest1());
        pool->submit(st(ThreadPriorityPoolExecutor)::PriorityHigh,createSequenceTest2());
        pool->submit(st(ThreadPriorityPoolExecutor)::PriorityMedium,createSequenceTest3());

        sleep(11);

        if(Sequence2 != 0 || Sequence3 != 1 || Sequence1 != 2) {
            printf("Sequence2 is %d,Sequence3 is %d,Sequence1 is %d \n",Sequence2,Sequence3,Sequence1);
            printf("---[TestPriorityPoolExecutor Sequence Test case3] [FAIL]--- \n");
            break;
        }

        printf("---[TestPriorityPoolExecutor Sequence Test case3] [Success]--- \n");
        break;
    }
}
