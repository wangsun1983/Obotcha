#include <stdio.h>
#include <unistd.h>

#include "Stack.hpp"

using namespace obotcha;

DECLARE_CLASS(TestPushData) {
public:
  _TestPushData(int value) {
    v = value;
  }

  int v;
};

void testStackPush() {
  while(1) {
    Stack<int> ss = createStack<int>();

    for(int i = 0;i<1024*32;i++) {
      ss->push(i);
    }

    if(ss->size() != 1024*32) {
      printf("testStack push test1-------[FAILED] \n");
      break;
    }

    for(int i = 1024*32 - 1;i >= 0;i--) {
      if(ss->pop() != i) {
        printf("testStack push test2-------[FAILED] \n");
        break;
      }
    }
    break;
  }

  while(1) {
    Stack<TestPushData> ss = createStack<TestPushData>();

    for(int i = 0;i<1024*32;i++) {
      ss->push(createTestPushData(i));
    }

    if(ss->size() != 1024*32) {
      printf("testStack push test3-------[FAILED] \n");
      break;
    }

    for(int i = 1024*32 - 1;i >= 0;i--) {
      if(ss->pop()->v != i) {
        printf("testStack push test4-------[FAILED] \n");
        break;
      }
    }
    break;
  }
  printf("testStack push test100-------[OK] \n");
}
