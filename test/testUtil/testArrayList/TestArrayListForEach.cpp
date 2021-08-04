#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

void testArrayListForEach() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString(1));
    list->add(createString(2));
    list->add(createString(3));

    int index = 1;
    list->foreach([&index](String value) {
      if(value->toBasicInt() != index) {
        printf("---[ArrayList Foreach test1] [FAILED]--- \n");
        return Global::Break;
      }
      index++;
      return Global::Continue;
    });
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString(1));
    list->add(createString(2));
    list->add(createString(3));
    int index = 1;
    list->foreach([&index](String value) {
      if(index == 2) {
        return Global::Break;
      }
      index++;
      return Global::Continue;
    });

    if(index != 2) {
      printf("---[ArrayList Foreach test2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList Foreach test100] [OK]--- \n");
}
