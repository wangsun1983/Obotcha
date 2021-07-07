#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "String.hpp"

using namespace obotcha;

int formattest() {

  printf("---[String Format Test Start]--- \n");

  while(1) {
    String str = st(String)::format("i say %s","hello");
    if(!str->equals("i say hello")){
      printf("---[String Format Test {format()} case1] [FAILED]--- \n");
      break;
    }

    str = st(String)::format("%d,%s",1,"a");
    if(!str->equals("1,a")) {
      printf("---[String Format Test {format()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[String Format Test {format()} case3] [Success]--- \n");
    break;
  }



}
