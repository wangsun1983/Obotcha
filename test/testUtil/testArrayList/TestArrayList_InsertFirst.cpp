#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;


void testArrayList_InsertFirst() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("c"));
    list2->add(createString("d"));
    list->insertFirst(list2);

    if(list->size() != 4
      || !list->get(0)->equals("c")
      || !list->get(1)->equals("d")
      || !list->get(2)->equals("a")
      || !list->get(3)->equals("b")) {
        printf("---[ArrayList insertFirst test1] [FAILED]--- \n");
        break;
      }

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("c"));
    list2->add(createString("d"));
    list2->add(createString("e"));
    list2->add(createString("f"));

    list->insertFirst(list2,2);
    if(list->size() != 4
      || !list->get(0)->equals("c")
      || !list->get(1)->equals("d")
      || !list->get(2)->equals("a")
      || !list->get(3)->equals("b")) {
      printf("---[ArrayList insertFirst test2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("c"));
    bool isException = false;
    try {
      list->insertFirst(list2,2);
    } catch(...) {
      isException = true;
    }
    if(!isException) {
      printf("---[ArrayList insertFirst test3] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList insertFirst test100] [OK]--- \n");
}
