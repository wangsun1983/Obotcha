#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Long.hpp"
#include "String.hpp"

using namespace obotcha;

void testArrayList_Long() {
  //--[_ArrayList<Long> Test {add(Long val)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));

    if(list->size() != 2) {
      printf("---[ArrayList<Long> Test {add(Long val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2) {
      printf("---[ArrayList<Long> Test {add(Long val)} case1] [FAILED]--- \n");
      break;
    }

    Long t;
    int size = list->size();
    list->add(t);
    if(size == list->size()) {
      printf("---[ArrayList<Long> Test {add(Long val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {add(Long val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {add(int val)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));

    if(list->size() != 2) {
      printf("---[ArrayList<Long> Test {add(int val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2) {
      printf("---[ArrayList<Long> Test {add(int val)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {add(int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {add(ArrayList<Long> list)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));

    ArrayList<Long>list2 = createArrayList<Long>();
    list2->add(createLong(3));
    list2->add(createLong(4));
    list->add(list2);

    if(list->size() != 4) {
      printf("---[ArrayList<Long> Test {add(ArrayList<Long> list)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3
    ||list->get(3)->toValue() != 4) {
      printf("---[ArrayList<Long> Test {add(ArrayList<Long> list)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Long>list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      printf("---[ArrayList<Long> Test {add(ArrayList<Long> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {add(ArrayList<Long> val)}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Long> Test {clear()} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    int size = list->size();
    list->clear();
    if(size == 0 || list->size() != 0) {
      printf("---[ArrayList<Long> Test {clear()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {clear()}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Long> Test {remove(int index)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    Long i = list->removeAt(2);
    if(i->toValue() != 3) {
      printf("---[ArrayList<Long> Test {remove(int index)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2) {
      printf("---[ArrayList<Long> Test {remove(int index)} case1] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
        Long i2 = list->removeAt(100);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<Long> Test {remove(int index)} case2] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
        Long i3 = list->removeAt(-1);
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<Long> Test {remove(int index)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {remove(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {remove(Long v)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    int result = list->remove(createLong(2));
    if(result == -1) {
      printf("---[ArrayList<Long> Test {remove(Long v)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2
      ||list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 3){
        printf("---[ArrayList<Long> Test {remove(Long v)} case1] [FAILED]--- \n");
        break;
    }

    Long t1 = createLong(100);
    if(list->remove(t1) != -1) {
      printf("---[ArrayList<Long> Test {remove(Long v)} case2] [FAILED]--- \n");
      break;
    }

    Long t2;
    int size = list->size();
    if(list->remove(t2) != -1) {
      printf("---[ArrayList<Long> Test {remove(Long v)} case3] [FAILED]--- \n");
      break;
    }

    if(size != list->size()) {
      printf("---[ArrayList<Long> Test {remove(Long v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {remove(Long v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {indexOf(Long v)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    if(list->indexOf(createLong(1)) != 0
      ||list->indexOf(createLong(2)) != 1
      ||list->indexOf(createLong(3)) != 2) {
        printf("---[ArrayList<Long> Test {indexOf(Long v)} case0] [FAILED]--- \n");
        break;
    }

    if(list->indexOf(createLong(100)) != -1) {
      printf("---[ArrayList<Long> Test {indexOf(Long v)} case1] [FAILED]--- \n");
      break;
    }

    Long p;
    if(list->indexOf(p) != -1) {
      printf("---[ArrayList<Long> Test {indexOf(Long v)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {indexOf(Long v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {set(int index,Long val)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->set(0,createLong(2));
    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {set(int index,Long val)} case1] [FAILED]--- \n");
      break;
    }

    Long t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Long> Test {set(int index,Long val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createLong(1));
    if(result != -1) {
      printf("---[ArrayList<Long> Test {set(int index,Long val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {set(int index,Long val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Long> Test {set(int index,Long val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {set(int index,Long val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {set(int index,int val)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->set(0,createLong(2));
    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {set(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    Long t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Long> Test {set(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createLong(1));
    if(result != -1) {
      printf("---[ArrayList<Long> Test {set(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {set(int index,int val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Long> Test {set(int index,int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {set(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {get(int index)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    Long v1 = list->get(1);
    if(v1->toValue() != 2) {
      printf("---[ArrayList<Long> Test {get(int index)} case0] [FAILED]--- \n");
      break;
    }

    Long v2 = list->get(1000);
    if(v2 != nullptr) {
      printf("---[ArrayList<Long> Test {get(int index)} case1] [FAILED]--- \n");
      break;
    }

    Long v3 = list->get(-1);
    if(v3 != nullptr) {
      printf("---[ArrayList<Long> Test {get(int index)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {get(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {insert(int index,Long val)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->insert(1,createLong(4));
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 2
    ||list->get(3)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {insert(int index,Long val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,createLong(4));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,Long val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createLong(4));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,Long val)} case2] [FAILED]--- \n");
      break;
    }

    Long ii;
    result = list->insert(-1,ii);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,Long val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insert(int index,Long val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Long> Test {insert(int index,int val)} Start]---
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->insert(1,createLong(4));
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 2
    ||list->get(3)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {insert(int index,int val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,createLong(4));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createLong(4));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    int currentSize = list->size();
    list->insert(0,createLong(100));
    if(list->get(0)->toValue() != 100 && (list->size() != (currentSize + 1))) {
      printf("---[ArrayList<Long> Test {insert(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insert(int index,int val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Long> list);
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->add(createLong(4));
    list2->add(createLong(5));
    list2->add(createLong(6));

    list->insert(1,list2);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 5
    ||list->get(3)->toValue() != 6
    ||list->get(4)->toValue() != 2
    ||list->get(5)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list)} case1] [FAILED]--- \n");
      break;
    }

    size = list->size();
    result = list->insert(-1,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Long>list3 = createArrayList<Long>();
    list3->add(createLong(10));
    list3->add(createLong(11));
    list3->add(createLong(12));

    ArrayList<Long>list4 = createArrayList<Long>();
    list4->add(createLong(13));
    list4->add(createLong(14));
    list4->add(createLong(15));

    list3->insert(0,list4);
    if(list3->get(0)->toValue() != 13
    ||list3->get(1)->toValue() != 14
    ||list3->get(2)->toValue() != 15
    ||list3->get(3)->toValue() != 10
    ||list3->get(4)->toValue() != 11
    ||list3->get(5)->toValue() != 12) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Long> list,int length);
  while(1) {
    ArrayList<Long>list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->add(createLong(4));
    list2->add(createLong(5));
    list2->add(createLong(6));

    list->insert(1,list2,2);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 5
    ||list->get(3)->toValue() != 2
    ||list->get(4)->toValue() != 3) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2,5);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    size != list->size();
    result = list->insert(-1,list2,100);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Long>list3 = createArrayList<Long>();
    list3->add(createLong(10));
    list3->add(createLong(11));
    list3->add(createLong(12));

    ArrayList<Long>list4 = createArrayList<Long>();
    list4->add(createLong(13));
    list4->add(createLong(14));
    list4->add(createLong(15));

    list3->insert(0,list4,2);
    if(list3->get(0)->toValue() != 13
    ||list3->get(1)->toValue() != 14
    ||list3->get(2)->toValue() != 10
    ||list3->get(3)->toValue() != 11
    ||list3->get(4)->toValue() != 12) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case3] [FAILED]--- \n");
      break;
    }

    if(list3->size() != 5) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Long>list5 = createArrayList<Long>();
    list5->add(createLong(10));
    list5->add(createLong(11));
    list5->add(createLong(12));

    ArrayList<Long>list6 = createArrayList<Long>();
    list6->add(createLong(13));
    list6->add(createLong(14));
    list6->add(createLong(15));

    result = list5->insert(0,list6,100);

#if 0
    printf("list5[0] is %d \n",list5->get(0)->toValue());
    printf("list5[1] is %d \n",list5->get(1)->toValue());
    printf("list5[2] is %d \n",list5->get(2)->toValue());
    printf("list5[3] is %d \n",list5->get(3)->toValue());
    printf("list5[4] is %d \n",list5->get(4)->toValue());
    printf("list5[5] is %d \n",list5->get(5)->toValue());
#endif

    if(list5->get(0)->toValue() != 13
      ||list5->get(1)->toValue() != 14
      ||list5->get(2)->toValue() != 15
      ||list5->get(3)->toValue() != 10
      ||list5->get(4)->toValue() != 11
      ||list5->get(5)->toValue() != 12) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case5] [FAILED]--- \n");
      break;
    }

    if(list5->size() != 6) {
      printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)} case6] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insert(int index,ArrayList<Long> list,int length)}] [OK]--- \n");
    break;
  }

  //void insertFirst(Long val);
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->insertFirst(createLong(4));
    if(list->get(0)->toValue() != 4
       ||list->get(1)->toValue() != 1
       ||list->get(2)->toValue() != 2
       ||list->get(3)->toValue() != 3) {
         printf("---[ArrayList<Long> Test {insertFirst(Long val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Long> Test {insertFirst(Long val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->insertFirst(createLong(4));
    if(list2->get(0)->toValue() != 4) {
      printf("---[ArrayList<Long> Test {insertFirst(Long val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Long> Test {insertFirst(Long val)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list3 = createArrayList<Long>();
    Long nt;
    list3->insertFirst(nt);
    if(list3->size() == 0) {
      printf("---[ArrayList<Long> Test {insertFirst(Long val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insertFirst(Long val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->insertFirst(createLong(4));
    if(list->get(0)->toValue() != 4
       ||list->get(1)->toValue() != 1
       ||list->get(2)->toValue() != 2
       ||list->get(3)->toValue() != 3) {
         printf("---[ArrayList<Long> Test {insertFirst(int val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Long> Test {insertFirst(int val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->insertFirst(createLong(4));
    if(list2->get(0)->toValue() != 4) {
      printf("---[ArrayList<Long> Test {insertFirst(int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Long> Test {insertFirst(int val)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insertFirst(int val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(ArrayList<Long> list);
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->add(createLong(4));
    list2->add(createLong(5));
    list2->add(createLong(6));
    list->insertFirst(list2);

    if(list->get(0)->toValue() != 4
      ||list->get(1)->toValue() != 5
      ||list->get(2)->toValue() != 6
      ||list->get(3)->toValue() != 1
      ||list->get(4)->toValue() != 2
      ||list->get(5)->toValue() != 3) {
        printf("---[ArrayList<Long> Test {insertFirst(ArrayList<Long> list)} case1] [FAILED]--- \n");
        break;
      }

    ArrayList<Long> list3 = createArrayList<Long>();
    list3->add(createLong(1));
    list3->add(createLong(2));

    ArrayList<Long> list4 = createArrayList<Long>();
    list4->insertFirst(list4);

    if(list3->get(0)->toValue() != 1
      ||list3->get(1)->toValue() != 2){
        printf("---[ArrayList<Long> Test {insertFirst(ArrayList<Long> list)} case2] [FAILED]--- \n");
        break;
      }

    if(list3->size() != 2) {
      printf("---[ArrayList<Long> Test {insertFirst(ArrayList<Long> list)} case3] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      printf("---[ArrayList<Long> Test {insertFirst(ArrayList<Long> list)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insertFirst(ArrayList<Long> list)}] [OK]--- \n");
    break;
  }

  //void insertLast(Long v);
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->insertLast(createLong(4));
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4) {
        printf("---[ArrayList<Long> Test {insertLast(Long v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Long> Test {insertLast(Long v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->add(createLong(1));
    list2->add(createLong(2));
    list2->add(createLong(3));
    Long t2;
    list2->insertLast(t2);

    if(list2->get(0)->toValue() != 1
      ||list2->get(1)->toValue() != 2
      ||list2->get(2)->toValue() != 3) {
        printf("---[ArrayList<Long> Test {insertLast(Long v)} case3] [FAILED]--- \n");
        break;
    }

    if(list2->size() != 4) {
      printf("---[ArrayList<Long> Test {insertLast(Long v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insertLast(Long v)} case5] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    list->insertLast(createLong(4));
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4) {
        printf("---[ArrayList<Long> Test {insertLast(int v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Long> Test {insertLast(int v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->insertLast(createLong(1));

    if(list2->size() != 1) {
      printf("---[ArrayList<Long> Test {insertLast(int v)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->get(0)->toValue() != 1) {
      printf("---[ArrayList<Long> Test {insertLast(int v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {insertLast(int v)} case5] [OK]--- \n");
    break;
  }

  //insertLast(ArrayList<Long> list);
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));

    ArrayList<Long> list2 = createArrayList<Long>();
    list2->add(createLong(4));
    list2->add(createLong(5));
    list2->add(createLong(6));

    list->insertLast(list2);
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4
      ||list->get(4)->toValue() != 5
      ||list->get(5)->toValue() != 6) {
        printf("---[ArrayList<Long> Test {insertLast(ArrayList<Long> v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 6) {
        printf("---[ArrayList<Long> Test {insertLast(ArrayList<Long> v)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Long> list3 = createArrayList<Long>();
    list3->add(createLong(1));
    list3->add(createLong(2));
    list3->add(createLong(3));

    ArrayList<Long> list4;
    list3->insertLast(list4);
    if(list3->get(0)->toValue() != 1
      ||list3->get(1)->toValue() != 2
      ||list3->get(2)->toValue() != 3) {
        printf("---[ArrayList<Long> Test {insertLast(ArrayList<Long> v)} case3] [FAILED]--- \n");
        break;
    }

    if(list3->size() != 3) {
        printf("---[ArrayList<Long> Test {insertLast(ArrayList<Long> v)} case4] [FAILED]--- \n");
        break;
    }

    printf("---[ArrayList<Long> Test {insertLast(ArrayList<Long> v)} case5] [OK]--- \n");
    break;
  }

  //int size();
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));
    if(list->size() != 3) {
      printf("---[ArrayList<Long> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    if(list2->size() != 0) {
      printf("---[ArrayList<Long> Test {size()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Long> Test {size()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Long> getValue;
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));
    list->add(createLong(4));
    list->add(createLong(5));

    ListIterator<Long>iterator = list->getIterator();
    int index = 1;
    while(iterator->hasValue() && index != list->size()) {
      Long v = iterator->getValue();
      if(v->toValue() != index) {
        printf("---[ListIterator<Long> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      iterator->next();
      index++;
    }

    ArrayList<Long> list1 = createArrayList<Long>();
    ListIterator<Long>iterator1 = list1->getIterator();
    Long v = iterator1->getValue();
    if(v != nullptr) {
      printf("---[ListIterator<Long> Test {getValue()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Long> Test {getValue()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Long> hasValue();
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));
    ListIterator<Long> iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ListIterator<Long> Test {hasValue()} case1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      printf("---[ListIterator<Long> Test {hasValue()} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    ListIterator<Long> iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      printf("---[ListIterator<Long> Test {hasValue()} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Long> Test {hasValue()} case4] [OK]--- \n");
    break;
  }

  // ListIterator<Long> next();
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));
    ListIterator<Long> iterator = list->getIterator();

    iterator->next();
    iterator->next();
    if(iterator->next()) {
      printf("---[ListIterator<Long> Test {next()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Long> list2 = createArrayList<Long>();
    ListIterator<Long> iterator2 = list2->getIterator();
    if(iterator2->next()) {
      printf("---[ListIterator<Long> Test {next()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Long> Test {next()} case3] [OK]--- \n");
    break;
  }

  //--[_ListIterator<Long> Test {remove()} Start]---
  while(1) {
    ArrayList<Long> list = createArrayList<Long>();
    list->add(createLong(1));
    list->add(createLong(2));
    list->add(createLong(3));
    list->add(createLong(4));
    list->add(createLong(5));
    ListIterator<Long> iterator = list->getIterator();
    while(iterator->hasValue()) {
      if(iterator->getValue()->toValue() == 3) {
        iterator->remove();
      }else {
        iterator->next();
      }
    }

    if(list->size() != 4) {
        printf("---[ListIterator<Long> Test {remove()} case0] [FAILED]--- \n");
        break;
    }

    if(list->get(0)->toValue() != 1 ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 4||list->get(3)->toValue() != 5) {
        printf("---[ListIterator<Long> Test {remove()} case2] [FAILED]--- \n");
        break;
    }

    printf("---[ListIterator<Long> Test {remove()} case3] [OK]--- \n");
    break;
  }
}
