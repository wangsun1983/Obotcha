#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ThreadPoolExecutor.hpp"


using namespace obotcha;

int main() {
    
    ThreadPoolExecutor t = createThreadPoolExecutor();
    int vv1 = 21;
    t->execute([&vv1](int v) {
        printf("woqu!!!!!!,v is %d,vv1 is %d \n",v,vv1);
    },123);

    Future future = t->submit([](){
        printf("woqu!!!!!!,submit  \n");
    });

    sleep(1);
    t->shutdown();
    sleep(1);
    printf("i will exit \n");
    int pp = 311;
    Thread t1 = createThread([](int v) {
        printf("it is a thread ,v is %d\n",v);
    },pp);
    t1->start();


    sleep(1);

    return 0;
}