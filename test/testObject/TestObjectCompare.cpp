#include <stdio.h>
#include <unistd.h>
#include <iostream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

int TestClass1ReleaseTag = 1;

//#define InstanceOf(X,Y) typeid(X->getPointer()) == typeid(_##Y)

using namespace obotcha;

//#define InstanceOf(X,Y) typeid(*X.get_pointer()) == typeid(_##Y)


DECLARE_SIMPLE_CLASS(TestClass1) {
public:
    int i;
};

DECLARE_SIMPLE_CLASS(TestClass2) IMPLEMENTS(TestClass1) {
public:
  int j;
};

DECLARE_SIMPLE_CLASS(TestClass3) IMPLEMENTS(TestClass1) {
public:
  int j;
};

int testObjectCompare() {
/*
    TestClass1 t = createTestClass1();
    TestClass1 t2 = createTestClass1();

    std::cout<<"id is "<< typeid(*t.get_pointer()).name()<<std::endl;
    std::cout<<"id is "<< typeid(_TestClass1).name()<<std::endl;

    if(InstanceOf(t,TestClass3)) {
      printf("yes it is  \n");
    } else {
      printf("no it is not\n");
    }
*/
}
