#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "StringFormat.hpp"

using namespace obotcha;

int main() {

  printf("---[StringFormat Test Start]--- \n");

  while(1) {
    StringFormat format = createStringFormat();
    String str = format->format("i say %s","hello");
    if(!str->equals("i say hello")){
      printf("---[StringFormat Test {format()} case1] [FAILED]--- \n");
      break;
    }

    str = format->format("%d,%s",1,"a");
    if(!str->equals("1,a")) {
      printf("---[StringFormat Test {format()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[StringFormat Test {format()} case3] [Success]--- \n");
    break;
  }



}
