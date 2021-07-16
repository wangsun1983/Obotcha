#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TestDataRef) {
public:
  int i;
};

DECLARE_SIMPLE_CLASS(TestDataRef2) IMPLEMENTS(TestDataRef) {
public:
  int j;
};

int testReferenceCount() {
  //case 1
  while(1) {
    TestDataRef ref = createTestDataRef();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceCount test1-------[FAIL] \n");
      break;
    }

    TestDataRef ref2 = ref;
    if(ref->getStrongCount() != 2) {
      printf("Object ReferenceCount test2-------[FAIL] \n");
      break;
    }

    {
      TestDataRef ref3 = ref;
      if(ref->getStrongCount() != 3) {
        printf("Object ReferenceCount test3-------[FAIL] \n");
        break;
      }
    }

    if(ref->getStrongCount() != 2) {
        printf("Object ReferenceCount test4-------[FAIL] \n");
        break;
    }

    break;
  }

  //case 2
  while(1) {
    TestDataRef2 ref = createTestDataRef2();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceCount test5-------[FAIL] \n");
      break;
    }

    TestDataRef ref2 = ref;
    if(ref2->getStrongCount() != 2) {
      printf("Object ReferenceCount test6-------[FAIL] \n");
      break;
    }

    {
      TestDataRef ref3 = ref;
      if(ref->getStrongCount() != 3) {
        printf("Object ReferenceCount test7-------[FAIL] \n");
        break;
      }
    }

    if(ref->getStrongCount() != 2 || ref2->getStrongCount() != 2) {
        printf("Object ReferenceCount test8-------[FAIL] \n");
        break;
    }
    break;
  }

  //case 3
  while(1) {
    TestDataRef ref = createTestDataRef();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceCount test9-------[FAIL] \n");
      break;
    }

    TestDataRef ref2 = AutoClone(ref.get_pointer());
    if(ref2->getStrongCount() != 2) {
      printf("Object ReferenceCount test10-------[FAIL] \n");
      break;
    }

    TestDataRef ref3 = ref.get_pointer();
    if(ref2->getStrongCount() != 3) {
      printf("Object ReferenceCount test11-------[FAIL] \n");
      break;
    }

    if(ref3 == ref2) {
      if(ref3->getStrongCount() != 3) {
        printf("Object ReferenceCount test10-------[FAIL] \n");
        break;
      }
    }
    break;
  }

  //case 3
  while(1) {
    TestDataRef ref = createTestDataRef();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceCount test11-------[FAIL] \n");
      break;
    }

    TestDataRef ref2 = createTestDataRef();
    if(ref2->getStrongCount() != 1) {
      printf("Object ReferenceCount test12-------[FAIL] \n");
      break;
    }

    TestDataRef ref3 = ref;
    if(ref3->getStrongCount() != 2) {
      printf("Object ReferenceCount test13-------[FAIL] \n");
      break;
    }

    ref = ref2;
    if(ref3->getStrongCount() != 1) {
      printf("Object ReferenceCount test14-------[FAIL] \n");
      break;
    }

    if(ref2->getStrongCount() != 2) {
      printf("Object ReferenceCount test15-------[FAIL] \n");
      break;
    }
    
    break;
  }

  printf("Object ReferenceCount test100-------[OK] \n");
}
