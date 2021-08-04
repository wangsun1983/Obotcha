#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_Iterator_Insert() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));

    auto iterator = list->getIterator();
    iterator->insert(createString("a1"));
    if(list->size() != 2 || !list->get(0)->equals("a1") || !list->get(1)->equals("a")) {
      printf("---[ArrayList Iterator Insert test1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    auto iterator = list->getIterator();
    iterator->next();
    iterator->insert(createString("a1"));
    if(list->size() != 3 || !list->get(0)->equals("a") || !list->get(1)->equals("a1") ||!list->get(2)->equals("b")) {
      printf("---[ArrayList Iterator Insert test2] [FAILED]--- \n");
      break;
    }

    auto value = iterator->getValue();
    if(value == nullptr || !value->equals("a1")) {
      printf("---[ArrayList Iterator Insert test3] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    auto iterator = list->getIterator();
    iterator->next();
    iterator->insert(createString("c"));
    iterator->insert(createString("d"));
    if(list->size() != 4
    || !list->get(0)->equals(createString("a"))
    || !list->get(1)->equals(createString("d"))
    || !list->get(2)->equals(createString("c"))
    || !list->get(3)->equals(createString("b"))) {
      printf("---[ArrayList Iterator Insert test4] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    auto iterator = list->getIterator();

    int sum = 0;
    bool isFirst = true;
    while(iterator->hasValue()) {
      sum += iterator->getValue();
      if(iterator->getValue() == 2 && isFirst) {
        iterator->insert(3);
        isFirst = false;
        continue;
      }
      iterator->next();
    }

    if(sum != 8) {
      printf("---[ArrayList Iterator Insert test5] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList Iterator Insert test100] [OK]--- \n");
}
