#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"


DECLARE_SIMPLE_CLASS(MyRun1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("MyRunn1 start \n");
        usleep(1000000);
        printf("MyRunn1 sleep complete \n");
    }
};

DECLARE_SIMPLE_CLASS(MyRun2) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("MyRunn2 start \n");
        usleep(2000000);
        printf("MyRunn2 sleep complete \n");
    }
};


int main() {

    ExecutorService service = createExecutorService();
    ExecutorService service2 = createExecutorService();
    service->execute(createMyRun1());
    service->execute(createMyRun2());
    printf("main1,start wait \n");
    sleep(1);
    service->awaitTermination();
    printf("main2,start wait finish \n");

    while(1) {
        usleep(1000);
    }
}
