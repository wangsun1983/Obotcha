#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Float.hpp"
#include "String.hpp"
#include "Float.hpp"

using namespace obotcha;

void testArrayList_Float() {
  //--[_ArrayList<Float> Test {add(Float val)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(createFloat(1.1));
    list->add(createFloat(2.1));

    if(list->size() != 2) {
      printf("---[ArrayList<Float> Test {add(Float val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 2.1f) {
      printf("---[ArrayList<Float> Test {add(Float val)} case1] [FAILED]--- \n");
      break;
    }

    Float t;
    int size = list->size();
    list->add(t);
    if(size != list->size()) {
      printf("---[ArrayList<Float> Test {add(Float val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {add(Float val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {add(float val)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);

    if(list->size() != 2) {
      printf("---[ArrayList<Float> Test {add(float val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 2.1f) {
      printf("---[ArrayList<Float> Test {add(float val)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {add(float val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {add(ArrayList<Float> list)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);

    ArrayList<Float>list2 = createArrayList<Float>();
    list2->add(3.1);
    list2->add(4.1);

    list->add(list2);

    if(list->size() != 4) {
      printf("---[ArrayList<Float> Test {add(ArrayList<Float> list)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 2.1f
    ||list->get(2)->toValue() != 3.1f
    ||list->get(3)->toValue() != 4.1f) {
      printf("---[ArrayList<Float> Test {add(ArrayList<Float> list)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Float>list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      printf("---[ArrayList<Float> Test {add(ArrayList<Float> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {add(ArrayList<Float> val)}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Float> Test {clear()} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    int size = list->size();
    list->clear();
    if(size == 0 || list->size() != 0) {
      printf("---[ArrayList<Float> Test {clear()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {clear()}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Float> Test {remove(int index)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    Float i = list->remove(2);
    if(i->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {remove(int index)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2) {
      printf("---[ArrayList<Float> Test {remove(int index)} case1] [FAILED]--- \n");
      break;
    }

    Float i2 = list->remove(100);
    if(i2 != nullptr) {
      printf("---[ArrayList<Float> Test {remove(int index)} case2] [FAILED]--- \n");
      break;
    }

    Float i3 = list->remove(-1);
    if(i2 != nullptr) {
      printf("---[ArrayList<Float> Test {remove(int index)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {remove(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {remove(Float v)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    int result = list->remove(createFloat(2.1));
    if(result == -1) {
      printf("---[ArrayList<Float> Test {remove(Float v)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2
      ||list->get(0)->toValue() != 1.1f
      ||list->get(1)->toValue() != 3.1f){
        printf("---[ArrayList<Float> Test {remove(Float v)} case1] [FAILED]--- \n");
        break;
    }

    Float t1 = createFloat(100);
    if(list->remove(t1) != -1) {
      printf("---[ArrayList<Float> Test {remove(Float v)} case2] [FAILED]--- \n");
      break;
    }

    Float t2;
    int size = list->size();
    if(list->remove(t2) != -1) {
      printf("---[ArrayList<Float> Test {remove(Float v)} case3] [FAILED]--- \n");
      break;
    }

    if(size != list->size()) {
      printf("---[ArrayList<Float> Test {remove(Float v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {remove(Float v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {indexOf(Float v)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    if(list->indexOf(createFloat(1.1)) != 0
      ||list->indexOf(createFloat(2.1)) != 1
      ||list->indexOf(createFloat(3.1)) != 2) {
        printf("---[ArrayList<Float> Test {indexOf(Float v)} case0] [FAILED]--- \n");
        break;
    }

    if(list->indexOf(createFloat(100.1)) != -1) {
      printf("---[ArrayList<Float> Test {indexOf(Float v)} case1] [FAILED]--- \n");
      break;
    }

    Float p;
    if(list->indexOf(p) != -1) {
      printf("---[ArrayList<Float> Test {indexOf(Float v)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {indexOf(Float v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {set(int index,Float val)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->set(0,createFloat(2.1));
    if(list->get(0)->toValue() != 2.1f
    ||list->get(1)->toValue() != 2.1f
    ||list->get(2)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {set(int index,Float val)} case1] [FAILED]--- \n");
      break;
    }

    Float t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Float> Test {set(int index,Float val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createFloat(1.1));
    if(result != -1) {
      printf("---[ArrayList<Float> Test {set(int index,Float val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2.1f
    ||list->get(1)->toValue() != 2.1f
    ||list->get(2)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {set(int index,Float val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Float> Test {set(int index,Float val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {set(int index,Float val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {set(int index,int val)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->set(0,2.1f);
    if(list->get(0)->toValue() != 2.1f
    ||list->get(1)->toValue() != 2.1f
    ||list->get(2)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {set(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    Float t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Float> Test {set(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,1.1f);
    if(result != -1) {
      printf("---[ArrayList<Float> Test {set(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2.1f
    ||list->get(1)->toValue() != 2.1f
    ||list->get(2)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {set(int index,int val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Float> Test {set(int index,int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {set(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {get(int index)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1f);
    list->add(2.1f);
    list->add(3.1f);

    Float v1 = list->get(1);
    if(v1->toValue() != 2.1f) {
      printf("---[ArrayList<Float> Test {get(int index)} case0] [FAILED]--- \n");
      break;
    }

    Float v2 = list->get(1000);
    if(v2 != nullptr) {
      printf("---[ArrayList<Float> Test {get(int index)} case1] [FAILED]--- \n");
      break;
    }

    Float v3 = list->get(-1);
    if(v3 != nullptr) {
      printf("---[ArrayList<Float> Test {get(int index)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {get(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {insert(int index,Float val)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->insert(1,createFloat(4.1));
    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 4.1f
    ||list->get(2)->toValue() != 2.1f
    ||list->get(3)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,Float val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,createFloat(4.1));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,Float val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createFloat(4.1));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,Float val)} case2] [FAILED]--- \n");
      break;
    }

    Float ii;
    result = list->insert(-1,ii);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,Float val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insert(int index,Float val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Float> Test {insert(int index,int val)} Start]---
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->insert(1,4.1);
    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 4.1f
    ||list->get(2)->toValue() != 2.1f
    ||list->get(3)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,int val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,4.1);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,4.1);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    int currentSize = list->size();
    list->insert(0,100.1);
    if(list->get(0)->toValue() != 100.1 && (list->size() != (currentSize + 1))) {
      printf("---[ArrayList<Float> Test {insert(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insert(int index,int val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Float> list);
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->add(4.1);
    list2->add(5.1);
    list2->add(6.1);

    list->insert(1,list2);
    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 4.1f
    ||list->get(2)->toValue() != 5.1f
    ||list->get(3)->toValue() != 6.1f
    ||list->get(4)->toValue() != 2.1f
    ||list->get(5)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list)} case1] [FAILED]--- \n");
      break;
    }

    size = list->size();
    result = list->insert(-1,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Float>list3 = createArrayList<Float>();
    list3->add(10.1);
    list3->add(11.1);
    list3->add(12.1);

    ArrayList<Float>list4 = createArrayList<Float>();
    list4->add(13.1);
    list4->add(14.1);
    list4->add(15.1);

    list3->insert(0,list4);
    if(list3->get(0)->toValue() != 13.1f
    ||list3->get(1)->toValue() != 14.1f
    ||list3->get(2)->toValue() != 15.1f
    ||list3->get(3)->toValue() != 10.1f
    ||list3->get(4)->toValue() != 11.1f
    ||list3->get(5)->toValue() != 12.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Float> list,int length);
  while(1) {
    ArrayList<Float>list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->add(4.1);
    list2->add(5.1);
    list2->add(6.1);

    list->insert(1,list2,2);
    if(list->get(0)->toValue() != 1.1f
    ||list->get(1)->toValue() != 4.1f
    ||list->get(2)->toValue() != 5.1f
    ||list->get(3)->toValue() != 2.1f
    ||list->get(4)->toValue() != 3.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2,5);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    size != list->size();
    result = list->insert(-1,list2,100);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Float>list3 = createArrayList<Float>();
    list3->add(10.1);
    list3->add(11.1);
    list3->add(12.1);

    ArrayList<Float>list4 = createArrayList<Float>();
    list4->add(13.1);
    list4->add(14.1);
    list4->add(15.1);

    list3->insert(0,list4,2);
    if(list3->get(0)->toValue() != 13.1f
    ||list3->get(1)->toValue() != 14.1f
    ||list3->get(2)->toValue() != 10.1f
    ||list3->get(3)->toValue() != 11.1f
    ||list3->get(4)->toValue() != 12.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case3] [FAILED]--- \n");
      break;
    }

    if(list3->size() != 5) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Float>list5 = createArrayList<Float>();
    list5->add(10.1);
    list5->add(11.1);
    list5->add(12.1);

    ArrayList<Float>list6 = createArrayList<Float>();
    list6->add(13.1);
    list6->add(14.1);
    list6->add(15.1);

    result = list5->insert(0,list6,100);

#if 0
    printf("list5[0] is %d \n",list5->get(0)->toValue());
    printf("list5[1] is %d \n",list5->get(1)->toValue());
    printf("list5[2] is %d \n",list5->get(2)->toValue());
    printf("list5[3] is %d \n",list5->get(3)->toValue());
    printf("list5[4] is %d \n",list5->get(4)->toValue());
    printf("list5[5] is %d \n",list5->get(5)->toValue());
#endif

    if(list5->get(0)->toValue() != 13.1f
      ||list5->get(1)->toValue() != 14.1f
      ||list5->get(2)->toValue() != 15.1f
      ||list5->get(3)->toValue() != 10.1f
      ||list5->get(4)->toValue() != 11.1f
      ||list5->get(5)->toValue() != 12.1f) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case5] [FAILED]--- \n");
      break;
    }

    if(list5->size() != 6) {
      printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)} case6] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insert(int index,ArrayList<Float> list,int length)}] [OK]--- \n");
    break;
  }

  //void insertFirst(Float val);
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->insertFirst(createFloat(4.1));
    if(list->get(0)->toValue() != 4.1f
       ||list->get(1)->toValue() != 1.1f
       ||list->get(2)->toValue() != 2.1f
       ||list->get(3)->toValue() != 3.1f) {
         printf("---[ArrayList<Float> Test {insertFirst(Float val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Float> Test {insertFirst(Float val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->insertFirst(createFloat(4.1));
    if(list2->get(0)->toValue() != 4.1f) {
      printf("---[ArrayList<Float> Test {insertFirst(Float val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Float> Test {insertFirst(Float val)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list3 = createArrayList<Float>();
    Float nt;
    list3->insertFirst(nt);
    if(list3->size() != 0) {
      printf("---[ArrayList<Float> Test {insertFirst(Float val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insertFirst(Float val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->insertFirst(4.1);
    if(list->get(0)->toValue() != 4.1f
       ||list->get(1)->toValue() != 1.1f
       ||list->get(2)->toValue() != 2.1f
       ||list->get(3)->toValue() != 3.1f) {
         printf("---[ArrayList<Float> Test {insertFirst(int val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Float> Test {insertFirst(int val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->insertFirst(4.1);
    if(list2->get(0)->toValue() != 4.1f) {
      printf("---[ArrayList<Float> Test {insertFirst(int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Float> Test {insertFirst(int val)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insertFirst(int val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(ArrayList<Float> list);
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->add(4.1);
    list2->add(5.1);
    list2->add(6.1);
    list->insertFirst(list2);

    if(list->get(0)->toValue() != 4.1f
      ||list->get(1)->toValue() != 5.1f
      ||list->get(2)->toValue() != 6.1f
      ||list->get(3)->toValue() != 1.1f
      ||list->get(4)->toValue() != 2.1f
      ||list->get(5)->toValue() != 3.1f) {
        printf("---[ArrayList<Float> Test {insertFirst(ArrayList<Float> list)} case1] [FAILED]--- \n");
        break;
      }

    ArrayList<Float> list3 = createArrayList<Float>();
    list3->add(1.1);
    list3->add(2.1);

    ArrayList<Float> list4 = createArrayList<Float>();
    list4->insertFirst(list4);

    if(list3->get(0)->toValue() != 1.1f
      ||list3->get(1)->toValue() != 2.1f){
        printf("---[ArrayList<Float> Test {insertFirst(ArrayList<Float> list)} case2] [FAILED]--- \n");
        break;
      }

    if(list3->size() != 2) {
      printf("---[ArrayList<Float> Test {insertFirst(ArrayList<Float> list)} case3] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      printf("---[ArrayList<Float> Test {insertFirst(ArrayList<Float> list)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insertFirst(ArrayList<Float> list)}] [OK]--- \n");
    break;
  }

  //void insertLast(Float v);
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->insertLast(createFloat(4.1));
    if(list->get(0)->toValue() != 1.1f
      ||list->get(1)->toValue() != 2.1f
      ||list->get(2)->toValue() != 3.1f
      ||list->get(3)->toValue() != 4.1f) {
        printf("---[ArrayList<Float> Test {insertLast(Float v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Float> Test {insertLast(Float v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->add(1.1);
    list2->add(2.1);
    list2->add(3.1);
    Float t2;
    list2->insertLast(t2);

    if(list2->get(0)->toValue() != 1.1f
      ||list2->get(1)->toValue() != 2.1f
      ||list2->get(2)->toValue() != 3.1f) {
        printf("---[ArrayList<Float> Test {insertLast(Float v)} case3] [FAILED]--- \n");
        break;
    }

    if(list2->size() != 3) {
      printf("---[ArrayList<Float> Test {insertLast(Float v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insertLast(Float v)} case5] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    list->insertLast(4.1);
    if(list->get(0)->toValue() != 1.1f
      ||list->get(1)->toValue() != 2.1f
      ||list->get(2)->toValue() != 3.1f
      ||list->get(3)->toValue() != 4.1f) {
        printf("---[ArrayList<Float> Test {insertLast(int v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Float> Test {insertLast(int v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->insertLast(1);

    if(list2->size() != 1) {
      printf("---[ArrayList<Float> Test {insertLast(int v)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->get(0)->toValue() != 1) {
      printf("---[ArrayList<Float> Test {insertLast(int v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {insertLast(int v)} case5] [OK]--- \n");
    break;
  }

  //insertLast(ArrayList<Float> list);
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);

    ArrayList<Float> list2 = createArrayList<Float>();
    list2->add(4.1);
    list2->add(5.1);
    list2->add(6.1);

    list->insertLast(list2);
    if(list->get(0)->toValue() != 1.1f
      ||list->get(1)->toValue() != 2.1f
      ||list->get(2)->toValue() != 3.1f
      ||list->get(3)->toValue() != 4.1f
      ||list->get(4)->toValue() != 5.1f
      ||list->get(5)->toValue() != 6.1f) {
        printf("---[ArrayList<Float> Test {insertLast(ArrayList<Float> v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 6) {
        printf("---[ArrayList<Float> Test {insertLast(ArrayList<Float> v)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Float> list3 = createArrayList<Float>();
    list3->add(1.1);
    list3->add(2.1);
    list3->add(3.1);

    ArrayList<Float> list4;
    list3->insertLast(list4);
    if(list3->get(0)->toValue() != 1.1f
      ||list3->get(1)->toValue() != 2.1f
      ||list3->get(2)->toValue() != 3.1f) {
        printf("---[ArrayList<Float> Test {insertLast(ArrayList<Float> v)} case3] [FAILED]--- \n");
        break;
    }

    if(list3->size() != 3) {
        printf("---[ArrayList<Float> Test {insertLast(ArrayList<Float> v)} case4] [FAILED]--- \n");
        break;
    }

    printf("---[ArrayList<Float> Test {insertLast(ArrayList<Float> v)} case5] [OK]--- \n");
    break;
  }

  //int size();
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);
    if(list->size() != 3) {
      printf("---[ArrayList<Float> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    if(list2->size() != 0) {
      printf("---[ArrayList<Float> Test {size()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Float> Test {size()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Float> getValue;
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1f);
    list->add(2.1f);
    list->add(3.1f);
    list->add(4.1f);
    list->add(5.1f);

    ListIterator<Float>iterator = list->getIterator();
    int index = 0;
    float checkdata[] = {1.1f,2.1f,3.1f,4.1f,5.1f};

    while(iterator->hasValue() && index != list->size()) {
      Float v = iterator->getValue();
      if(v->toValue() != checkdata[index]) {
        printf("---[ListIterator<Float> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      iterator->next();
      index++;
    }

    ArrayList<Float> list1 = createArrayList<Float>();
    ListIterator<Float>iterator1 = list1->getIterator();
    Float v = iterator1->getValue();
    if(v != nullptr) {
      printf("---[ListIterator<Float> Test {getValue()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Float> Test {getValue()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Float> hasValue();
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);
    ListIterator<Float> iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ListIterator<Float> Test {hasValue()} case1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      printf("---[ListIterator<Float> Test {hasValue()} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    ListIterator<Float> iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      printf("---[ListIterator<Float> Test {hasValue()} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Float> Test {hasValue()} case4] [OK]--- \n");
    break;
  }

  // ListIterator<Float> next();
  while(1) {
    ArrayList<Float> list = createArrayList<Float>();
    list->add(1.1);
    list->add(2.1);
    list->add(3.1);
    ListIterator<Float> iterator = list->getIterator();

    iterator->next();
    iterator->next();
    if(iterator->next()) {
      printf("---[ListIterator<Float> Test {next()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Float> list2 = createArrayList<Float>();
    ListIterator<Float> iterator2 = list2->getIterator();
    if(iterator2->next()) {
      printf("---[ListIterator<Float> Test {next()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Float> Test {next()} case3] [OK]--- \n");
    break;
  }
}
