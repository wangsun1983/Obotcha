#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

int TestClass1ReleaseTag = 1;

DECLARE_SIMPLE_CLASS(TestClass1) {
public:
    int i;
};

DECLARE_SIMPLE_CLASS(TestClass2) IMPLEMENTS(TestClass1) {
public:
  int j;
};

int main() {

  printf("---[Object Test Start]--- \n");
  //Test Construct
  {
      TestClass1 c1 = createTestClass1();
  }

  printf("---[Object Test nullptr check Start]--- \n");

  TestClass1 class1;
  if(class1 == nullptr) {
    printf("Object test null case 1-------[OK] \n");
  } else {
    printf("Object test null case 1-------[FAIL] \n");
  }

  if(class1 != nullptr) {
    printf("Object test null case 2-------[FAIL] \n");
  } else {
    printf("Object test null case 2-------[OK] \n");
  }

  class1 = createTestClass1();
  if(class1 == nullptr) {
    printf("Object test null case 3-------[FAIL] \n");
  } else {
    printf("Object test null case 3-------[OK] \n");
  }

  if(class1 != nullptr) {
    printf("Object test null case 3-------[OK] \n");
  } else {
    printf("Object test null case 3-------[FAIL] \n");
  }
}
