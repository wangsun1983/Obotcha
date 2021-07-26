#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Double.hpp"
#include "String.hpp"
#include "Double.hpp"
#include "Math.hpp"

using namespace obotcha;

void testArrayList_Double() {
  //--[_ArrayList<Double> Test {add(Double val)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));

    if(list->size() != 2) {
      printf("---[ArrayList<Double> Test {add(Double val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 2.1) {
      printf("---[ArrayList<Double> Test {add(Double val)} case1] [FAILED]--- \n");
      break;
    }

    Double t;
    int size = list->size();
    list->add(t);
    if(size == list->size()) {
      printf("---[ArrayList<Double> Test {add(Double val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {add(Double val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {add(Double val)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));

    if(list->size() != 2) {
      printf("---[ArrayList<Double> Test {add(Double val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 2.1) {
      printf("---[ArrayList<Double> Test {add(Double val)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {add(Double val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {add(ArrayList<Double> list)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));

    ArrayList<Double>list2 = createArrayList<Double>();
    list2->add(createDouble(3.1));
    list2->add(createDouble(4.1));

    list->add(list2);

    if(list->size() != 4) {
      printf("---[ArrayList<Double> Test {add(ArrayList<Double> list)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 2.1
    ||list->get(2)->toValue() != 3.1
    ||list->get(3)->toValue() != 4.1) {
      printf("---[ArrayList<Double> Test {add(ArrayList<Double> list)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Double>list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      printf("---[ArrayList<Double> Test {add(ArrayList<Double> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {add(ArrayList<Double> val)}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Double> Test {clear()} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    int size = list->size();
    list->clear();
    if(size == 0 || list->size() != 0) {
      printf("---[ArrayList<Double> Test {clear()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {clear()}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<Double> Test {remove(int index)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    Double i = list->removeAt(2);
    if(i->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {remove(int index)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2) {
      printf("---[ArrayList<Double> Test {remove(int index)} case1] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
        Double i2 = list->removeAt(100);
    } catch(ArrayIndexOutOfBoundsException e) {
      isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<Double> Test {remove(int index)} case2] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
        Double i3 = list->removeAt(-1);
    } catch(ArrayIndexOutOfBoundsException e) {
      isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<Double> Test {remove(int index)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {remove(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {remove(Double v)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    int result = list->remove(createDouble(2.1));
    if(result == -1) {
      printf("---[ArrayList<Double> Test {remove(Double v)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2
      ||list->get(0)->toValue() != 1.1
      ||list->get(1)->toValue() != 3.1){
        printf("---[ArrayList<Double> Test {remove(Double v)} case1] [FAILED]--- \n");
        break;
    }

    Double t1 = createDouble(100);
    if(list->remove(t1) != -1) {
      printf("---[ArrayList<Double> Test {remove(Double v)} case2] [FAILED]--- \n");
      break;
    }

    Double t2;
    int size = list->size();
    if(list->remove(t2) != -1) {
      printf("---[ArrayList<Double> Test {remove(Double v)} case3] [FAILED]--- \n");
      break;
    }

    if(size != list->size()) {
      printf("---[ArrayList<Double> Test {remove(Double v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {remove(Double v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {indexOf(Double v)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    if(list->indexOf(createDouble(1.1)) != 0
      ||list->indexOf(createDouble(2.1)) != 1
      ||list->indexOf(createDouble(3.1)) != 2) {
        printf("---[ArrayList<Double> Test {indexOf(Double v)} case0] [FAILED]--- \n");
        break;
    }

    if(list->indexOf(createDouble(100.1)) != -1) {
      printf("---[ArrayList<Double> Test {indexOf(Double v)} case1] [FAILED]--- \n");
      break;
    }

    Double p;
    if(list->indexOf(p) != -1) {
      printf("---[ArrayList<Double> Test {indexOf(Double v)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {indexOf(Double v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {set(int index,Double val)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->set(0,createDouble(2.1));
    if(list->get(0)->toValue() != 2.1
    ||list->get(1)->toValue() != 2.1
    ||list->get(2)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {set(int index,Double val)} case1] [FAILED]--- \n");
      break;
    }

    Double t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Double> Test {set(int index,Double val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createDouble(1.1));
    if(result != -1) {
      printf("---[ArrayList<Double> Test {set(int index,Double val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2.1
    ||list->get(1)->toValue() != 2.1
    ||list->get(2)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {set(int index,Double val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Double> Test {set(int index,Double val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {set(int index,Double val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {set(int index,int val)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->set(0,createDouble(2.1));
    if(list->get(0)->toValue() != 2.1
    ||list->get(1)->toValue() != 2.1
    ||list->get(2)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {set(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    Double t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Double> Test {set(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createDouble(1.1f));
    if(result != -1) {
      printf("---[ArrayList<Double> Test {set(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != 2.1
    ||list->get(1)->toValue() != 2.1
    ||list->get(2)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {set(int index,int val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Double> Test {set(int index,int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {set(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {get(int index)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    Double v1 = list->get(1);
    if(v1->toValue() != 2.1) {
      printf("---[ArrayList<Double> Test {get(int index)} case0] [FAILED]--- \n");
      break;
    }

    Double v2 = list->get(1000);
    if(v2 != nullptr) {
      printf("---[ArrayList<Double> Test {get(int index)} case1] [FAILED]--- \n");
      break;
    }

    Double v3 = list->get(-1);
    if(v3 != nullptr) {
      printf("---[ArrayList<Double> Test {get(int index)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {get(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {insert(int index,Double val)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->insert(1,createDouble(4.1));
    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 4.1
    ||list->get(2)->toValue() != 2.1
    ||list->get(3)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {insert(int index,Double val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,createDouble(4.1));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,Double val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createDouble(4.1));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,Double val)} case2] [FAILED]--- \n");
      break;
    }

    Double ii;
    result = list->insert(-1,ii);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,Double val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insert(int index,Double val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<Double> Test {insert(int index,int val)} Start]---
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->insert(1,createDouble(4.1));
    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 4.1
    ||list->get(2)->toValue() != 2.1
    ||list->get(3)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {insert(int index,int val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,createDouble(4.1));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createDouble(4.1));
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    int currentSize = list->size();
    list->insert(0,createDouble(100.1));
    if(list->get(0)->toValue() != 100.1 && (list->size() != (currentSize + 1))) {
      printf("---[ArrayList<Double> Test {insert(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insert(int index,int val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Double> list);
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->add(createDouble(4.1));
    list2->add(createDouble(5.1));
    list2->add(createDouble(6.1));

    list->merge(1,list2);
    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 4.1
    ||list->get(2)->toValue() != 5.1
    ||list->get(3)->toValue() != 6.1
    ||list->get(4)->toValue() != 2.1
    ||list->get(5)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->merge(100,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list)} case1] [FAILED]--- \n");
      break;
    }

    size = list->size();
    result = list->merge(-1,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Double>list3 = createArrayList<Double>();
    list3->add(createDouble(10.1));
    list3->add(createDouble(11.1));
    list3->add(createDouble(12.1));

    ArrayList<Double>list4 = createArrayList<Double>();
    list4->add(createDouble(13.1));
    list4->add(createDouble(14.1));
    list4->add(createDouble(15.1));

    list3->merge(0,list4);
    if(list3->get(0)->toValue() != 13.1
    ||list3->get(1)->toValue() != 14.1
    ||list3->get(2)->toValue() != 15.1
    ||list3->get(3)->toValue() != 10.1
    ||list3->get(4)->toValue() != 11.1
    ||list3->get(5)->toValue() != 12.1) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Double> list,int length);
  while(1) {
    ArrayList<Double>list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->add(createDouble(4.1));
    list2->add(createDouble(5.1));
    list2->add(createDouble(6.1));

    list->merge(1,list2,2);
    if(list->get(0)->toValue() != 1.1
    ||list->get(1)->toValue() != 4.1
    ||list->get(2)->toValue() != 5.1
    ||list->get(3)->toValue() != 2.1
    ||list->get(4)->toValue() != 3.1) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->merge(100,list2,5);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    size != list->size();
    result = list->merge(-1,list2,100);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Double>list3 = createArrayList<Double>();
    list3->add(createDouble(10.1));
    list3->add(createDouble(11.1));
    list3->add(createDouble(12.1));

    ArrayList<Double>list4 = createArrayList<Double>();
    list4->add(createDouble(13.1));
    list4->add(createDouble(14.1));
    list4->add(createDouble(15.1));

    list3->merge(0,list4,2);
    if(list3->get(0)->toValue() != 13.1
    ||list3->get(1)->toValue() != 14.1
    ||list3->get(2)->toValue() != 10.1
    ||list3->get(3)->toValue() != 11.1
    ||list3->get(4)->toValue() != 12.1) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case3] [FAILED]--- \n");
      break;
    }

    if(list3->size() != 5) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Double>list5 = createArrayList<Double>();
    list5->add(createDouble(10.1));
    list5->add(createDouble(11.1));
    list5->add(createDouble(12.1));

    ArrayList<Double>list6 = createArrayList<Double>();
    list6->add(createDouble(13.1));
    list6->add(createDouble(14.1));
    list6->add(createDouble(15.1));

    result = list5->merge(0,list6,100);

#if 0
    printf("list5[0] is %d \n",list5->get(0)->toValue());
    printf("list5[1] is %d \n",list5->get(1)->toValue());
    printf("list5[2] is %d \n",list5->get(2)->toValue());
    printf("list5[3] is %d \n",list5->get(3)->toValue());
    printf("list5[4] is %d \n",list5->get(4)->toValue());
    printf("list5[5] is %d \n",list5->get(5)->toValue());
#endif

    if(list5->get(0)->toValue() != 13.1
      ||list5->get(1)->toValue() != 14.1
      ||list5->get(2)->toValue() != 15.1
      ||list5->get(3)->toValue() != 10.1
      ||list5->get(4)->toValue() != 11.1
      ||list5->get(5)->toValue() != 12.1) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case5] [FAILED]--- \n");
      break;
    }

    if(list5->size() != 6) {
      printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)} case6] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insert(int index,ArrayList<Double> list,int length)}] [OK]--- \n");
    break;
  }

  //void insertFirst(Double val);
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->insertFirst(createDouble(4.1));
    if(list->get(0)->toValue() != 4.1
       ||list->get(1)->toValue() != 1.1
       ||list->get(2)->toValue() != 2.1
       ||list->get(3)->toValue() != 3.1) {
         printf("---[ArrayList<Double> Test {insertFirst(Double val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Double> Test {insertFirst(Double val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->insertFirst(createDouble(4.1));
    if(list2->get(0)->toValue() != 4.1) {
      printf("---[ArrayList<Double> Test {insertFirst(Double val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Double> Test {insertFirst(Double val)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list3 = createArrayList<Double>();
    Double nt;
    list3->insertFirst(nt);
    if(list3->size() == 0) {
      printf("---[ArrayList<Double> Test {insertFirst(Double val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insertFirst(Double val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->insertFirst(createDouble(4.1));
    if(list->get(0)->toValue() != 4.1
       ||list->get(1)->toValue() != 1.1
       ||list->get(2)->toValue() != 2.1
       ||list->get(3)->toValue() != 3.1) {
         printf("---[ArrayList<Double> Test {insertFirst(int val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Double> Test {insertFirst(int val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->insertFirst(createDouble(4.1));
    if(list2->get(0)->toValue() != 4.1) {
      printf("---[ArrayList<Double> Test {insertFirst(int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Double> Test {insertFirst(int val)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insertFirst(int val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(ArrayList<Double> list);
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->add(createDouble(4.1));
    list2->add(createDouble(5.1));
    list2->add(createDouble(6.1));
    list->insertFirst(list2);

    if(list->get(0)->toValue() != 4.1
      ||list->get(1)->toValue() != 5.1
      ||list->get(2)->toValue() != 6.1
      ||list->get(3)->toValue() != 1.1
      ||list->get(4)->toValue() != 2.1
      ||list->get(5)->toValue() != 3.1) {
        printf("---[ArrayList<Double> Test {insertFirst(ArrayList<Double> list)} case1] [FAILED]--- \n");
        break;
      }

    ArrayList<Double> list3 = createArrayList<Double>();
    list3->add(createDouble(1.1));
    list3->add(createDouble(2.1));

    ArrayList<Double> list4 = createArrayList<Double>();
    list4->insertFirst(list4);

    if(list3->get(0)->toValue() != 1.1
      ||list3->get(1)->toValue() != 2.1){
        printf("---[ArrayList<Double> Test {insertFirst(ArrayList<Double> list)} case2] [FAILED]--- \n");
        break;
      }

    if(list3->size() != 2) {
      printf("---[ArrayList<Double> Test {insertFirst(ArrayList<Double> list)} case3] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      printf("---[ArrayList<Double> Test {insertFirst(ArrayList<Double> list)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insertFirst(ArrayList<Double> list)}] [OK]--- \n");
    break;
  }

  //void insertLast(Double v);
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->insertLast(createDouble(4.1));
    if(list->get(0)->toValue() != 1.1
      ||list->get(1)->toValue() != 2.1
      ||list->get(2)->toValue() != 3.1
      ||list->get(3)->toValue() != 4.1) {
        printf("---[ArrayList<Double> Test {insertLast(Double v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Double> Test {insertLast(Double v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->add(createDouble(1.1));
    list2->add(createDouble(2.1));
    list2->add(createDouble(3.1));
    Double t2;
    list2->insertLast(t2);

    if(list2->get(0)->toValue() != 1.1
      ||list2->get(1)->toValue() != 2.1
      ||list2->get(2)->toValue() != 3.1) {
        printf("---[ArrayList<Double> Test {insertLast(Double v)} case3] [FAILED]--- \n");
        break;
    }

    if(list2->size() != 4) {
      printf("---[ArrayList<Double> Test {insertLast(Double v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insertLast(Double v)} case5] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    list->add(createDouble(4.1));
    if(list->get(0)->toValue() != 1.1
      ||list->get(1)->toValue() != 2.1
      ||list->get(2)->toValue() != 3.1
      ||list->get(3)->toValue() != 4.1) {
        printf("---[ArrayList<Double> Test {insertLast(int v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Double> Test {insertLast(int v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->add(createDouble(1));

    if(list2->size() != 1) {
      printf("---[ArrayList<Double> Test {insertLast(int v)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->get(0)->toValue() != 1) {
      printf("---[ArrayList<Double> Test {insertLast(int v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {insertLast(int v)} case5] [OK]--- \n");
    break;
  }

  //insertLast(ArrayList<Double> list);
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));

    ArrayList<Double> list2 = createArrayList<Double>();
    list2->add(createDouble(4.1));
    list2->add(createDouble(5.1));
    list2->add(createDouble(6.1));

    list->insertLast(list2);
    if(list->get(0)->toValue() != 1.1
      ||list->get(1)->toValue() != 2.1
      ||list->get(2)->toValue() != 3.1
      ||list->get(3)->toValue() != 4.1
      ||list->get(4)->toValue() != 5.1
      ||list->get(5)->toValue() != 6.1) {
        printf("---[ArrayList<Double> Test {insertLast(ArrayList<Double> v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 6) {
        printf("---[ArrayList<Double> Test {insertLast(ArrayList<Double> v)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Double> list3 = createArrayList<Double>();
    list3->add(createDouble(1.1));
    list3->add(createDouble(2.1));
    list3->add(createDouble(3.1));

    ArrayList<Double> list4;
    list3->insertLast(list4);
    if(list3->get(0)->toValue() != 1.1
      ||list3->get(1)->toValue() != 2.1
      ||list3->get(2)->toValue() != 3.1) {
        printf("---[ArrayList<Double> Test {insertLast(ArrayList<Double> v)} case3] [FAILED]--- \n");
        break;
    }

    if(list3->size() != 3) {
        printf("---[ArrayList<Double> Test {insertLast(ArrayList<Double> v)} case4] [FAILED]--- \n");
        break;
    }

    printf("---[ArrayList<Double> Test {insertLast(ArrayList<Double> v)} case5] [OK]--- \n");
    break;
  }

  //int size();
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));
    if(list->size() != 3) {
      printf("---[ArrayList<Double> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    if(list2->size() != 0) {
      printf("---[ArrayList<Double> Test {size()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Double> Test {size()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Double> getValue;
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));
    list->add(createDouble(4.1));
    list->add(createDouble(5.1));

    ListIterator<Double>iterator = list->getIterator();
    int index = 0;
    double checkdata[] = {1.1,2.1,3.1,4.1,5.1};

    while(iterator->hasValue() && index != list->size()) {
      Double v = iterator->getValue();
      if(v->toValue() != checkdata[index]) {
        printf("---[ListIterator<Double> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      iterator->next();
      index++;
    }

    ArrayList<Double> list1 = createArrayList<Double>();
    ListIterator<Double>iterator1 = list1->getIterator();
    Double v = iterator1->getValue();
    if(v != nullptr) {
      printf("---[ListIterator<Double> Test {getValue()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Double> Test {getValue()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Double> hasValue();
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));
    ListIterator<Double> iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ListIterator<Double> Test {hasValue()} case1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      printf("---[ListIterator<Double> Test {hasValue()} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    ListIterator<Double> iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      printf("---[ListIterator<Double> Test {hasValue()} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Double> Test {hasValue()} case4] [OK]--- \n");
    break;
  }

  // ListIterator<Double> next();
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));
    ListIterator<Double> iterator = list->getIterator();

    iterator->next();
    iterator->next();
    if(iterator->next()) {
      printf("---[ListIterator<Double> Test {next()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Double> list2 = createArrayList<Double>();
    ListIterator<Double> iterator2 = list2->getIterator();
    if(iterator2->next()) {
      printf("---[ListIterator<Double> Test {next()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Double> Test {next()} case3] [OK]--- \n");
    break;
  }

  //--[_ListIterator<Double> Test {remove()} Start]---
  while(1) {
    ArrayList<Double> list = createArrayList<Double>();
    list->add(createDouble(1.1));
    list->add(createDouble(2.1));
    list->add(createDouble(3.1));
    list->add(createDouble(4.1));
    list->add(createDouble(5.1));
    ListIterator<Double> iterator = list->getIterator();
    while(iterator->hasValue()) {
      if(st(Math)::compareDouble(iterator->getValue()->toValue(),3.1) == st(Math)::AlmostEqual) {
        iterator->remove();
      }else {
        iterator->next();
      }
    }

    if(list->size() != 4) {
        printf("---[ListIterator<Double> Test {remove()} case0] [FAILED]--- \n");
        break;
    }

    if(st(Math)::compareDouble(list->get(0)->toValue(),1.1) != st(Math)::AlmostEqual
      ||st(Math)::compareDouble(list->get(1)->toValue(),2.1) != st(Math)::AlmostEqual
      ||st(Math)::compareDouble(list->get(2)->toValue(),4.1) != st(Math)::AlmostEqual
      ||st(Math)::compareDouble(list->get(3)->toValue(),5.1) != st(Math)::AlmostEqual) {
        printf("---[ListIterator<Double> Test {remove()} case2] [FAILED]--- \n");
        break;
    }

    printf("---[ListIterator<Double> Test {remove()} case3] [OK]--- \n");
    break;
  }
}
