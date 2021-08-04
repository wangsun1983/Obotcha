#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_Iterator_GetValue() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    auto iterator = list->getIterator();
    auto v = iterator->getValue();
    if(v == nullptr || !v->equals("a")) {
      printf("---[ArrayList Iterator GetValue test1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    v = iterator->getValue();
    if(v == nullptr || !v->equals("b")) {
      printf("---[ArrayList Iterator GetValue test2] [FAILED]--- \n");
      break;
    }

    iterator->next();
    bool isExcpetion = false;
    try {
      v = iterator->getValue();
    } catch(...) {
      isExcpetion = true;
    }

    if(!isExcpetion) {
      printf("---[ArrayList Iterator GetValue test3] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
      ArrayList<String> list = createArrayList<String>();
      auto iterator = list->getIterator();
      bool isExcpetion = false;
      try {
        auto v = iterator->getValue();
      } catch(...) {
        isExcpetion = true;
      }

      if(!isExcpetion) {
        printf("---[ArrayList Iterator GetValue test4] [FAILED]--- \n");
        break;
      }
      break;
  }

  printf("---[ArrayList Iterator GetValue test100] [OK]--- \n");
}
