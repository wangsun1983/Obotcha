#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;


void testArrayList_InsertLast() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("c"));
    list2->add(createString("d"));
    list->insertLast(list2);

    if(list->size() != 4
      || !list->get(0)->equals("a")
      || !list->get(1)->equals("b")
      || !list->get(2)->equals("c")
      || !list->get(3)->equals("d")) {
        printf("---[ArrayList InsertLast test1] [FAILED]--- \n");
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

    list->insertLast(list2,2);
    printf("size is %d \n",list->size());
    printf("a1 %s,a2 %s,a3 %s,a4 %s \n",list->get(0)->toChars(),list->get(1)->toChars(),list->get(2)->toChars(),list->get(3)->toChars());
    if(list->size() != 4
      || !list->get(0)->equals("a")
      || !list->get(1)->equals("b")
      || !list->get(2)->equals("c")
      || !list->get(3)->equals("d")) {
      printf("---[ArrayList InsertLast test2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList InsertLast test100] [OK]--- \n");
}
