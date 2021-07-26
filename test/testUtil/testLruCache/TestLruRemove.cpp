#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "LruCache.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyTestData) {
public:
  int i;

  ~_MyTestData() {
    //printf("release mydata : %d \n",i);
  }
};

int testLruRemove() {

    //case 1
    while(1) {
      LruCache<String,MyTestData> lru = createLruCache<String,MyTestData>(3);
      for(int i = 0;i < 15;i++) {
        MyTestData d = createMyTestData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {remove()} case1] [FAILED]--- \n");
        return 1;
      }
      //[14,13,12]
      lru->remove(createString(14));
      if(lru->size() != 2) {
        printf("---[LruCache Test {remove()} case2] [FAILED]--- \n");
        return 1;
      }

      MyTestData m1 = lru->at(0); //13
      MyTestData m2 = lru->at(1); //12
      if(m1 == nullptr || m2 == nullptr) {
        printf("---[LruCache Test {remove()} case3] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 13 || m2->i != 12) {
        printf("m1->i is %d,m2->i is %d \n",m1->i,m2->i);
        printf("---[LruCache Test {remove()} case4] [FAILED]--- \n");
        return 1;
      }
      printf("---[LruCache Test {remove()} case4] [OK]--- \n");
      break;
    }

    //case 2
    while(1) {
      LruCache<String,MyTestData> lru = createLruCache<String,MyTestData>(3);
      for(int i = 0;i < 15;i++) {
        MyTestData d = createMyTestData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {remove()} case5] [FAILED]--- \n");
        return 1;
      }
      //[14,13,12]
      lru->remove(createString(13));
      if(lru->size() != 2) {
        printf("---[LruCache Test {remove()} case6] [FAILED]--- \n");
        return 1;
      }

      MyTestData m1 = lru->at(0); //14
      MyTestData m2 = lru->at(1); //12
      if(m1 == nullptr || m2 == nullptr) {
        printf("---[LruCache Test {remove()} case7] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 14 || m2->i != 12) {
        printf("m1->i is %d,m2->i is %d \n",m1->i,m2->i);
        printf("---[LruCache Test {remove()} case8] [FAILED]--- \n");
        return 1;
      }
      printf("---[LruCache Test {remove()} case9] [OK]--- \n");
      break;
    }

    //case 3
    while(1) {
      LruCache<String,MyTestData> lru = createLruCache<String,MyTestData>(3);
      for(int i = 0;i < 15;i++) {
        MyTestData d = createMyTestData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {remove()} case10] [FAILED]--- \n");
        return 1;
      }
      //[14,13,12]
      lru->remove(createString(12));
      if(lru->size() != 2) {
        printf("---[LruCache Test {remove()} case11] [FAILED]--- \n");
        return 1;
      }

      MyTestData m1 = lru->at(0); //14
      MyTestData m2 = lru->at(1); //13
      if(m1 == nullptr || m2 == nullptr) {
        printf("---[LruCache Test {remove()} case12] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 14 || m2->i != 13) {
        printf("m1->i is %d,m2->i is %d \n",m1->i,m2->i);
        printf("---[LruCache Test {remove()} case13] [FAILED]--- \n");
        return 1;
      }

      printf("---[LruCache Test {remove()} case14] [OK]--- \n");
      break;
    }

}
