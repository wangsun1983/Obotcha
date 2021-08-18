#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

DECLARE_CLASS(ContainerData) {
public:
  int i;
};

DECLARE_CLASS(ContainerData2) IMPLEMENTS(ContainerData) {
public:
  int j;
};

int testReferenceArraylist() {
  //case 1
  while(1) {
    ContainerData ref = createContainerData();
    ArrayList<ContainerData> list = createArrayList<ContainerData>();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceArraylistCount test1-------[FAIL] \n");
      break;
    }

    list->add(ref);
    if(ref->getStrongCount() != 2) {
      printf("Object ReferenceArraylistCount test2-------[FAIL] \n");
      break;
    }

    list->clear();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceArraylistCount test3-------[FAIL] \n");
      break;
    }

    break;
  }

  //case 1
  while(1) {
    ContainerData2 ref = createContainerData2();
    ArrayList<ContainerData> list = createArrayList<ContainerData>();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceArraylistCount test4-------[FAIL] \n");
      break;
    }

    list->add(Cast<ContainerData>(ref));
    if(ref->getStrongCount() != 2) {
      printf("Object ReferenceArraylistCount test5-------[FAIL] \n");
      break;
    }

    list->clear();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceArraylistCount test6-------[FAIL] \n");
      break;
    }

    break;
  }


  printf("Object ReferenceArraylistCount test100-------[OK] \n");
}
