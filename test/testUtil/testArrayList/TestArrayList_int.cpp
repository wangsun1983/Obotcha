#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "String.hpp"

using namespace obotcha;

void testArrayList_dataType_int() {
  //--[_ArrayList<int> Test {add(int val)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);

    if(list->size() != 2) {
      printf("---[ArrayList<int> Test {add(int val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0) != 1
    ||list->get(1) != 2) {
      printf("---[ArrayList<int> Test {add(int val)} case1] [FAILED]--- \n");
      break;
    }

    int t;
    int size = list->size();
    list->add(t);
    if(size == list->size()) {
      printf("---[ArrayList<int> Test {add(int val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {add(int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {add(int val)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);

    if(list->size() != 2) {
      printf("---[ArrayList<int> Test {add(int val)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0) != 1
    ||list->get(1) != 2) {
      printf("---[ArrayList<int> Test {add(int val)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {add(int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {add(ArrayList<int> list)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);

    ArrayList<int>list2 = createArrayList<int>();
    list2->add(3);
    list2->add(4);
    list->merge(list2);

    if(list->size() != 4) {
      printf("---[ArrayList<int> Test {add(ArrayList<int> list)} case0] [FAILED]--- \n");
      break;
    }

    if(list->get(0) != 1
    ||list->get(1) != 2
    ||list->get(2) != 3
    ||list->get(3) != 4) {
      printf("---[ArrayList<int> Test {add(ArrayList<int> list)} case1] [FAILED]--- \n");
      break;
    }
/*
    ArrayList<int>list3;
    int size = list->size();
    list->merge(list3);
    if(size != list->size()) {
      printf("---[ArrayList<int> Test {add(ArrayList<int> list)} case2] [FAILED]--- \n");
      break;
    }
*/
    printf("---[ArrayList<int> Test {add(ArrayList<int> val)}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<int> Test {clear()} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    int size = list->size();
    list->clear();
    if(size == 0 || list->size() != 0) {
      printf("---[ArrayList<int> Test {clear()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {clear()}] [OK]--- \n");
    break;
  }
  //--[_ArrayList<int> Test {remove(int index)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    int i = list->removeAt(2);
    if(i != 3) {
      printf("---[ArrayList<int> Test {remove(int index)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2) {
      printf("---[ArrayList<int> Test {remove(int index)} case1] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
         int i2 = list->removeAt(100);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {remove(int index)} case2] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
        int i3 = list->removeAt(-1);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {remove(int index)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {remove(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {remove(int v)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    int result = list->remove(2);
    if(result == -1) {
      printf("---[ArrayList<int> Test {remove(int v)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 2
      ||list->get(0) != 1
      ||list->get(1) != 3){
        printf("---[ArrayList<int> Test {remove(int v)} case1] [FAILED]--- \n");
        break;
    }

    int t1 = 100;
    if(list->remove(t1) != -1) {
      printf("---[ArrayList<int> Test {remove(int v)} case2] [FAILED]--- \n");
      break;
    }

/*
    int t2;
    int size = list->size();
    if(list->remove(t2) != -1) {
      printf("---[ArrayList<int> Test {remove(int v)} case3] [FAILED]--- \n");
      break;
    }

    if(size != list->size()) {
      printf("---[ArrayList<int> Test {remove(int v)} case4] [FAILED]--- \n");
      break;
    }*/

    printf("---[ArrayList<int> Test {remove(int v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {indexOf(int v)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    if(list->indexOf(1) != 0
      ||list->indexOf(2) != 1
      ||list->indexOf(3) != 2) {
        printf("---[ArrayList<int> Test {indexOf(int v)} case0] [FAILED]--- \n");
        break;
    }

    if(list->indexOf(100) != -1) {
      printf("---[ArrayList<int> Test {indexOf(int v)} case1] [FAILED]--- \n");
      break;
    }
/*
    int p;
    if(list->indexOf(p) != -1) {
      printf("---[ArrayList<int> Test {indexOf(int v)} case2] [FAILED]--- \n");
      break;
    }*/

    printf("---[ArrayList<int> Test {indexOf(int v)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {set(int index,int val)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->set(0,2);
    if(list->get(0) != 2
    ||list->get(1) != 2
    ||list->get(2) != 3) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
        list->set(100,1);
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0) != 2
    ||list->get(1) != 2
    ||list->get(2) != 3) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {set(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {set(int index,int val)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->set(0,2);
    if(list->get(0) != 2
    ||list->get(1) != 2
    ||list->get(2) != 3) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
        list->set(100,1);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0) != 2
    ||list->get(1) != 2
    ||list->get(2) != 3) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<int> Test {set(int index,int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {set(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {get(int index)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    int v1 = list->get(1);
    if(v1 != 2) {
      printf("---[ArrayList<int> Test {get(int index)} case0] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
        int v2 = list->get(1000);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {get(int index)} case1] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
        int v3 = list->get(-1);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {get(int index)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {get(int index)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {insert(int index,int val)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insert(1,4);
    if(list->get(0) != 1
    ||list->get(1) != 4
    ||list->get(2) != 2
    ||list->get(3) != 3) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        int result = list->insert(100,4);
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
        list->insert(-1,4);
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    int ii;
    isException = false;
    try {
        list->insert(-1,ii);
    } catch(ArrayIndexOutOfBoundsException e) {
          isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insert(int index,int val)}] [OK]--- \n");
    break;
  }

  //--[_ArrayList<int> Test {insert(int index,int val)} Start]---
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insert(1,4);
    if(list->get(0) != 1
    ||list->get(1) != 4
    ||list->get(2) != 2
    ||list->get(3) != 3) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        int result = list->insert(100,4);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case1] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
        list->insert(-1,4);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case2] [FAILED]--- \n");
      break;
    }

    int currentSize = list->size();
    list->insert(0,100);
    if(list->get(0) != 100 && (list->size() != (currentSize + 1))) {
      printf("---[ArrayList<int> Test {insert(int index,int val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insert(int index,int val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<int> list);
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<int> list2 = createArrayList<int>();
    list2->add(4);
    list2->add(5);
    list2->add(6);

    list->merge(1,list2);
    if(list->get(0) != 1
    ||list->get(1) != 4
    ||list->get(2) != 5
    ||list->get(3) != 6
    ||list->get(4) != 2
    ||list->get(5) != 3) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        int result = list->merge(100,list2);
    } catch(ArrayIndexOutOfBoundsException e) {
         isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list)} case1] [FAILED]--- \n");
      break;
    }

    isException = false;
    size = list->size();
    try {
        list->merge(-1,list2);
    } catch(ArrayIndexOutOfBoundsException e) {
        isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<int>list3 = createArrayList<int>();
    list3->add(10);
    list3->add(11);
    list3->add(12);

    ArrayList<int>list4 = createArrayList<int>();
    list4->add(13);
    list4->add(14);
    list4->add(15);

    list3->merge(0,list4);
    if(list3->get(0) != 13
    ||list3->get(1) != 14
    ||list3->get(2) != 15
    ||list3->get(3) != 10
    ||list3->get(4) != 11
    ||list3->get(5) != 12) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<int> list,int length);
  while(1) {
    ArrayList<int>list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<int> list2 = createArrayList<int>();
    list2->add(4);
    list2->add(5);
    list2->add(6);

    list->merge(1,list2,2);
    if(list->get(0) != 1
    ||list->get(1) != 4
    ||list->get(2) != 5
    ||list->get(3) != 2
    ||list->get(4) != 3) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    bool isException = false;
    try {
        list->merge(100,list2,5);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    size != list->size();
    isException = false;
    try {
        list->merge(-1,list2,100);
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<int>list3 = createArrayList<int>();
    list3->add(10);
    list3->add(11);
    list3->add(12);

    ArrayList<int>list4 = createArrayList<int>();
    list4->add(13);
    list4->add(14);
    list4->add(15);

    list3->merge(0,list4,2);
    if(list3->get(0) != 13
    ||list3->get(1) != 14
    ||list3->get(2) != 10
    ||list3->get(3) != 11
    ||list3->get(4) != 12) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case3] [FAILED]--- \n");
      break;
    }

    if(list3->size() != 5) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<int>list5 = createArrayList<int>();
    list5->add(10);
    list5->add(11);
    list5->add(12);

    ArrayList<int>list6 = createArrayList<int>();
    list6->add(13);
    list6->add(14);
    list6->add(15);

    bool isException1 = false;
    try {
        int result = list5->merge(0,list6,100);
    }catch(ArrayIndexOutOfBoundsException e) {
        isException1 = true;
    }

    if(!isException1) {
        printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case4_1] [FAILED]--- \n");
    }



#if 0
    printf("list5[0] is %d \n",list5->get(0));
    printf("list5[1] is %d \n",list5->get(1));
    printf("list5[2] is %d \n",list5->get(2));
    printf("list5[3] is %d \n",list5->get(3));
    printf("list5[4] is %d \n",list5->get(4));
    printf("list5[5] is %d \n",list5->get(5));
#endif

    if(list5->get(0) != 10
      ||list5->get(1) != 11
      ||list5->get(2) != 12) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case5] [FAILED]--- \n");
      break;
    }

    if(list5->size() != 3) {
      printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)} case6] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insert(int index,ArrayList<int> list,int length)}] [OK]--- \n");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertFirst(4);
    if(list->get(0) != 4
       ||list->get(1) != 1
       ||list->get(2) != 2
       ||list->get(3) != 3) {
         printf("---[ArrayList<int> Test {insertFirst(int val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<int> Test {insertFirst(int val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    list2->insertFirst(4);
    if(list2->get(0) != 4) {
      printf("---[ArrayList<int> Test {insertFirst(int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<int> Test {insertFirst(int val)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<int> list3 = createArrayList<int>();
    int nt;
    list3->insertFirst(nt);
    if(list3->size() == 0) {
      printf("---[ArrayList<int> Test {insertFirst(int val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insertFirst(int val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(int val);
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertFirst(4);
    if(list->get(0) != 4
       ||list->get(1) != 1
       ||list->get(2) != 2
       ||list->get(3) != 3) {
         printf("---[ArrayList<int> Test {insertFirst(int val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<int> Test {insertFirst(int val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    list2->insertFirst(4);
    if(list2->get(0) != 4) {
      printf("---[ArrayList<int> Test {insertFirst(int val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<int> Test {insertFirst(int val)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insertFirst(int val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(ArrayList<int> list);
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<int> list2 = createArrayList<int>();
    list2->add(4);
    list2->add(5);
    list2->add(6);
    list->insertFirst(list2);

    if(list->get(0) != 4
      ||list->get(1) != 5
      ||list->get(2) != 6
      ||list->get(3) != 1
      ||list->get(4) != 2
      ||list->get(5) != 3) {
        printf("---[ArrayList<int> Test {insertFirst(ArrayList<int> list)} case1] [FAILED]--- \n");
        break;
      }

    ArrayList<int> list3 = createArrayList<int>();
    list3->add(1);
    list3->add(2);

    ArrayList<int> list4 = createArrayList<int>();
    list4->insertFirst(list4);

    if(list3->get(0) != 1
      ||list3->get(1) != 2){
        printf("---[ArrayList<int> Test {insertFirst(ArrayList<int> list)} case2] [FAILED]--- \n");
        break;
      }

    if(list3->size() != 2) {
      printf("---[ArrayList<int> Test {insertFirst(ArrayList<int> list)} case3] [FAILED]--- \n");
      break;
    }

/*
    ArrayList<int> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      printf("---[ArrayList<int> Test {insertFirst(ArrayList<int> list)} case4] [FAILED]--- \n");
      break;
    }
*/
    printf("---[ArrayList<int> Test {insertFirst(ArrayList<int> list)}] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertLast(4);
    if(list->get(0) != 1
      ||list->get(1) != 2
      ||list->get(2) != 3
      ||list->get(3) != 4) {
        printf("---[ArrayList<int> Test {insertLast(int v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<int> Test {insertLast(int v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    list2->add(1);
    list2->add(2);
    list2->add(3);
    int t2;
    list2->insertLast(t2);

    if(list2->get(0) != 1
      ||list2->get(1) != 2
      ||list2->get(2) != 3) {
        printf("---[ArrayList<int> Test {insertLast(int v)} case3] [FAILED]--- \n");
        break;
    }

    if(list2->size() != 4) {
      printf("---[ArrayList<int> Test {insertLast(int v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insertLast(int v)} case5] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    list->insertLast(4);
    if(list->get(0) != 1
      ||list->get(1) != 2
      ||list->get(2) != 3
      ||list->get(3) != 4) {
        printf("---[ArrayList<int> Test {insertLast(int v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<int> Test {insertLast(int v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    list2->insertLast(1);

    if(list2->size() != 1) {
      printf("---[ArrayList<int> Test {insertLast(int v)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->get(0) != 1) {
      printf("---[ArrayList<int> Test {insertLast(int v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {insertLast(int v)} case5] [OK]--- \n");
    break;
  }

  //insertLast(ArrayList<int> list);
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<int> list2 = createArrayList<int>();
    list2->add(4);
    list2->add(5);
    list2->add(6);

    list->insertLast(list2);
    if(list->get(0) != 1
      ||list->get(1) != 2
      ||list->get(2) != 3
      ||list->get(3) != 4
      ||list->get(4) != 5
      ||list->get(5) != 6) {
        printf("---[ArrayList<int> Test {insertLast(ArrayList<int> v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 6) {
        printf("---[ArrayList<int> Test {insertLast(ArrayList<int> v)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<int> list3 = createArrayList<int>();
    list3->add(1);
    list3->add(2);
    list3->add(3);
/*
    ArrayList<int> list4;
    list3->insertLast(list4);
    if(list3->get(0) != 1
      ||list3->get(1) != 2
      ||list3->get(2) != 3) {
        printf("---[ArrayList<int> Test {insertLast(ArrayList<int> v)} case3] [FAILED]--- \n");
        break;
    }
*/
    if(list3->size() != 3) {
        printf("---[ArrayList<int> Test {insertLast(ArrayList<int> v)} case4] [FAILED]--- \n");
        break;
    }

    printf("---[ArrayList<int> Test {insertLast(ArrayList<int> v)} case5] [OK]--- \n");
    break;
  }

  //int size();
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);
    if(list->size() != 3) {
      printf("---[ArrayList<int> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    if(list2->size() != 0) {
      printf("---[ArrayList<int> Test {size()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<int> Test {size()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<int> getValue;
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);

    ListIterator<int>iterator = list->getIterator();
    int index = 1;
    while(iterator->hasValue() && index != list->size()) {
      int v = iterator->getValue();
      if(v != index) {
        printf("---[ListIterator<int> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      iterator->next();
      index++;
    }

/*
    ArrayList<int> list1 = createArrayList<int>();
    ListIterator<int>iterator1 = list1->getIterator();
    bool isException = false;
    try {
        int v = iterator1->getValue();
    } catch(ArrayIndexOutOfBoundsException e) {
       isException = true;
    }

    if(!isException) {
      printf("---[ListIterator<int> Test {getValue()} case2] [FAILED]--- \n");
      break;
    }
*/
    printf("---[ListIterator<int> Test {getValue()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<int> hasValue();
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);
    ListIterator<int> iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ListIterator<int> Test {hasValue()} case1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      printf("---[ListIterator<int> Test {hasValue()} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    ListIterator<int> iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      printf("---[ListIterator<int> Test {hasValue()} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<int> Test {hasValue()} case4] [OK]--- \n");
    break;
  }

  // ListIterator<int> next();
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);
    ListIterator<int> iterator = list->getIterator();

    iterator->next();
    iterator->next();
    if(iterator->next()) {
      printf("---[ListIterator<int> Test {next()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<int> list2 = createArrayList<int>();
    ListIterator<int> iterator2 = list2->getIterator();
    if(iterator2->next()) {
      printf("---[ListIterator<int> Test {next()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<int> Test {next()} case3] [OK]--- \n");
    break;
  }

  //--[_ListIterator<int> Test {remove()} Start]---
  while(1) {
    ArrayList<int> list = createArrayList<int>();
    list->add(1);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);
    ListIterator<int> iterator = list->getIterator();
    while(iterator->hasValue()) {
      if(iterator->getValue() == 3) {
        iterator->remove();
      }else {
        iterator->next();
      }
    }

    if(list->size() != 4) {
        printf("---[ListIterator<int> Test {remove()} case0] [FAILED]--- \n");
        break;
    }

    if(list->get(0) != 1 ||list->get(1) != 2
      ||list->get(2) != 4||list->get(3) != 5) {
        printf("---[ListIterator<int> Test {remove()} case2] [FAILED]--- \n");
        break;
    }

    printf("---[_ListIterator<int> Test {remove()} case3] [OK]--- \n");
    break;
  }
}
