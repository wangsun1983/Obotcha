#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "LruCache.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyData) {
public:
  int i;

  ~_MyData() {
    //printf("release mydata : %d \n",i);
  }
};

int testLruAdd() {

    //case 1
    while(1) {
      LruCache<String,MyData> lru = createLruCache<String,MyData>(3);
      for(int i = 0;i < 15;i++) {
        MyData d = createMyData();
        d->i = i;
        lru->put(createString(i),d);
      }

      if(lru->size() != 3) {
        printf("---[LruCache Test {put()} case1] [FAILED]--- \n");
        return 1;
      }

      MyData m1 = lru->get(createString(14));
      MyData m2 = lru->get(createString(13));
      MyData m3 = lru->get(createString(12));

      if(m1 == nullptr || m2 == nullptr || m3 == nullptr) {
        printf("---[LruCache Test {put()} case2] [FAILED]--- \n");
        return 1;
      }

      if(m1->i != 14 && m2->i != 13 && m3->i != 12) {
        printf("---[LruCache Test {put()} case3] [FAILED]--- \n");
        return 1;
      }

      printf("---[LruCache Test {put()} case4] [OK]--- \n");
      break;
    }

    //case 2
    while(1) {
      LruCache<String,MyData> lru = createLruCache<String,MyData>(3);
      for(int i = 0;i < 15;i++) {
        MyData d = createMyData();
        d->i = i;
        lru->put(createString(i),d);
      }

      MyData m1 = lru->at(0); //14
      MyData m2 = lru->at(1); //13
      MyData m3 = lru->at(2); //12
      if(m1->i != 14 && m2->i != 13 && m3->i != 12) {
        printf("---[LruCache Test {put()} case5] [FAILED]--- \n");
        return 1;
      }

      lru->get(createString(13));
      m1 = lru->at(0); //13
      m2 = lru->at(1); //14
      m3 = lru->at(2); //12
      if(m1->i != 13 && m2->i != 14 && m3->i != 12) {
        printf("---[LruCache Test {put()} case6] [FAILED]--- \n");
        return 1;
      }

      lru->get(createString(12));
      m1 = lru->at(0); //12
      m2 = lru->at(1); //13
      m3 = lru->at(2); //14
      if(m1->i != 12 && m2->i != 13 && m3->i != 14) {
        printf("---[LruCache Test {put()} case7] [FAILED]--- \n");
        return 1;
      }

      lru->get(createString(14));
      m1 = lru->at(0); //14
      m2 = lru->at(1); //12
      m3 = lru->at(2); //13
      if(m1->i != 14 && m2->i != 12 && m3->i != 13) {
        printf("---[LruCache Test {put()} case8] [FAILED]--- \n");
        return 1;
      }

      printf("---[LruCache Test {put()} case9] [OK]--- \n");
      break;
    }
}
