#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Boolean.hpp"

using namespace obotcha;

void testArrayList_Boolean() {
  //ArrayList<Boolean> add
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(createBoolean(true));
    list->add(createBoolean(false));
    list->add(createBoolean(true));
    if(list->get(0)->toValue() != true
      ||list->get(1)->toValue() != false
      ||list->get(2)->toValue() != true) {
        printf("---[ArrayList<Boolean> Test {add()} case1] [FAILED]--- \n");
        break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    Boolean t2;
    list2->add(t2);
    if(list2->size() != 0) {
      printf("---[ArrayList<Boolean> Test {add()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {add()} case3] [OK]--- \n");
    break;
  }

  //ArrayList<Boolean> add(bool val);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(false);
    list->add(true);
    if(list->get(0)->toValue() != true
      ||list->get(1)->toValue() != false
      ||list->get(2)->toValue() != true) {
        printf("---[ArrayList<Boolean> Test {add(bool val)} case1] [FAILED]--- \n");
        break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    Boolean t2;
    list2->add(t2);
    if(list2->size() != 0) {
      printf("---[ArrayList<Boolean> Test {add(bool val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {add(bool val)} case3] [OK]--- \n");
    break;
  }

  //void add(ArrayList<Boolean> list);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(false);
    list->add(true);

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(false);
    list2->add(true);

    list->add(list2);
    if(list->get(0)->toValue() != true
      ||list->get(1)->toValue() != false
      ||list->get(2)->toValue() != true
      ||list->get(3)->toValue() != false
      ||list->get(4)->toValue() != true) {
        printf("---[ArrayList<Boolean> Test {add(ArrayList<Boolean> list)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<Boolean> Test {add(ArrayList<Boolean> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list3 = createArrayList<Boolean>();
    list3->add(true);
    list3->add(false);
    list3->add(true);

    ArrayList<Boolean> list4 = createArrayList<Boolean>();
    list3->add(list4);

    if(list3->get(0)->toValue() != true
      ||list3->get(1)->toValue() != false
      ||list3->get(2)->toValue() != true){
        printf("---[ArrayList<Boolean> Test {add(ArrayList<Boolean> list)} case3] [FAILED]--- \n");
        break;
    }

    if(list3->size() != 3) {
      printf("---[ArrayList<Boolean> Test {add(ArrayList<Boolean> list)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list5;
    list3->add(list5);

    if(list3->size() != 3) {
      printf("---[ArrayList<Boolean> Test {add(ArrayList<Boolean> list)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {add(ArrayList<Boolean> list)} case6] [OK]--- \n");
    break;
  }

  //void clear();
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(false);
    list->add(true);
    int size = list->size();
    list->clear();
    if(size != 3 || list->size() != 0) {
      printf("---[ArrayList<Boolean> Test {clear()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->clear();
    if(list2->size() != 0) {
      printf("---[ArrayList<Boolean> Test {clear()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {clear()} case3] [OK]--- \n");
    break;
  }

  //Boolean remove(int index);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(false);
    list->add(true);

    Boolean v1 = list->remove(0);
    if(!v1->equals(true)) {
      printf("---[ArrayList<Boolean> Test {remove(int index)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(true);
    list2->add(false);
    list2->add(true);
    Boolean v2 = list2->remove(100);
    if(v2 != nullptr) {
      printf("---[ArrayList<Boolean> Test {remove(int index)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list3 = createArrayList<Boolean>();
    Boolean v3 = list3->remove(2);
    if(v3 != nullptr) {
      printf("---[ArrayList<Boolean> Test {remove(int index)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {remove(int index)} case4] [OK]--- \n");
    break;
  }

  //int remove(Boolean v);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(false);
    list->add(true);

    int index = list->remove(createBoolean(false));
    if(index != 1) {
      printf("---[ArrayList<Boolean> Test {remove(Boolean v)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(true);

    int index2 = list2->remove(createBoolean(false));
    if(index2 != -1) {
      printf("---[ArrayList<Boolean> Test {remove(Boolean v)} case2] [FAILED]--- \n");
      break;
    }

    int size = list2->size();
    Boolean v3;
    list2->remove(v3);
    if(list2->size() != size) {
      printf("---[ArrayList<Boolean> Test {remove(Boolean v)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {remove(Boolean v)} case4] [OK]--- \n");
    break;
  }

  //int indexOf(Boolean v);
  while(1) {
    ArrayList<Boolean>list = createArrayList<Boolean>();
    list->add(createBoolean(true));
    list->add(createBoolean(true));
    list->add(createBoolean(false));

    if(list->indexOf(createBoolean(true)) != 0
      ||list->indexOf(createBoolean(false)) != 2) {
        printf("---[ArrayList<Boolean> Test {indexOf(Boolean v)} case0] [FAILED]--- \n");
        break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(createBoolean(true));
    list2->add(createBoolean(true));

    if(list2->indexOf(createBoolean(false)) != -1) {
      printf("---[ArrayList<Boolean> Test {indexOf(Boolean v)} case1] [FAILED]--- \n");
      break;
    }

    Boolean p;
    if(list2->indexOf(p) != -1) {
      printf("---[ArrayList<Boolean> Test {indexOf(Boolean v)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {indexOf(Boolean v)}] [OK]--- \n");
    break;
  }

  //int set(int index,Boolean val);
  while(1) {
    ArrayList<Boolean>list = createArrayList<Boolean>();
    list->add(createBoolean(false));
    list->add(createBoolean(false));
    list->add(createBoolean(false));

    list->set(0,createBoolean(true));
    if(list->get(0)->toValue() != true
    ||list->get(1)->toValue() != false
    ||list->get(2)->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {set(int index,Boolean val)} case1] [FAILED]--- \n");
      break;
    }

    Boolean t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {set(int index,Boolean val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createBoolean(true));
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {set(int index,Boolean val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != true
    ||list->get(1)->toValue() != false
    ||list->get(2)->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {set(int index,Boolean val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Boolean> Test {set(int index,Boolean val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {set(int index,Boolean val)}] [OK]--- \n");
    break;
  }

  //int set(int index,bool val);
  while(1) {
    ArrayList<Boolean>list = createArrayList<Boolean>();
    list->add(false);
    list->add(false);
    list->add(false);

    list->set(0,true);
    if(list->get(0)->toValue() != true
    ||list->get(1)->toValue() != false
    ||list->get(2)->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {set(int index,bool val)} case1] [FAILED]--- \n");
      break;
    }

    Boolean t1;
    int result = list->set(1,t1);
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {set(int index,bool val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->set(100,createBoolean(true));
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {set(int index,bool val)} case3] [FAILED]--- \n");
      break;
    }

    if(list->get(0)->toValue() != true
    ||list->get(1)->toValue() != false
    ||list->get(2)->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {set(int index,bool val)} case4] [FAILED]--- \n");
      break;
    }

    if(list->size() != 3) {
      printf("---[ArrayList<Boolean> Test {set(int index,bool val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {set(int index,bool val)}] [OK]--- \n");
    break;
  }

  //Boolean get(int index);
  while(1) {
    ArrayList<Boolean>list = createArrayList<Boolean>();
    list->add(true);
    list->add(false);
    list->add(false);

    Boolean v1 = list->get(1);
    if(v1->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {get(int index)} case0] [FAILED]--- \n");
      break;
    }

    Boolean v2 = list->get(1000);
    if(v2 != nullptr) {
      printf("---[ArrayList<Boolean> Test {get(int index)} case1] [FAILED]--- \n");
      break;
    }

    Boolean v3 = list->get(-1);
    if(v3 != nullptr) {
      printf("---[ArrayList<Boolean> Test {get(int index)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {get(int index)}] [OK]--- \n");
    break;
  }

  //int insert(int index,Boolean val);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(createBoolean(true));
    list->add(createBoolean(true));
    list->add(createBoolean(true));

    list->insert(1,createBoolean(false));
    if(!list->get(0)->equals(true)
    ||!list->get(1)->equals(false)
    ||!list->get(2)->equals(true)
    ||!list->get(3)->equals(true)) {
      printf("---[ArrayList<Boolean> Test {insert(int index,Boolean val)} case1] [FAILED]--- \n");
      break;
    }

    int result = list->insert(50,createBoolean(false));
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {insert(int index,Boolean val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,createBoolean(false));
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {insert(int index,Boolean val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insert(int index,Boolean val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,bool val);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    list->insert(1,false);
    if(!list->get(0)->equals(true)
    ||!list->get(1)->equals(false)
    ||!list->get(2)->equals(true)
    ||!list->get(3)->equals(true)) {
      printf("---[ArrayList<Boolean> Test {insert(int index,bool val)} case1] [FAILED]--- \n");
      break;
    }

    int result = list->insert(50,false);
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {insert(int index,bool val)} case2] [FAILED]--- \n");
      break;
    }

    result = list->insert(-1,false);
    if(result != -1) {
      printf("---[ArrayList<Boolean> Test {insert(int index,bool val)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insert(int index,bool val)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Boolean> list);
  while(1) {
    ArrayList<Boolean>list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(false);
    list2->add(false);
    list2->add(false);

    list->insert(1,list2);

#if 0
    if(list->get(0)->toValue() == true) {
         printf("list[0] is true \n");
    } else {
         printf("list[0] is false \n");
    }

    if(list->get(1)->toValue() == true) {
         printf("list[1] is true \n");
    } else {
         printf("list[1] is false \n");
    }

    if(list->get(2)->toValue() == true) {
         printf("list[2] is true \n");
    } else {
         printf("list[2] is false \n");
    }

    if(list->get(3)->toValue() == true) {
         printf("list[3] is true \n");
    } else {
         printf("list[3] is false \n");
    }

    if(list->get(4)->toValue() == true) {
         printf("list[4] is true \n");
    } else {
         printf("list[4] is false \n");
    }

    if(list->get(5)->toValue() == true) {
         printf("list[5] is true \n");
    } else {
         printf("list[5] is false \n");
    }
#endif

    if(list->get(0)->toValue() != true
    ||list->get(1)->toValue() != false
    ||list->get(2)->toValue() != false
    ||list->get(3)->toValue() != false
    ||list->get(4)->toValue() != true
    ||list->get(5)->toValue() != true) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list)} case0] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list)} case1] [FAILED]--- \n");
      break;
    }

    size = list->size();
    result = list->insert(-1,list2);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean>list3 = createArrayList<Boolean>();
    list3->add(true);
    list3->add(true);
    list3->add(true);

    ArrayList<Boolean>list4 = createArrayList<Boolean>();
    list4->add(false);
    list4->add(false);
    list4->add(false);

    list3->insert(0,list4);
    if(list3->get(0)->toValue() != false
    ||list3->get(1)->toValue() != false
    ||list3->get(2)->toValue() != false
    ||list3->get(3)->toValue() != true
    ||list3->get(4)->toValue() != true
    ||list3->get(5)->toValue() != true) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list)} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list)}] [OK]--- \n");
    break;
  }

  //int insert(int index,ArrayList<Boolean> list,int length);
  while(1) {
    ArrayList<Boolean>list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(false);
    list2->add(false);
    list2->add(false);

    list->insert(1,list2,2);
    if(list->get(0)->toValue() != true
    ||list->get(1)->toValue() != false
    ||list->get(2)->toValue() != false
    ||list->get(3)->toValue() != true
    ||list->get(4)->toValue() != true) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case0] [FAILED]--- \n");
      break;
    }

    if(list->size() != 5) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    int result = list->insert(100,list2,5);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case1] [FAILED]--- \n");
      break;
    }

    size != list->size();
    result = list->insert(-1,list2,100);
    if(result != -1 || size != list->size()) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean>list3 = createArrayList<Boolean>();
    list3->add(true);
    list3->add(true);
    list3->add(true);

    ArrayList<Boolean>list4 = createArrayList<Boolean>();
    list4->add(false);
    list4->add(false);
    list4->add(false);

    list3->insert(0,list4,2);
    if(list3->get(0)->toValue() != false
    ||list3->get(1)->toValue() != false
    ||list3->get(2)->toValue() != true
    ||list3->get(3)->toValue() != true
    ||list3->get(4)->toValue() != true) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case3] [FAILED]--- \n");
      break;
    }

    if(list3->size() != 5) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean>list5 = createArrayList<Boolean>();
    list5->add(true);
    list5->add(true);
    list5->add(true);

    ArrayList<Boolean>list6 = createArrayList<Boolean>();
    list6->add(false);
    list6->add(false);
    list6->add(false);

    result = list5->insert(0,list6,100);
#if 0
    printf("size is %d \n",list5->size());
    if(list5->get(0)->toValue() == true) {
         printf("list[0] is true \n");
    } else {
         printf("list[0] is false \n");
    }

    if(list5->get(1)->toValue() == true) {
         printf("list[1] is true \n");
    } else {
         printf("list[1] is false \n");
    }

    if(list5->get(2)->toValue() == true) {
         printf("list[2] is true \n");
    } else {
         printf("list[2] is false \n");
    }

    if(list5->get(3)->toValue() == true) {
         printf("list[3] is true \n");
    } else {
         printf("list[3] is false \n");
    }

    if(list5->get(4)->toValue() == true) {
         printf("list[4] is true \n");
    } else {
         printf("list[4] is false \n");
    }

    if(list5->get(5)->toValue() == true) {
         printf("list[5] is true \n");
    } else {
         printf("list[5] is false \n");
    }
#endif

    if(list5->get(0)->toValue() != false
      ||list5->get(1)->toValue() != false
      ||list5->get(2)->toValue() != false
      ||list5->get(3)->toValue() != true
      ||list5->get(4)->toValue() != true
      ||list5->get(5)->toValue() != true) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case5] [FAILED]--- \n");
      break;
    }

    if(list5->size() != 6) {
      printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)} case6] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insert(int index,ArrayList<Boolean> list,int length)}] [OK]--- \n");
    break;
  }

  //void insertFirst(Integer val);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    list->insertFirst(createBoolean(false));
    if(list->get(0)->toValue() != false
       ||list->get(1)->toValue() != true
       ||list->get(2)->toValue() != true
       ||list->get(3)->toValue() != true) {
         printf("---[ArrayList<Boolean> Test {insertFirst(Boolean val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Boolean> Test {insertFirst(Boolean val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->insertFirst(createBoolean(false));
    if(list2->get(0)->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {insertFirst(Boolean val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Boolean> Test {insertFirst(Boolean val)} case4] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list3 = createArrayList<Boolean>();
    Boolean nt;
    list3->insertFirst(nt);
    if(list3->size() != 0) {
      printf("---[ArrayList<Boolean> Test {insertFirst(Boolean val)} case5] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insertFirst(Boolean val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(bool val);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    list->insertFirst(false);
    if(list->get(0)->toValue() != false
       ||list->get(1)->toValue() != true
       ||list->get(2)->toValue() != true
       ||list->get(3)->toValue() != true) {
         printf("---[ArrayList<Boolean> Test {insertFirst(bool val)} case1] [FAILED]--- \n");
         break;
    }

    if(list->size() != 4) {
        printf("---[ArrayList<Boolean> Test {insertFirst(bool val)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->insertFirst(true);
    if(list2->get(0)->toValue() != true) {
      printf("---[ArrayList<Boolean> Test {insertFirst(bool val)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->size() != 1) {
      printf("---[ArrayList<Boolean> Test {insertFirst(bool val)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insertFirst(bool val)}] [OK]--- \n");
    break;
  }

  //void insertFirst(ArrayList<Boolean> list);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(false);
    list2->add(false);
    list2->add(false);
    list->insertFirst(list2);

    if(list->get(0)->toValue() != false
      ||list->get(1)->toValue() != false
      ||list->get(2)->toValue() != false
      ||list->get(3)->toValue() != true
      ||list->get(4)->toValue() != true
      ||list->get(5)->toValue() != true) {
        printf("---[ArrayList<Boolean> Test {insertFirst(ArrayList<Boolean> list)} case1] [FAILED]--- \n");
        break;
      }

    ArrayList<Boolean> list3 = createArrayList<Boolean>();
    list3->add(false);
    list3->add(false);

    ArrayList<Boolean> list4 = createArrayList<Boolean>();
    list4->insertFirst(list4);

    if(list3->get(0)->toValue() != false
      ||list3->get(1)->toValue() != false){
        printf("---[ArrayList<Boolean> Test {insertFirst(ArrayList<Boolean> list)} case2] [FAILED]--- \n");
        break;
      }

    if(list3->size() != 2) {
      printf("---[ArrayList<Boolean> Test {insertFirst(ArrayList<Boolean> list)} case3] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list5;
    list3->insertFirst(list5);
    if(list3->size() != 2) {
      printf("---[ArrayList<Boolean> Test {insertFirst(ArrayList<Boolean> list)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insertFirst(ArrayList<Boolean> list)}] [OK]--- \n");
    break;
  }

  //void insertLast(Boolean v);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    list->insertLast(createBoolean(false));
    if(list->get(0)->toValue() != true
      ||list->get(1)->toValue() != true
      ||list->get(2)->toValue() != true
      ||list->get(3)->toValue() != false) {
        printf("---[ArrayList<Boolean> Test {insertLast(Boolean v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Boolean> Test {insertLast(Boolean v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(true);
    list2->add(true);
    list2->add(true);
    Boolean t2;
    list2->insertLast(t2);

    if(list2->get(0)->toValue() != true
      ||list2->get(1)->toValue() != true
      ||list2->get(2)->toValue() != true) {
        printf("---[ArrayList<Boolean> Test {insertLast(Boolean v)} case3] [FAILED]--- \n");
        break;
    }

    if(list2->size() != 3) {
      printf("---[ArrayList<Boolean> Test {insertLast(Boolean v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insertLast(Boolean v)} case5] [OK]--- \n");
    break;
  }

  //void insertLast(int v);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);

    list->insertLast(false);
    if(list->get(0)->toValue() != true
      ||list->get(1)->toValue() != true
      ||list->get(2)->toValue() != true
      ||list->get(3)->toValue() != false) {
        printf("---[ArrayList<Boolean> Test {insertLast(bool v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 4) {
      printf("---[ArrayList<Boolean> Test {insertLast(bool v)} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->insertLast(false);

    if(list2->size() != 1) {
      printf("---[ArrayList<Boolean> Test {insertLast(bool v)} case3] [FAILED]--- \n");
      break;
    }

    if(list2->get(0)->toValue() != false) {
      printf("---[ArrayList<Boolean> Test {insertLast(bool v)} case4] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {insertLast(bool v)} case5] [OK]--- \n");
    break;
  }

  //insertLast(ArrayList<Boolean> list);
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(false);
    list->add(false);
    list->add(false);

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    list2->add(true);
    list2->add(true);
    list2->add(true);

    list->insertLast(list2);
    if(list->get(0)->toValue() != false
      ||list->get(1)->toValue() != false
      ||list->get(2)->toValue() != false
      ||list->get(3)->toValue() != true
      ||list->get(4)->toValue() != true
      ||list->get(5)->toValue() != true) {
        printf("---[ArrayList<Boolean> Test {insertLast(ArrayList<Boolean> v)} case1] [FAILED]--- \n");
        break;
    }

    if(list->size() != 6) {
        printf("---[ArrayList<Boolean> Test {insertLast(ArrayList<Boolean> v)} case2] [FAILED]--- \n");
        break;
    }

    ArrayList<Boolean> list3 = createArrayList<Boolean>();
    list3->add(false);
    list3->add(false);
    list3->add(false);

    ArrayList<Boolean> list4;
    list3->insertLast(list4);
    if(list3->get(0)->toValue() != false
      ||list3->get(1)->toValue() != false
      ||list3->get(2)->toValue() != false) {
        printf("---[ArrayList<Boolean> Test {insertLast(ArrayList<Boolean> v)} case3] [FAILED]--- \n");
        break;
    }

    if(list3->size() != 3) {
        printf("---[ArrayList<Boolean> Test {insertLast(ArrayList<Boolean> v)} case4] [FAILED]--- \n");
        break;
    }

    printf("---[ArrayList<Boolean> Test {insertLast(ArrayList<Boolean> v)} case5] [OK]--- \n");
    break;
  }

  //int size();
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);
    if(list->size() != 3) {
      printf("---[ArrayList<Boolean> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    if(list2->size() != 0) {
      printf("---[ArrayList<Boolean> Test {size()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<Boolean> Test {size()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Boolean> getValue;
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(true);
    list->add(true);
    list->add(true);
    list->add(true);
    list->add(true);

    ListIterator<Boolean>iterator = list->getIterator();
    int index = 1;
    while(iterator->hasValue() && index != list->size()) {
      Boolean v = iterator->getValue();
      if(v->toValue() != true) {
        printf("---[ListIterator<Boolean> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      iterator->next();
      index++;
    }

    ArrayList<Boolean> list1 = createArrayList<Boolean>();
    ListIterator<Boolean>iterator1 = list1->getIterator();
    Boolean v = iterator1->getValue();
    if(v != nullptr) {
      printf("---[ListIterator<Boolean> Test {getValue()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Boolean> Test {getValue()} case3] [OK]--- \n");
    break;
  }

  //ListIterator<Integer> hasValue();
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(false);
    list->add(false);
    list->add(false);
    ListIterator<Boolean> iterator = list->getIterator();
    if(!iterator->hasValue()) {
      printf("---[ListIterator<Boolean> Test {hasValue()} case1] [FAILED]--- \n");
      break;
    }

    iterator->next();
    iterator->next();
    iterator->next();

    if(iterator->hasValue()) {
      printf("---[ListIterator<Boolean> Test {hasValue()} case2] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    ListIterator<Boolean> iterator2 = list2->getIterator();
    if(iterator2->hasValue()) {
      printf("---[ListIterator<Boolean> Test {hasValue()} case3] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Boolean> Test {hasValue()} case4] [OK]--- \n");
    break;
  }

  // ListIterator<Integer> next();
  while(1) {
    ArrayList<Boolean> list = createArrayList<Boolean>();
    list->add(false);
    list->add(false);
    list->add(false);
    ListIterator<Boolean> iterator = list->getIterator();

    iterator->next();
    iterator->next();
    if(iterator->next()) {
      printf("---[ListIterator<Boolean> Test {next()} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<Boolean> list2 = createArrayList<Boolean>();
    ListIterator<Boolean> iterator2 = list2->getIterator();
    if(iterator2->next()) {
      printf("---[ListIterator<Boolean> Test {next()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ListIterator<Boolean> Test {next()} case3] [OK]--- \n");
    break;
  }
}
