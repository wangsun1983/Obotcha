#include <stdio.h>
#include <unistd.h>

#include "HttpContentType.hpp"

using namespace obotcha;

int testHttpContentType() {
  //case1
  //while(1) {
    String content = createString("application/x-www-form-urlencoded;charset=UTF-8");
    printf("trace1 \n");
    HttpContentType type = createHttpContentType();
    printf("trace2 \n");
    type->import(content);

    String content2 = createString("text/plain;boundary=foo;charset=utf-8");
    type->import(content2);
    printf("type is %s,boundary is %s,charset is %s \n",
            type->getType()->toChars(),
            type->getBoundary()->toChars(),
            type->getCharSet()->toChars());
  //}
}
