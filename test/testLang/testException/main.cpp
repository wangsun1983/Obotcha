#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"
#include "Exception.hpp"

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
    Trigger(MyException,exception);
}


int main() {
    bool isException = false;

    try {
        doException();
    }catch(MyException e) {
        isException = true;
    }

    if(!isException) {
        printf("---[Exception test1] [FAILED]--- \n");
    }

    printf("---[Exception test1] [OK]--- \n");
    return 1;
}
