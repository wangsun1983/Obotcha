#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_RemoveAt() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    auto value = list->removeAt(0);
    if(value == nullptr || !value->equals("a")) {
      printf("---[ArrayList removeAt test1] [FAILED]--- \n");
      break;
    }

    if(list->size() != 1) {
      printf("---[ArrayList removeAt test2] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    bool isException = false;
    try {
      list->removeAt(0);
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[ArrayList removeAt test3] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList removeAt test100] [OK]--- \n");
}
