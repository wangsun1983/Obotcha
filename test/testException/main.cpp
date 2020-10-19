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
#include "Error.hpp"
#include "IllegalStateException.hpp"

using namespace obotcha;

DECLARE_EXCEPTION(MyException) {
public:
	MyException(const char * str):Exception(str){

    }
	MyException(String str):Exception(str) {}
};


void doException() {
    String exception = createString("ByteArray [] fail")
                            ->append("size is",
                                    createString(1),
                                    "index is ",
                                    createString(1));
    throwMyException(exception);
}

DECLARE_SIMPLE_CLASS(MyTT) {
public:
    int i;
    MyTT sayhello() {
        printf("hello");
        i = 100;
        return AutoClone(this);
    }
};

int main() {
    //doException();
    MyTT q = createMyTT();
    MyTT q2 = q->sayhello();
    printf("v is %d \n",q2->i);
    return 1;
}
