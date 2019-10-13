#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "ForkJoinTask.hpp"

using namespace obotcha;


DECLARE_SIMPLE_CLASS(MyTest) IMPLEMENTS(ForkJoinTask<int>) {

public:
    int compute() {
        printf("iiii \n");
    }
};

int main() {
    printf("---[TestRecursiveTask Test Start]--- \n");
    MyTest t = createMyTest();
    t->compute();
    
    
}

