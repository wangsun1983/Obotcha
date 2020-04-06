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


int basetest() {

    //construct1
    while(1) {
      List<int> mylist1 = createList<int>(4);
      if(mylist1->size() != 4) {
        printf("List construct test1-------[FAIL] \n");
        break;
      }

      int v1 = mylist1[0];
      if(v1 != 0) {
        printf("List construct test2-------[FAIL] \n");
        break;
      }

      printf("List construct test3-------[OK] \n");
      break;
    }

    //construct2
    while(1) {
      int v[5];
      v[0] = 0;
      v[1] = 1;
      v[2] = 2;
      v[3] = 3;
      v[4] = 4;

      List<int> list1 = createList<int>(v,5);
      if(list1->size() != 5) {
        printf("List construct test4-------[FAIL] \n");
        break;
      }

      if(list1[0] != 0 ||
         list1[1] != 1 ||
         list1[2] != 2 ||
         list1[3] != 3 ||
         list1[4] != 4) {
           printf("List construct test5-------[FAIL] \n");
           break;
      }

      list1[0] = 100;
      list1[1] = 101;
      list1[2] = 102;
      list1[3] = 103;
      list1[4] = 104;

      if(list1[0] != 100 ||
         list1[1] != 101 ||
         list1[2] != 102 ||
         list1[3] != 103 ||
         list1[4] != 104) {
           printf("List construct test6-------[FAIL] \n");
           break;
      }

      printf("List construct test7-------[OK] \n");
      break;
    }

    //compare
    while(1) {
      List<int> list1 = createList<int>(2);
      List<int> list2 = createList<int>(2);
      if(list1 == list2) {
        printf("List equal test1-------[FAIL] \n");
        break;
      }

      printf("List equal test2-------[OK] \n");
      break;
    }

}
