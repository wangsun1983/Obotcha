#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;


void testArrayList_Construct() {
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    if(list->size() != 0) {
      printf("---[ArrayList construct test1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    ArrayList<String> list2 = createArrayList<String>(list);
    if(list2->size() != 3) {
      printf("---[ArrayList construct test2] [FAILED]--- \n");
      break;
    }

    if(!list2->get(0)->equals("a") ||!list2->get(1)->equals("b") ||!list2->get(2)->equals("c")) {
      printf("---[ArrayList construct test3] [FAILED]--- \n");
      break;
    }

    list->add(createString("d"));
    if(list2->size() != 3 || list->size() != 4) {
      printf("---[ArrayList construct test4] [FAILED]--- \n");
      break;
    }

    break;
  }
  printf("---[ArrayList construct test100] [OK]--- \n");
}
