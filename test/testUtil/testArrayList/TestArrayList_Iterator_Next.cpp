#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_Iterator_Next() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    auto iterator = list->getIterator();
    if(iterator->next()) {
      printf("---[ArrayList Iterator Next test1] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    auto iterator = list->getIterator();
    if(iterator->next()) {
      printf("---[ArrayList Iterator Next test2] [FAILED]--- \n");
      break;
    }

    if(iterator->next()) {
      printf("---[ArrayList Iterator Next test3] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    auto iterator = list->getIterator();
    if(!iterator->next()) {
      printf("---[ArrayList Iterator Next test4] [FAILED]--- \n");
      break;
    }

    if(iterator->next()) {
      printf("---[ArrayList Iterator Next test5] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList Iterator Next test100] [OK]--- \n");
}
