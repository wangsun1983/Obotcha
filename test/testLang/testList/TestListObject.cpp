#include <stdio.h>
#include <unistd.h>
#include <vector>
//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "Uint8.hpp"
#include "List.hpp"

using namespace std;
using namespace obotcha;

DECLARE_CLASS(MyData) {
public:
  int i;
  int j;
};

void listobjecttest() {
  //construct1
  while(1) {
    List<MyData> mylist1 = createList<MyData>(4);
    if(mylist1->size() != 4) {
      printf("List Object construct test1-------[FAIL] \n");
      break;
    }

    MyData v1 = mylist1[0];
    if(v1 != nullptr) {
      printf("List Object construct test2-------[FAIL] \n");
      break;
    }

    printf("List Object construct test3-------[OK] \n");
    break;
  }

  //construct2
  while(1) {
    MyData vlist[5];
    for(int i = 0;i < 5;i++) {
      MyData v = createMyData();
      v->i = i;
      v->j = i;
      vlist[i] = v;
    }

    List<MyData> list1 = createList<MyData>(vlist,5);
    if(list1->size() != 5) {
      printf("List Object construct test4-------[FAIL] \n");
      break;
    }

    for(int i = 0;i<5;i++) {
      MyData v = vlist[i];
      if(v->i != i ||v->j != i) {
        printf("List Object construct test5-------[FAIL] \n");
        break;
      }
    }

    for(int i = 0;i<5;i++) {
      MyData v = vlist[i];
      v->i = i*100;
      v->j = i*100;
    }

    for(int i = 0;i<5;i++) {
      MyData v = vlist[i];
      if(v->i != i*100 ||v->j != i*100) {
        printf("List Object construct test6-------[FAIL] \n");
        break;
      }
    }

    printf("List Object construct test7-------[OK] \n");
    break;
  }

  //nullptr set
  while(1) {
    List<MyData> list1 = createList<MyData>(2);
    MyData data1 = createMyData();
    data1->i = 1;
    data1->j = 1;
    list1[0] = data1;
    list1[1] = data1;

    list1[0] = nullptr;
    MyData data1_1 = list1[0];
    if(data1_1 != nullptr) {
      printf("List Object set null test1-------[FAIL] \n");
      break;
    }

    printf("List Object set null test2-------[OK] \n");
    break;
  }
}
