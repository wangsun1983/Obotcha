#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_Iterator_HasValue() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    auto iterator = list->getIterator();
    if(iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test1] [FAILED]--- \n");
      break;
    }

    list->add(createString("a")); //this may case crash~~~.haha
    if(!iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test2] [FAILED]--- \n");
      break;
    }

#if 0
    iterator->remove();
    if(iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test2_1] [FAILED]--- \n");
      break;
    }

    if(list->size() != 0) {
      printf("---[ArrayList Iterator HasValue test2_2] [FAILED]--- \n");
      break;
    }
#endif

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    auto iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test3] [FAILED]--- \n");
      break;
    }

    iterator->remove();
    if(iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test4] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    auto iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test5] [FAILED]--- \n");
      break;
    }

    iterator->next();
    if(iterator->hasValue()) {
      printf("---[ArrayList Iterator HasValue test6] [FAILED]--- \n");
      break;
    }

    break;
  }

  printf("---[ArrayList Iterator HasValue test100] [OK]--- \n");
}
