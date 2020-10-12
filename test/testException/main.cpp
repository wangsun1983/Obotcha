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

int main() {
    doException();
    return 1;
}
