#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(EnqueueData) {
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

DECLARE_SIMPLE_CLASS(EnqueueThread1) IMPLEMENTS(Thread) {
public:
    _EnqueueThread1(BlockingQueue<EnqueueData> queue) {
        mQueue = queue;
    }

    void run() {
        sleep(5);
        mQueue->deQueueFirst();
    }

private:
    BlockingQueue<EnqueueData> mQueue;    
};

DECLARE_SIMPLE_CLASS(EnqueueThread2) IMPLEMENTS(Thread) {
public:
    _EnqueueThread2(BlockingQueue<EnqueueData> queue) {
        mQueue = queue;
        fvalue = 0;
    }

    void run() {
        int i = 0;
        while(1) {
            //printf("setvalue is %d \n",i);
            EnqueueData d = createEnqueueData(i);
            mQueue->enQueueFirst(d);
            mQueue->enQueueFirst(d);

            if(i == 50) {
                EnqueueData nt;
                mQueue->enQueueLast(nt);
                //printf("fvalue is %d \n",fvalue);
                return;
            }
            i++;
            fvalue += i;
        }
    }

private:
    BlockingQueue<EnqueueData> mQueue;
    int fvalue;
};

DECLARE_SIMPLE_CLASS(DequeueThread2) IMPLEMENTS(Thread) {
public:
    _DequeueThread2(BlockingQueue<EnqueueData> queue) {
        mQueue = queue;
    }

    void run() {
        int i = 0;
        while(1) {
            EnqueueData d = mQueue->deQueueFirst();
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
    BlockingQueue<EnqueueData> mQueue;
    int value;
};


int testEnqueueDequeue() {
   
    while(1) {
        BlockingQueue<EnqueueData> list = createBlockingQueue<EnqueueData>(5);
        list->enQueueFirst(createEnqueueData(1));
        list->enQueueFirst(createEnqueueData(2));
        list->enQueueFirst(createEnqueueData(3));
        list->enQueueFirst(createEnqueueData(4));
        list->enQueueFirst(createEnqueueData(5));
        EnqueueThread1 t1 = createEnqueueThread1(list);
        t1->start();
        long time1 = st(System)::currentTimeMillis();
        list->enQueueFirst(createEnqueueData(5));
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) != 5000) {
            printf("BlockingQueue enqueueFirst test1-------[FAIL],value is %ld \n",time2 - time1);
            break;
        }

        printf("BlockingQueue enqueueFirst test2-------[Success] \n");
        break;
    }

    while(1) {
        BlockingQueue<EnqueueData> list = createBlockingQueue<EnqueueData>(5);
        list->enQueueFirst(createEnqueueData(1));
        list->enQueueFirst(createEnqueueData(2));
        list->enQueueFirst(createEnqueueData(3));
        list->enQueueFirst(createEnqueueData(4));
        list->enQueueFirst(createEnqueueData(5));
        
        EnqueueData data1 = list->deQueueFirst();
        if(data1->getValue() != 5) {
            printf("BlockingQueue enqueueFirst test3-------[FAIL] \n");
            break;
        }

        data1 = list->deQueueFirst();
        if(data1->getValue() != 4) {
            printf("BlockingQueue enqueueFirst test4-------[FAIL] \n");
            break;
        }

        data1 = list->deQueueFirst();
        if(data1->getValue() != 3) {
            printf("BlockingQueue enqueueFirst test5-------[FAIL] \n");
            break;
        }

        data1 = list->deQueueFirst();
        if(data1->getValue() != 2) {
            printf("BlockingQueue enqueueFirst test6-------[FAIL] \n");
            break;
        }

        data1 = list->deQueueFirst();
        if(data1->getValue() != 1) {
            printf("BlockingQueue enqueueFirst test7-------[FAIL] \n");
            break;
        }

        printf("BlockingQueue enqueueFirst test8-------[Success] \n");
        break;
    }

    while(1) {
        BlockingQueue<EnqueueData> list = createBlockingQueue<EnqueueData>(5);
        list->enQueueFirst(nullptr);
        if(list->size() == 0) {
            printf("BlockingQueue enqueueFirst test9-------[FAIL] \n");
            break;
        }

        printf("BlockingQueue enqueueFirst test10-------[Success] \n");
        break;
    }


    while(1) {
        BlockingQueue<EnqueueData> list = createBlockingQueue<EnqueueData>(5);
        EnqueueThread2 t1 = createEnqueueThread2(list);
        DequeueThread2 t2 = createDequeueThread2(list);

        t1->start();
        t2->start();

        t1->join();
        t2->join();

        int result = t2->getResult();
        if(result != 2550) {
            printf("BlockingQueue enqueueFirst test11-------[FAIL],result is %d \n",result);
            break;
        }

        printf("BlockingQueue enqueueFirst test12-------[Success] \n");
        break;
    }
}
