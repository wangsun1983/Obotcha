#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyRun1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("MyRunn1 start \n");
        sleep(3);
        printf("MyRunn1 sleep complete \n");
    }
};

DECLARE_SIMPLE_CLASS(MyRun2) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("MyRunn2 start \n");
        sleep(4);
        printf("MyRunn2 sleep complete \n");
    }
};

DECLARE_SIMPLE_CLASS(MyRun3) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("MyRunn3 start \n");
        sleep(4);
        printf("MyRunn3 sleep complete \n");
    }
};

int main() {
    ExecutorService service = st(Executors)::newFixedThreadPool(1);
    printf("main1,start trace1 \n");
    Future f = service->submit(createMyRun1());
    printf("main1,start trace1_1 \n");
    Future f2 = service->submit(createMyRun2());
    printf("main1,start trace2 \n");
    sleep(1);
    printf("main1,start trace2_1 \n");
    f2->cancel();
    service->execute(createMyRun3());
    printf("main1,start trace3 \n");
    f->wait();
    printf("main1,start trace4 \n");
    sleep(1);
    //service->awaitTermination(0);
    //printf("main2,start wait finish \n");
    printf("main1,start trace5 \n");
    while(1) {
        usleep(1000);
    }
}
