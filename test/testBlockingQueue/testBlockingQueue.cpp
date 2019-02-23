#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"


DECLARE_SIMPLE_CLASS(ConsumeRunn) IMPLEMENTS(Runnable) {
public:

    _ConsumeRunn(BlockingQueue<Integer> ll) {
        queue = ll;
    }

    void run() {
        printf("i am a thread1 \n");
        while(1) {
            Integer val = queue->deQueueFirst();
            printf("thread1 get val is %d \n",val->toValue());
            usleep(100000);
        }
    }

private:
    BlockingQueue<Integer> queue;
};

DECLARE_SIMPLE_CLASS(ProduceRunn) IMPLEMENTS(Runnable) {
public:

    _ProduceRunn(BlockingQueue<Integer> ll) {
        queue = ll;
    }

    void run() {
        printf("i am a thread2 \n");
        int i = 0;
        while(1) {
            queue->enQueueLast(i);
            printf("thread2 set val is %d \n",i);
            i++;
            //usleep(100000);
        }
    }

private:
    BlockingQueue<Integer> queue;
};


DECLARE_SIMPLE_CLASS(Student) {
public:
    int i;
};

int main() {

    BlockingQueue<Integer> qq = createBlockingQueue<Integer>(3);

    Thread mThread1 = createThread(createConsumeRunn(qq));
    mThread1->start();

    Thread mThread2 = createThread(createProduceRunn(qq));
    mThread2->start();

    while(1) {
        usleep(1000);
    }
}
