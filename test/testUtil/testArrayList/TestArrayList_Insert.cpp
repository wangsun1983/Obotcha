#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;


void testArrayList_Insert() {
  //int insert(int index,const T val)
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->insert(0,createString("c"));
    if(list->size() != 3 || !list->get(0)->equals("c")
      || !list->get(1)->equals("a")|| !list->get(2)->equals("b")) {
      printf("---[ArrayList Insert test1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->insert(0,createString("c"));
    if(list->size() != 1 || !list->get(0)->equals("c")) {
      printf("---[ArrayList Insert test2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->insert(0,createString("c"));
    list->insert(1,createString("d"));
    if(list->size() != 2 || !list->get(0)->equals("c") || !list->get(1)->equals("d")) {
      printf("---[ArrayList Insert test3] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    bool isException = false;
    try {
      list->insert(1,createString("c"));
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[ArrayList Insert test4] [FAILED]--- \n");
      break;
    }
    break;
  }

  //int insert(int index,const ArrayList<T> &list)
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("c"));
    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("a"));
    list2->add(createString("b"));
    list->insert(0,list2);
    if(list->size() != 3 || !list->get(0)->equals("a")
      || !list->get(1)->equals("b")|| !list->get(2)->equals("c")) {
      printf("---[ArrayList Insert test5] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("a"));
    list2->add(createString("b"));
    list->insert(0,list2);
    if(list->size() != 2 || !list->get(0)->equals("a")
      || !list->get(1)->equals("b")) {
      printf("---[ArrayList Insert test6] [FAILED]--- \n");
      break;
    }

    list2->clear();
    if(list->size() != 2 || !list->get(0)->equals("a")
      || !list->get(1)->equals("b")) {
      printf("---[ArrayList Insert test7] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("c"));
    list->add(createString("d"));
    list->add(createString("e"));

    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("a"));
    list2->add(createString("b"));
    list->insert(2,list2);
    if(list->size() != 5 || !list->get(0)->equals("c")
      || !list->get(1)->equals("d")
      || !list->get(2)->equals("a")
      || !list->get(3)->equals("b")
      || !list->get(4)->equals("e")
      ) {
      printf("---[ArrayList Insert test8] [FAILED]--- \n");
      break;
    }
    break;
  }

  //int insert(int index,const ArrayList<T> &list,int length)
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("c"));
    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("a"));
    list2->add(createString("b"));
    list->insert(0,list2,1);
    if(list->size() != 2 || !list->get(0)->equals("a")
      || !list->get(1)->equals("c")) {
      printf("---[ArrayList Insert test9] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("a"));
    list2->add(createString("b"));
    list->insert(0,list2,1);
    if(list->size() != 1 || !list->get(0)->equals("a")) {
      printf("---[ArrayList Insert test10] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ArrayList<String> list = createArrayList<String>();
    ArrayList<String> list2 = createArrayList<String>();
    list2->add(createString("a"));
    list2->add(createString("b"));
    bool isException = false;
    try {
      list->insert(0,list2,12);
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[ArrayList Insert test11] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[ArrayList Insert test100] [OK]--- \n");
}
