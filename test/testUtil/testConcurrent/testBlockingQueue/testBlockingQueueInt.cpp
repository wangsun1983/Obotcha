#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(EnqueueIntThread1) IMPLEMENTS(Thread) {
public:
    _EnqueueIntThread1(BlockingQueue<int> queue) {
        mQueue = queue;
    }

    void run() {
        msleep(1000*5);
        mQueue->takeFirst();
    }

private:
    BlockingQueue<int> mQueue;
};

void testBlockingQueueInt() {

    while(1) {
        BlockingQueue<int> list = createBlockingQueue<int>(5);
        list->putFirst(1);
        list->putFirst(2);
        list->putFirst(3);
        list->putFirst(4);
        list->putFirst(5);
        EnqueueIntThread1 t1 = createEnqueueIntThread1(list);
        t1->start();
        long time1 = st(System)::currentTimeMillis();
        list->putFirst(6);
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) > 5005 ||(time2 - time1) < 5000 ) {
            printf("BlockingQueue<int> putFirst test1-------[FAIL],value is %ld \n",time2 - time1);
            break;
        }

        printf("BlockingQueue<int> putFirst test2-------[OK] \n");
        break;
    }

    while(1) {
        BlockingQueue<int> list = createBlockingQueue<int>(5);
        list->putLast(0);
        list->putLast(1);
        list->putLast(2);
        list->putLast(3);
        list->putLast(4);
        for(int i = 0;i<5;i++) {
            int v = list->takeFirst();
            if(v != i) {
                printf("BlockingQueue<int> putFirst test3-------[FAIL],v is %d i is %d\n",v,i);
                break;
            }
        }
        printf("BlockingQueue<int> putFirst test4-------[OK] \n");
        break;
    }

    while(1) {
        BlockingQueue<int> list = createBlockingQueue<int>(5);
        bool isException = false;
        long time1 = st(System)::currentTimeMillis();
        try {
            list->takeFirst(100);
        } catch(...) {
            isException = true;
        }
        long time2 = st(System)::currentTimeMillis();
        if(!isException) {
            printf("BlockingQueue<int> takeFirst test3-------[FAIL] \n");
            break;
        }

        if((time2 - time1) > 105 || (time2 - time1) < 100) {
            printf("BlockingQueue<int> takeFirst test3-------[FAIL],interval is %ld \n",time2-time1);
            break;
        }

        printf("BlockingQueue<int> takeFirst test4-------[OK] \n");
        break;
    }

}
