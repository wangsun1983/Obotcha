#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

void testArrayList_Integer() {
  //--[_ArrayList<Integer> Test {add(Integer val)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(createInteger(1));
    list->add(createInteger(2));

    if(list->size() != 2) {
      printf("---[ArrayList<Integer> Test {add(Integer val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2) {
      printf("---[ArrayList<Integer> Test {add(Integer val)} case1] [FAILED]--- \n");
      break;
    }

    Integer t;
    int size = list->size();
    list->add(t);
    if(size != list->size()) {
      printf("---[ArrayList<Integer> Test {add(Integer val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {add(Integer val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {add(int val)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);

    if(list->size() != 2) {
      printf("---[ArrayList<Integer> Test {add(int val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2) {
      printf("---[ArrayList<Integer> Test {add(int val)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {add(int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {add(ArrayList<Integer> list)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);

    ArrayList<Integer>list2 = createArrayList<Integer>();
    list2->add(3);
    list2->add(4);
    list->add(list2);

    if(list->size() != 4) {
      printf("---[ArrayList<Integer> Test {add(ArrayList<Integer> list)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3
    ||list->get(3)->toValue() != 4) {
      printf("---[ArrayList<Integer> Test {add(ArrayList<Integer> list)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer>list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      printf("---[ArrayList<Integer> Test {add(ArrayList<Integer> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {add(ArrayList<Integer> val)}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Integer> Test {clear()} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    int size = list->size();
    list->clear();
    if(size == 0 || list->size() != 0) {
      printf("---[ArrayList<Integer> Test {clear()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {clear()}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Integer> Test {remove(int index)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    Integer i = list->remove(2);
    if(i->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {remove(int index)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2) {
      printf("---[ArrayList<Integer> Test {remove(int index)} case1] [FAILED]--- \n");
      break;
    }

    Integer i2 = list->remove(100);
    if(i2 != nullptr) {
      printf("---[ArrayList<Integer> Test {remove(int index)} case2] [FAILED]--- \n");
      break;
    }

    Integer i3 = list->remove(-1);
    if(i2 != nullptr) {
      printf("---[ArrayList<Integer> Test {remove(int index)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {remove(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {remove(Integer v)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    int result = list->remove(createInteger(2));
    if(result == -1) {
      printf("---[ArrayList<Integer> Test {remove(Integer v)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2
      ||list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 3){
        printf("---[ArrayList<Integer> Test {remove(Integer v)} case1] [FAILED]--- \n");
        break;
    }

    Integer t1 = createInteger(100);
    if(list->remove(t1) != -1) {
      printf("---[ArrayList<Integer> Test {remove(Integer v)} case2] [FAILED]--- \n");
      break;
    }

    Integer t2;
    int size = list->size();
    if(list->remove(t2) != -1) {
      printf("---[ArrayList<Integer> Test {remove(Integer v)} case3] [FAILED]--- \n");
      break;
    }

    if(size != list->size()) {
      printf("---[ArrayList<Integer> Test {remove(Integer v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {remove(Integer v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {indexOf(Integer v)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    if(list->indexOf(createInteger(1)) != 0
      ||list->indexOf(createInteger(2)) != 1
      ||list->indexOf(createInteger(3)) != 2) {
        printf("---[ArrayList<Integer> Test {indexOf(Integer v)} case0] [FAILED]--- \n");
        break;
    }

    if(list->indexOf(createInteger(100)) != -1) {
      printf("---[ArrayList<Integer> Test {indexOf(Integer v)} case1] [FAILED]--- \n");
      break;
    }

    Integer p;
    if(list->indexOf(p) != -1) {
      printf("---[ArrayList<Integer> Test {indexOf(Integer v)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {indexOf(Integer v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {set(int index,Integer val)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->set(0,createInteger(2));
    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {set(int index,Integer val)} case1] [FAILED]--- \n");
      break;
    }

    Integer t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Integer> Test {set(int index,Integer val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createInteger(1));
    if(result != -1) {
      printf("---[ArrayList<Integer> Test {set(int index,Integer val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {set(int index,Integer val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Integer> Test {set(int index,Integer val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {set(int index,Integer val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {set(int index,int val)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->set(0,2);
    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {set(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    Integer t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Integer> Test {set(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,1);
    if(result != -1) {
      printf("---[ArrayList<Integer> Test {set(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2
    ||list->get(1)->toValue() != 2
    ||list->get(2)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {set(int index,int val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Integer> Test {set(int index,int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {set(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {get(int index)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    Integer v1 = list->get(1);
    if(v1->toValue() != 2) {
      printf("---[ArrayList<Integer> Test {get(int index)} case0] [FAILED]--- \n");
      break;
    }

    Integer v2 = list->get(1000);
    if(v2 != nullptr) {
      printf("---[ArrayList<Integer> Test {get(int index)} case1] [FAILED]--- \n");
      break;
    }

    Integer v3 = list->get(-1);
    if(v3 != nullptr) {
      printf("---[ArrayList<Integer> Test {get(int index)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {get(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {insert(int index,Integer val)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insert(1,createInteger(4));
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 2
    ||list->get(3)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {insert(int index,Integer val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,createInteger(4));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,Integer val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createInteger(4));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,Integer val)} case2] [FAILED]--- \n");
      break;
    }

    Integer ii;
    result = list->insert(-1,ii);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,Integer val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insert(int index,Integer val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Integer> Test {insert(int index,int val)} Start]---
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insert(1,4);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 2
    ||list->get(3)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {insert(int index,int val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,4);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,4);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    int currentSize = list->size();
    list->insert(0,100);
    if(list->get(0)->toValue() != 100 && (list->size() != (currentSize + 1))) {
      printf("---[ArrayList<Integer> Test {insert(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insert(int index,int val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Integer> list);
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->add(4);
    list2->add(5);
    list2->add(6);

    list->insert(1,list2);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 5
    ||list->get(3)->toValue() != 6
    ||list->get(4)->toValue() != 2
    ||list->get(5)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case1] [FAILED]--- \n");
      break;
    }

    size = list->size();
    result = list->insert(-1,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer>list3 = createArrayList<Integer>();
    list3->add(10);
    list3->add(11);
    list3->add(12);

    ArrayList<Integer>list4 = createArrayList<Integer>();
    list4->add(13);
    list4->add(14);
    list4->add(15);

    list3->insert(0,list4);
    if(list3->get(0)->toValue() != 13
    ||list3->get(1)->toValue() != 14
    ||list3->get(2)->toValue() != 15
    ||list3->get(3)->toValue() != 10
    ||list3->get(4)->toValue() != 11
    ||list3->get(5)->toValue() != 12) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Integer> list,int length);
  while(1) {
    ArrayList<Integer>list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->add(4);
    list2->add(5);
    list2->add(6);

    list->insert(1,list2,2);
    if(list->get(0)->toValue() != 1
    ||list->get(1)->toValue() != 4
    ||list->get(2)->toValue() != 5
    ||list->get(3)->toValue() != 2
    ||list->get(4)->toValue() != 3) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2,5);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    size != list->size();
    result = list->insert(-1,list2,100);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer>list3 = createArrayList<Integer>();
    list3->add(10);
    list3->add(11);
    list3->add(12);

    ArrayList<Integer>list4 = createArrayList<Integer>();
    list4->add(13);
    list4->add(14);
    list4->add(15);

    list3->insert(0,list4,2);
    if(list3->get(0)->toValue() != 13
    ||list3->get(1)->toValue() != 14
    ||list3->get(2)->toValue() != 10
    ||list3->get(3)->toValue() != 11
    ||list3->get(4)->toValue() != 12) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case3] [FAILED]--- \n");
      break;
    }

    if(list3->size() != 5) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer>list5 = createArrayList<Integer>();
    list5->add(10);
    list5->add(11);
    list5->add(12);

    ArrayList<Integer>list6 = createArrayList<Integer>();
    list6->add(13);
    list6->add(14);
    list6->add(15);

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
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case5] [FAILED]--- \n");
      break;
    }

    if(list5->size() != 6) {
      printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)} case6] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insert(int index,ArrayList<Integer> list,int length)}] [OK]--- \n");
    break;
  }

  //void insertFirst(Integer val);
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertFirst(createInteger(4));
    if(list->get(0)->toValue() != 4
       ||list->get(1)->toValue() != 1
       ||list->get(2)->toValue() != 2
       ||list->get(3)->toValue() != 3) {
         printf("---[ArrayList<Integer> Test {insertFirst(Integer val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Integer> Test {insertFirst(Integer val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->insertFirst(createInteger(4));
    if(list2->get(0)->toValue() != 4) {
      printf("---[ArrayList<Integer> Test {insertFirst(Integer val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Integer> Test {insertFirst(Integer val)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list3 = createArrayList<Integer>();
    Integer nt;
    list3->insertFirst(nt);
    if(list3->size() != 0) {
      printf("---[ArrayList<Integer> Test {insertFirst(Integer val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insertFirst(Integer val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertFirst(4);
    if(list->get(0)->toValue() != 4
       ||list->get(1)->toValue() != 1
       ||list->get(2)->toValue() != 2
       ||list->get(3)->toValue() != 3) {
         printf("---[ArrayList<Integer> Test {insertFirst(int val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Integer> Test {insertFirst(int val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->insertFirst(4);
    if(list2->get(0)->toValue() != 4) {
      printf("---[ArrayList<Integer> Test {insertFirst(int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Integer> Test {insertFirst(int val)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insertFirst(int val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(ArrayList<Integer> list);
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->add(4);
    list2->add(5);
    list2->add(6);
    list->insertFirst(list2);

    if(list->get(0)->toValue() != 4
      ||list->get(1)->toValue() != 5
      ||list->get(2)->toValue() != 6
      ||list->get(3)->toValue() != 1
      ||list->get(4)->toValue() != 2
      ||list->get(5)->toValue() != 3) {
        printf("---[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case1] [FAILED]--- \n");
        break;
      }

    ArrayList<Integer> list3 = createArrayList<Integer>();
    list3->add(1);
    list3->add(2);

    ArrayList<Integer> list4 = createArrayList<Integer>();
    list4->insertFirst(list4);

    if(list3->get(0)->toValue() != 1
      ||list3->get(1)->toValue() != 2){
        printf("---[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case2] [FAILED]--- \n");
        break;
      }

    if(list3->size() != 2) {
      printf("---[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case3] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      printf("---[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insertFirst(ArrayList<Integer> list)}] [OK]--- \n");
    break;
  }

  //void insertLast(Integer v);
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertLast(createInteger(4));
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4) {
        printf("---[ArrayList<Integer> Test {insertLast(Integer v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Integer> Test {insertLast(Integer v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->add(1);
    list2->add(2);
    list2->add(3);
    Integer t2;
    list2->insertLast(t2);

    if(list2->get(0)->toValue() != 1
      ||list2->get(1)->toValue() != 2
      ||list2->get(2)->toValue() != 3) {
        printf("---[ArrayList<Integer> Test {insertLast(Integer v)} case3] [FAILED]--- \n");
        break;
    }

    if(list2->size() != 3) {
      printf("---[ArrayList<Integer> Test {insertLast(Integer v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insertLast(Integer v)} case5] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertLast(4);
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4) {
        printf("---[ArrayList<Integer> Test {insertLast(int v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Integer> Test {insertLast(int v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->insertLast(1);

    if(list2->size() != 1) {
      printf("---[ArrayList<Integer> Test {insertLast(int v)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->get(0)->toValue() != 1) {
      printf("---[ArrayList<Integer> Test {insertLast(int v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {insertLast(int v)} case5] [OK]--- \n");
    break;
  }

  //insertLast(ArrayList<Integer> list);
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<Integer> list2 = createArrayList<Integer>();
    list2->add(4);
    list2->add(5);
    list2->add(6);

    list->insertLast(list2);
    if(list->get(0)->toValue() != 1
      ||list->get(1)->toValue() != 2
      ||list->get(2)->toValue() != 3
      ||list->get(3)->toValue() != 4
      ||list->get(4)->toValue() != 5
      ||list->get(5)->toValue() != 6) {
        printf("---[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 6) {
        printf("---[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Integer> list3 = createArrayList<Integer>();
    list3->add(1);
    list3->add(2);
    list3->add(3);

    ArrayList<Integer> list4;
    list3->insertLast(list4);
    if(list3->get(0)->toValue() != 1
      ||list3->get(1)->toValue() != 2
      ||list3->get(2)->toValue() != 3) {
        printf("---[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case3] [FAILED]--- \n");
        break;
    }

    if(list3->size() != 3) {
        printf("---[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case4] [FAILED]--- \n");
        break;
    }

    printf("---[ArrayList<Integer> Test {insertLast(ArrayList<Integer> v)} case5] [OK]--- \n");
    break;
  }

  //int size();
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);
    if(list->size() != 3) {
      printf("---[ArrayList<Integer> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    if(list2->size() != 0) {
      printf("---[ArrayList<Integer> Test {size()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Integer> Test {size()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Integer> getValue;
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);

    ListIterator<Integer>iterator = list->getIterator();
    int index = 1;
    while(iterator->hasValue() && index != list->size()) {
      Integer v = iterator->getValue();
      if(v->toValue() != index) {
        printf("---[ListIterator<Integer> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      iterator->next();
      index++;
    }

    ArrayList<Integer> list1 = createArrayList<Integer>();
    ListIterator<Integer>iterator1 = list1->getIterator();
    Integer v = iterator1->getValue();
    if(v != nullptr) {
      printf("---[ListIterator<Integer> Test {getValue()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Integer> Test {getValue()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Integer> hasValue();
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);
    ListIterator<Integer> iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ListIterator<Integer> Test {hasValue()} case1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      printf("---[ListIterator<Integer> Test {hasValue()} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    ListIterator<Integer> iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      printf("---[ListIterator<Integer> Test {hasValue()} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Integer> Test {hasValue()} case4] [OK]--- \n");
    break;
  }

  // ListIterator<Integer> next();
  while(1) {
    ArrayList<Integer> list = createArrayList<Integer>();
    list->add(1);
    list->add(2);
    list->add(3);
    ListIterator<Integer> iterator = list->getIterator();

    iterator->next();
    iterator->next();
    if(iterator->next()) {
      printf("---[ListIterator<Integer> Test {next()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Integer> list2 = createArrayList<Integer>();
    ListIterator<Integer> iterator2 = list2->getIterator();
    if(iterator2->next()) {
      printf("---[ListIterator<Integer> Test {next()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Integer> Test {next()} case3] [OK]--- \n");
    break;
  }
}
