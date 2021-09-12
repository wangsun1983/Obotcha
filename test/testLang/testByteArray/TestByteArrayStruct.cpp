#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

using namespace obotcha;

struct MyData {
int data1;
long data2;
int data3;
};

void testByteArrayStruct() {
  while(1) {
    ByteArray array = createByteArray(sizeof(MyData));
    MyData *p = array->get<MyData>();
    p->data1 = 1;
    p->data2 = 2;
    p->data3 = 100;

    MyData *p2 = array->get<MyData>();
    if(p2->data1 != 1 || p2->data2 != 2 || p2->data3 != 100) {
      printf("ByteArray test Struct test 1-------[FAILED],data1 is %d,data2 is %ld,data3 is %d \n",
            p2->data1,p2->data2,p2->data3);
    }
    break;
  }

  while(1) {
    ByteArray array = createByteArray(1024);
    MyData p;
    p.data1 = 1;
    p.data2 = 2;
    p.data3 = 100;
    array->apply(&p);

    MyData *p2 = array->get<MyData>();
    if(p2->data1 != 1 || p2->data2 != 2 || p2->data3 != 100) {
      printf("ByteArray test Struct test 2-------[FAILED],data1 is %d,data2 is %ld,data3 is %d \n",
            p2->data1,p2->data2,p2->data3);
    }
    break;
  }

  while(1) {
    ByteArray array = st(ByteArray)::alloc<MyData>();
    MyData *p = array->get<MyData>();
    p->data1 = 1;
    p->data2 = 2;
    p->data3 = 100;

    MyData *p2 = array->get<MyData>();
    if(p2->data1 != 1 || p2->data2 != 2 || p2->data3 != 100) {
      printf("ByteArray test Struct test 3-------[FAILED],data1 is %d,data2 is %ld,data3 is %d \n",
            p2->data1,p2->data2,p2->data3);
    }
    break;
  }

  printf("ByteArray test Struct test 100-------[OK] \n");
}
