#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "UUID.hpp"
#include "Log.hpp"
#include "ArrayList.hpp"
#include "String.hpp"
#include "Runnable.hpp"
#include "ExecutorService.hpp"
#include "Executors.hpp"


using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyData) {
public:
    int value;    
};

DECLARE_SIMPLE_CLASS(MyRun) IMPLEMENTS(Runnable) {
public:
    _MyRun() {
        printf("myRun \n");
    }

    void run() {
        printf("start run \n");
        sleep(10);
        printf("finish sleep,set result \n");
        MyData data = createMyData();
        data->value = 199;
        setResult(data);
        printf("run complete \n");
    }
};

int main() {
    ExecutorService pool = st(Executors)::newFixedThreadPool(100,100);
    Future future = pool->submit(createMyRun());
    MyData value = future->getResult<MyData>();
    printf("result is %d \n",value->value);
    
}
