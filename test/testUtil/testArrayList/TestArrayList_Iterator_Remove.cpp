#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_Iterator_Remove() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    auto iterator = list->getIterator();
    if(!iterator->remove()) {
      printf("---[ArrayList Iterator Remove test1] [FAILED]--- \n");
      break;
    }

    String value = iterator->getValue();
    if(value == nullptr || !value->equals("b") || list->size() != 1) {
      printf("---[ArrayList Iterator Remove test2] [FAILED]--- \n");
      break;
    }

    if(list->size() != 1) {
      printf("---[ArrayList Iterator Remove test3] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    auto iterator = list->getIterator();
    if(iterator->remove()) {
      printf("---[ArrayList Iterator Remove test4] [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---[ArrayList Iterator Remove test100] [OK]--- \n");
}
