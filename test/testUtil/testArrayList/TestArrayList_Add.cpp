#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

DECLARE_CLASS(AddTestData) {
public:
  int data1;
  int data2;
};

void testArrayList_Add() {
  while(1) {
    ArrayList<AddTestData> list1 = createArrayList<AddTestData>();
    AddTestData d1 = createAddTestData();
    d1->data1 = 1;
    d1->data2 = 2;

    AddTestData d2 = createAddTestData();
    d2->data1 = 3;
    d2->data2 = 4;
    list1->add(d1);
    list1->add(d2);

    ArrayList<AddTestData> list2 = createArrayList<AddTestData>();
    list2->add(list1);

    AddTestData data = list2->get(0);
    if(data == nullptr || data->data1 != 1 ||data->data2 != 2) {
      printf("---[ArrayList add test1] [FAILED]--- \n");
    }

    data = list2->get(1);
    if(data == nullptr || data->data1 != 3 ||data->data2 != 4) {
      printf("---[ArrayList add test2] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    ArrayList<ArrayList<AddTestData>> list1 = createArrayList<ArrayList<AddTestData>>();
    AddTestData d1 = createAddTestData();
    d1->data1 = 1;
    d1->data2 = 2;

    AddTestData d2 = createAddTestData();
    d2->data1 = 3;
    d2->data2 = 4;

    ArrayList<AddTestData> l1 = createArrayList<AddTestData>();
    l1->add(d1);

    ArrayList<AddTestData> l2 = createArrayList<AddTestData>();
    l2->add(d2);

    list1->add(l1);
    list1->add(l2);

    ArrayList<ArrayList<AddTestData>> list2 = createArrayList<ArrayList<AddTestData>>();
    list2->add(list1);

    if(list2->size() != 2) {
      printf("---[ArrayList add test3] [FAILED]--- \n");
      break;
    }

    ArrayList<AddTestData> ll1 = list2->get(0);
    AddTestData ll1_data = ll1->get(0);
    if(ll1_data->data1 != 1 || ll1_data->data2 != 2) {
      printf("---[ArrayList add test4] [FAILED]--- \n");
      break;
    }

    ArrayList<AddTestData> ll2 = list2->get(1);
    AddTestData ll2_data = ll2->get(0);
    if(ll2_data->data1 != 3 || ll2_data->data2 != 4) {
      printf("---[ArrayList add test5] [FAILED]---,data1 is %d,data2 i %d \n",ll2_data->data1,ll2_data->data2);
      break;
    }
    break;
  }

  printf("---[ArrayList add test100] [OK]--- \n");
}
