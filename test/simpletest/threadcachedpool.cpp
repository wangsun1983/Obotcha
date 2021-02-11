#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ThreadCachedPoolExecutor.hpp"


using namespace obotcha;

int runDestory = 1;
DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("run test1 start 1\n");
        try {
            st(Thread)::sleep(1*1000);
        } catch(InterruptedException &e){
            printf("run test1 start 1_1 \n");
        }
        printf("run test1 start 2\n");
    }

    void onInterrupt() {
    }

    ~_RunTest1() {
        runDestory = 0;
    }
};

int main() {
    
    ThreadCachedPoolExecutor t = createThreadCachedPoolExecutor();
    int vv1 = 21;
    t->submit(createRunTest1());
    //sleep(1);
    //t->shutdown();
    sleep(20);

    printf("thread num is %d \n",t->getThreadsNum());

    

    return 0;
}