#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_CLASS(EnqueueData) {
public:
    _EnqueueData(int v) {
        i = v;
    }

    int getValue() {
        return i;
    }

private:
    int i;
};

DECLARE_CLASS(EnqueueThread1) IMPLEMENTS(Thread) {
public:
    _EnqueueThread1(BlockingLinkedList<EnqueueData> queue) {
        mQueue = queue;
    }

    void run() {
        msleep(1000*5);
        mQueue->takeFirst();
    }

private:
    BlockingLinkedList<EnqueueData> mQueue;
};

DECLARE_CLASS(EnqueueThread2) IMPLEMENTS(Thread) {
public:
    _EnqueueThread2(BlockingLinkedList<EnqueueData> queue) {
        mQueue = queue;
        fvalue = 0;
    }

    void run() {
        int i = 0;
        while(1) {
            //printf("setvalue is %d \n",i);
            EnqueueData d = createEnqueueData(i);
            mQueue->putFirst(d);
            mQueue->putFirst(d);

            if(i == 50) {
                EnqueueData nt;
                mQueue->putLast(nt);
                //printf("fvalue is %d \n",fvalue);
                return;
            }
            i++;
            fvalue += i;
        }
    }

private:
    BlockingLinkedList<EnqueueData> mQueue;
    int fvalue;
};

DECLARE_CLASS(DequeueThread2) IMPLEMENTS(Thread) {
public:
    _DequeueThread2(BlockingLinkedList<EnqueueData> queue) {
        mQueue = queue;
    }

    void run() {
        int i = 0;
        while(1) {
            EnqueueData d = mQueue->takeFirst();
            if(d == nullptr) {
                return;
            }
            //printf("d->getValue is %d \n",d->getValue());

            value += d->getValue();
        }
    }

    int getResult() {
        return value;
    }

private:
    BlockingLinkedList<EnqueueData> mQueue;
    int value;
};


void testEnqueueDequeue() {

    while(1) {
        BlockingLinkedList<EnqueueData> list = createBlockingLinkedList<EnqueueData>(5);
        list->putFirst(createEnqueueData(1));
        list->putFirst(createEnqueueData(2));
        list->putFirst(createEnqueueData(3));
        list->putFirst(createEnqueueData(4));
        list->putFirst(createEnqueueData(5));
        EnqueueThread1 t1 = createEnqueueThread1(list);
        t1->start();
        long time1 = st(System)::currentTimeMillis();
        list->putFirst(createEnqueueData(5));
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) < 5000 || (time2 - time1) > 5005) {
            printf("BlockingLinkedList putFirst test1-------[FAIL],value is %ld \n",time2 - time1);
            break;
        }

        printf("BlockingLinkedList putFirst test2-------[OK] \n");
        break;
    }

    while(1) {
        BlockingLinkedList<EnqueueData> list = createBlockingLinkedList<EnqueueData>(5);
        list->putFirst(createEnqueueData(1));
        list->putFirst(createEnqueueData(2));
        list->putFirst(createEnqueueData(3));
        list->putFirst(createEnqueueData(4));
        list->putFirst(createEnqueueData(5));

        EnqueueData data1 = list->takeFirst();
        if(data1->getValue() != 5) {
            printf("BlockingLinkedList putFirst test3-------[FAIL] \n");
            break;
        }

        data1 = list->takeFirst();
        if(data1->getValue() != 4) {
            printf("BlockingLinkedList putFirst test4-------[FAIL] \n");
            break;
        }

        data1 = list->takeFirst();
        if(data1->getValue() != 3) {
            printf("BlockingLinkedList putFirst test5-------[FAIL] \n");
            break;
        }

        data1 = list->takeFirst();
        if(data1->getValue() != 2) {
            printf("BlockingLinkedList putFirst test6-------[FAIL] \n");
            break;
        }

        data1 = list->takeFirst();
        if(data1->getValue() != 1) {
            printf("BlockingLinkedList putFirst test7-------[FAIL] \n");
            break;
        }

        printf("BlockingLinkedList putFirst test8-------[OK] \n");
        break;
    }

    while(1) {
        BlockingLinkedList<EnqueueData> list = createBlockingLinkedList<EnqueueData>(5);
        list->putFirst(nullptr);
        if(list->size() == 0) {
            printf("BlockingLinkedList putFirst test9-------[FAIL] \n");
            break;
        }

        printf("BlockingLinkedList putFirst test10-------[OK] \n");
        break;
    }


    while(1) {
        BlockingLinkedList<EnqueueData> list = createBlockingLinkedList<EnqueueData>(5);
        EnqueueThread2 t1 = createEnqueueThread2(list);
        DequeueThread2 t2 = createDequeueThread2(list);

        t1->start();
        t2->start();

        t1->join();
        t2->join();

        int result = t2->getResult();
        if(result != 2550) {
            printf("BlockingLinkedList putFirst test11-------[FAIL],result is %d \n",result);
            break;
        }

        printf("BlockingLinkedList putFirst test12-------[OK] \n");
        break;
    }
}
