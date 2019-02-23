#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(TestClass1) {
public:
    int i;
    ~_TestClass1() {
      printf("release testclass1 \n");
    }
};

int main() {

  printf("---[Object Test Start]--- \n");
  //Test Construct
  {
      TestClass1 c1 = createTestClass1();
  }


}
