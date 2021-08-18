#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "LruCache.hpp"

using namespace obotcha;

DECLARE_CLASS(MyUpdateData) {
public:
  int i;

  ~_MyUpdateData() {
    //printf("release mydata : %d \n",i);
  }
};

int testLruUpdate() {
    //case 1
    while(1) {
      LruCache<String,MyUpdateData> lru = createLruCache<String,MyUpdateData>(3);
      for(int i = 0;i < 15;i++) {
        MyUpdateData d = createMyUpdateData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {update()} case1] [FAILED]--- \n");
        return 1;
      }

      //[14,13,12]
      MyUpdateData data1 = createMyUpdateData();
      data1->i = 15;
      lru->put(createString(15),data1);
      if(lru->size() != 3) {
        printf("---[LruCache Test {update()} case2] [FAILED]--- \n");
        return 1;
      }

      MyUpdateData m1 = lru->at(0); //15
      MyUpdateData m2 = lru->at(1); //14
      MyUpdateData m3 = lru->at(2); //13

      if(m1 == nullptr || m2 == nullptr || m3 == nullptr) {
        printf("---[LruCache Test {update()} case3] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 15 || m2->i != 14 || m3->i != 13) {
        printf("m1->i is %d,m2->i is %d,m3->i is %d \n",m1->i,m2->i,m3->i);
        printf("---[LruCache Test {update()} case4] [FAILED]--- \n");
        return 0;
      }
      printf("---[LruCache Test {update()} case4] [OK]--- \n");
      break;
    }

    //case 2
    while(1) {
      LruCache<String,MyUpdateData> lru = createLruCache<String,MyUpdateData>(3);
      for(int i = 0;i < 15;i++) {
        MyUpdateData d = createMyUpdateData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {update()} case5] [FAILED]--- \n");
        return 1;
      }

      //[14,13,12]
      MyUpdateData data1 = lru->get(createString(12)); //->[12,14,13]

      if(lru->size() != 3) {
        printf("---[LruCache Test {update()} case6] [FAILED]--- \n");
        return 1;
      }

      MyUpdateData m1 = lru->at(0); //12
      MyUpdateData m2 = lru->at(1); //14
      MyUpdateData m3 = lru->at(2); //13

      if(m1 == nullptr || m2 == nullptr || m3 == nullptr) {
        printf("---[LruCache Test {update()} case7] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 12 || m2->i != 14 || m3->i != 13) {
        printf("m1->i is %d,m2->i is %d,m3->i is %d \n",m1->i,m2->i,m3->i);
        printf("---[LruCache Test {update()} case8] [FAILED]--- \n");
        return 0;
      }
      printf("---[LruCache Test {update()} case9] [OK]--- \n");
      break;
    }

    //case 3
    while(1) {
      LruCache<String,MyUpdateData> lru = createLruCache<String,MyUpdateData>(3);
      for(int i = 0;i < 15;i++) {
        MyUpdateData d = createMyUpdateData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {update()} case10] [FAILED]--- \n");
        return 1;
      }

      //[14,13,12]
      MyUpdateData data1 = lru->get(createString(14)); //->[14,13,12]

      if(lru->size() != 3) {
        printf("---[LruCache Test {update()} case11] [FAILED]--- \n");
        return 1;
      }

      MyUpdateData m1 = lru->at(0); //12
      MyUpdateData m2 = lru->at(1); //14
      MyUpdateData m3 = lru->at(2); //13

      if(m1 == nullptr || m2 == nullptr || m3 == nullptr) {
        printf("---[LruCache Test {update()} case12] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 14 || m2->i != 13 || m3->i != 12) {
        printf("m1->i is %d,m2->i is %d,m3->i is %d \n",m1->i,m2->i,m3->i);
        printf("---[LruCache Test {update()} case13] [FAILED]--- \n");
        return 0;
      }
      printf("---[LruCache Test {update()} case14] [OK]--- \n");
      break;
    }

}
