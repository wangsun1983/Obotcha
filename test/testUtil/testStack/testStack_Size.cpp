#include <stdio.h>
#include <unistd.h>

#include "Stack.hpp"

using namespace obotcha;

DECLARE_CLASS(TestSizeData) {
public:
  _TestSizeData(int value) {
    v = value;
  }

  int v;
};

void testStackSize() {
  while(1) {
    Stack<int> stack = createStack<int>();
    stack->push(1);
    stack->push(2);

    if(stack->size() != 2) {
      printf("testStack size test1-------[FAIL] \n");
      break;
    }

    int v1 = stack->pop();
    int v2 = stack->pop();

    if(v1 != 2 || v2 != 1) {
      printf("testStack size test2-------[FAIL] \n");
      break;
    }

    bool isException = false;
    try {
      int v2 = stack->pop();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("testStack size test3-------[FAIL] \n");
      break;
    }
    break;
  }

  while(1) {
    Stack<TestSizeData> stack = createStack<TestSizeData>();
    stack->push(createTestSizeData(1));
    stack->push(createTestSizeData(2));

    if(stack->size() != 2) {
      printf("testStack size test4-------[FAIL] \n");
      break;
    }

    auto v1 = stack->pop();
    auto v2 = stack->pop();

    if(v1->v != 2 || v2->v != 1) {
      printf("testStack size test5-------[FAIL] \n");
      break;
    }
    auto v3 = stack->pop();

    if(v3 != nullptr) {
      printf("testStack size test6-------[FAIL] \n");
      break;
    }
    break;
  }
  printf("testStack size test100-------[OK] \n");
}
