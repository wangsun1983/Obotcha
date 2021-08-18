#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_CLASS(TestData1) {
public:
  int i;
};

void testArrayList_MyData() {
  //---[ArrayList<T> Test Start]---

      //---[ArrayList<T> Test {void add(T val)} Start]---
      while(1){
          ArrayList<TestData1> list = createArrayList<TestData1>();
          TestData1 t1 = createTestData1();
          t1->i = 1;

          TestData1 t2 = createTestData1();
          t2->i = 2;

          TestData1 t3 = createTestData1();
          t3->i = 3;

          TestData1 t4 = createTestData1();
          t4->i = 4;

          list->add(t1);
          list->add(t2);
          list->add(t3);
          list->add(t4);

          if(list->size() != 4) {
             printf("---[ArrayList<T> Test {void add(T val)} Size error] [FAILED]--- \n");
             break;
          }

          TestData1 t1_1 = list->get(0);
          TestData1 t1_2 = list->get(1);
          TestData1 t1_3 = list->get(2);
          TestData1 t1_4 = list->get(3);

          if(t1_1->i != 1 || t1_2->i != 2 || t1_3->i != 3 || t1_4->i != 4) {
            printf("---[ArrayList<T> Test {void add(T val)} Value error] [FAILED]--- \n");
            break;
          }

          printf("---[ArrayList<T> Test {void add(T val)} Start] [OK]--- \n");
          break;
      }

      //---[ArrayList<T> Test {void add(ArrayList<T> list)} Start]---
      while(1) {
          ArrayList<TestData1> list1 = createArrayList<TestData1>();
          ArrayList<TestData1> list2 = createArrayList<TestData1>();

          TestData1 tt1 = createTestData1();
          tt1->i = 1;

          TestData1 tt2 = createTestData1();
          tt2->i = 2;

          list1->add(tt1);
          list1->add(tt2);

          TestData1 tt1_1 = createTestData1();
          tt1_1->i = 1;

          TestData1 tt2_1 = createTestData1();
          tt2_1->i = 2;

          list2->add(tt1_1);
          list2->add(tt2_1);

          list1->add(list2);

          if(list1->size() != 4) {
            printf("---[ArrayList<T> Test {void add(ArrayList<T> list)} Size error] [FAILED]--- \n");
            break;
          }

          TestData1 v1_1 = list1->get(0);
          TestData1 v1_2 = list1->get(1);
          TestData1 v1_3 = list1->get(2);
          TestData1 v1_4 = list1->get(3);

          if(v1_1->i != 1 || v1_2->i != 2 || v1_3->i != 1 || v1_4->i != 2) {
            printf("---[ArrayList<T> Test {void add(ArrayList<T> list)} Value error] [FAILED]--- \n");
            break;
          }

          printf("---[ArrayList<T> Test {void add(ArrayList<T> list)} Start] [OK]--- \n");
          break;
      }

      //---[ArrayList<T> Test {void clear()} Start]---
      while(1) {
          ArrayList<TestData1> clist = createArrayList<TestData1>();
          TestData1 cl1_1 = createTestData1();
          cl1_1->i = 1;

          clist->add(cl1_1);
          int size = clist->size();
          clist->clear();
          if(clist->size() != 0 || size != 1) {
              printf("---[ArrayList<T> Test {void clear()} Size error] [FAILED]--- \n");
              break;
          }

          printf("---[ArrayList<T> Test {void clear()}] [OK]--- \n");
          break;
      }

      //---[ArrayList<T> Test {remove(int index)} Start]---
      while(1) {
          ArrayList<TestData1> clist = createArrayList<TestData1>();
          TestData1 t1 = createTestData1();
          t1->i = 1;

          TestData1 t2 = createTestData1();
          t2->i = 2;

          TestData1 t3 = createTestData1();
          t3->i = 3;

          clist->add(t1);
          clist->add(t2);
          clist->add(t3);

          TestData1 tt1 = clist->removeAt(0);
          TestData1 tt2 = clist->removeAt(1);

          if(tt1->i != 1 || tt2->i != 3 || clist->size() != 1) {
            printf("---[ArrayList<T> Test {remove(int index)} case1] [FAILED]--- \n");
            break;
          }

          bool isException = false;
          try {
              TestData1 tt3 = clist->removeAt(100);
          } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
          }

          if(!isException) {
            printf("---[ArrayList<T> Test {remove(int index)} case2] [FAILED]--- \n");
            break;
          }

          printf("---[ArrayList<T> Test {remove(int index)}] [OK]--- \n");
          break;
      }

      //---[ArrayList<T> Test {remove(T val)} Start]---
      while(1) {
          ArrayList<TestData1> clist = createArrayList<TestData1>();
          TestData1 t1 = createTestData1();
          t1->i = 1;

          TestData1 t2 = createTestData1();
          t2->i = 2;

          TestData1 t3 = createTestData1();
          t3->i = 3;

          clist->add(t1);
          clist->add(t2);
          clist->add(t3);

          TestData1 tt1 = clist->get(1);
          int result = clist->remove(tt1);
          if(result == -1 || clist->size() != 2) {
            printf("---[ArrayList<T> Test {remove(T val)} case1] [FAILED]--- \n");
            break;
          }

          result = clist->remove(t1);
          if(result == -1 || clist->size() != 1) {
            printf("---[ArrayList<T> Test {remove(T val)} case2] [FAILED]--- \n");
            break;
          }

          TestData1 tt3 = createTestData1();
          tt3->i = 100;
          result =clist->remove(tt3);
          if(result != -1 || clist->size() != 1) {
            printf("---[ArrayList<T> Test {remove(T val)} case3] [FAILED]--- \n");
            break;
          }
          printf("---[ArrayList<T> Test {remove(T val)}] [OK]--- \n");
          break;
      }

      //---[ArrayList<T> Test {indexOf(T val)} Start]---
      while(1) {
          ArrayList<TestData1> clist = createArrayList<TestData1>();
          TestData1 t1 = createTestData1();
          t1->i = 1;

          TestData1 t2 = createTestData1();
          t2->i = 2;

          TestData1 t3 = createTestData1();
          t3->i = 3;

          clist->add(t1);
          clist->add(t2);
          clist->add(t3);

          int index = clist->indexOf(t2);
          if(index != 1) {
            printf("---[ArrayList<T> Test {indexOf(T val)} case1] [FAILED]--- \n");
            break;
          }

          TestData1 t4 = clist->get(2);
          index = clist->indexOf(t4);
          if(index != 2) {
            printf("---[ArrayList<T> Test {indexOf(T val)} case2] [FAILED]--- \n");
            break;
          }

          TestData1 t5 = t4;
          index = clist->indexOf(t5);
          if(index != 2) {
            printf("---[ArrayList<T> Test {indexOf(T val)} case3] [FAILED]--- \n");
            break;
          }

          TestData1 t6 = createTestData1();
          t6->i = 1;
          index = clist->indexOf(t6);
          if(index != -1) {
            printf("---[ArrayList<T> Test {indexOf(T val)} case4] [FAILED]--- \n");
            break;
          }

          printf("---[ArrayList<T> Test {indexOf(T val)}] [OK]--- \n");
          break;
      }

      //---[ArrayList<T> Test {set(int index,T val)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->add(t1);
        clist->add(t2);
        clist->add(t3);

        TestData1 t4 = createTestData1();
        t4->i = 4;

        bool isException = false;
        try {
          clist->set(8,t4);
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<T> Test {set(int index,T val)} case1] [FAILED]--- \n");
          break;
        }

        int size = clist->size();

        int result = clist->set(2,t4);
        if(result == -1) {
          printf("---[ArrayList<T> Test {set(int index,T val)} case2] [FAILED]--- \n");
          break;
        }

        if(clist->size() != size) {
          printf("---[ArrayList<T> Test {set(int index,T val)} case3] [FAILED]--- \n");
          break;
        }

        TestData1 t8 = clist->get(2);
        if(t8->i != t4->i) {
          printf("---[ArrayList<T> Test {set(int index,T val)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {set(int index,T val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {get(int index)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->add(t1);
        clist->add(t2);
        clist->add(t3);

        TestData1 t1_1 = clist->get(0);
        TestData1 t1_2 = clist->get(1);
        TestData1 t1_3 = clist->get(2);

        if(t1_1->i != t1->i
          ||t1_2->i != t2->i
          ||t1_3->i != t3->i) {
            printf("---[ArrayList<T> Test {get(int index)} case1] [FAILED]--- \n");
            break;
          }

        bool isException = false;
        try {
            TestData1 t1_4 = clist->get(200);
        } catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<T> Test {get(int index)} case2] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {get(int index)}] [OK]--- \n");
        break;
      }


      //---[ArrayList<T> Test {insert(int index,T val)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->add(t1);
        clist->add(t2);
        clist->add(t3);

        int size = clist->size();
        TestData1 t4 = createTestData1();
        t4->i = 4;
        clist->insert(1,t4);

        TestData1 t5 = clist->get(1);
        TestData1 t6 = clist->get(2);

        if(t5->i != t4->i
         ||t6->i != t2->i) {
           printf("---[ArrayList<T> Test {insert(int index,T val) case1] [FAILED]--- \n");
           break;
         }

         if(size != clist->size() - 1) {
           printf("---[ArrayList<T> Test {insert(int index,T val) case2] [FAILED]--- \n");
           break;
         }

         printf("---[ArrayList<T> Test {insert(int index,T val)] [OK]--- \n");
         break;
      }

      //---[ArrayList<T> Test {insert(int index,ArrayList<T> list)} Start]---
      while(1){
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->add(t1);
        clist->add(t2);
        clist->add(t3);

        int size = clist->size();

        ArrayList<TestData1> clist2 = createArrayList<TestData1>();
        TestData1 t4 = createTestData1();
        t4->i = 4;

        TestData1 t5 = createTestData1();
        t5->i = 5;

        clist2->add(t4);
        clist2->add(t5);

        int result = clist->insert(1,clist2);
        if(result != 0) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list) case1] [FAILED]--- \n");
          break;
        }

        if((size + clist2->size()) != clist->size()) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list) case2] [FAILED]--- \n");
          break;
        }

        TestData1 tt0 = clist->get(0);
        TestData1 tt1 = clist->get(1);
        TestData1 tt2 = clist->get(2);
        TestData1 tt3 = clist->get(3);
        TestData1 tt4 = clist->get(4);

        if(tt0->i != 1 || tt1->i != 4|| tt2->i != 5 || tt3->i != 2 || tt4->i != 3) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list) case3] [FAILED]--- \n");
          break;
        }

        bool isException = false;
        try {
          result = clist->insert(100,clist2);
        } catch(ArrayIndexOutOfBoundsException e) {
          isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list) case4] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list)] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->add(t1);
        clist->add(t2);
        clist->add(t3);

        ArrayList<TestData1> clist2 = createArrayList<TestData1>();
        TestData1 t4 = createTestData1();
        t4->i = 4;

        TestData1 t5 = createTestData1();
        t5->i = 5;

        TestData1 t6 = createTestData1();
        t6->i = 6;

        clist2->add(t4);
        clist2->add(t5);
        clist2->add(t6);

        int result = clist->insert(1,clist2,2);
        if(result != 0) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case1] [FAILED]--- \n");
          break;
        }

        TestData1 tt0 = clist->get(0);
        TestData1 tt1 = clist->get(1);
        TestData1 tt2 = clist->get(2);
        TestData1 tt3 = clist->get(3);
        TestData1 tt4 = clist->get(4);
        if(tt0->i != 1 || tt1->i != 4 || tt2->i != 5 || tt3->i != 2|| tt4->i != 3) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case2] [FAILED]--- \n");
          break;
        }

        clist->clear();
        clist->add(t1);
        clist->add(t2);
        clist->add(t3);
        bool isException = false;
        try {
            clist->insert(100,clist2,2);
        }catch(ArrayIndexOutOfBoundsException e) {
             isException = true;
        }

        if(!isException) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case3] [FAILED]--- \n");
          break;
        }
        
        int isException2 = false;
        try {
          result = clist->insert(1,clist2,100);
        } catch(ArrayIndexOutOfBoundsException e) {
          isException2 = true;
        }

        if(tt0->i != 1 || tt1->i != 4 || tt2->i != 5 || tt3->i != 2 || tt4->i != 3) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case4] [FAILED]--- \n");
          break;
        }

        if(!isException2) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case4_0] [FAILED]--- \n");
          break;          
        }

        bool isException3 = false;
        try {
            result = clist->insert(-1,clist2,100);
        } catch(ArrayIndexOutOfBoundsException e) {
            isException3 = true;
        }

        if(!isException3) {
            printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case4_1] [FAILED]--- \n");
            break;
        }

        if(tt0->i != 1 || tt1->i != 4 || tt2->i != 5 || tt3->i != 2 || tt4->i != 3) {
          printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case5] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {insertFirst(T val)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->insertFirst(t1);
        clist->insertFirst(t2);
        clist->insertFirst(t3);

        TestData1 tt1 = clist->get(0);
        TestData1 tt2 = clist->get(1);
        TestData1 tt3 = clist->get(2);

        if(tt1->i != 3 || tt2->i != 2 || tt3->i != 1) {
          printf("---[ArrayList<T> Test {insertFirst(T val)}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {insertFirst(T val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {insertFirst(ArrayList<T> list)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->add(t1);
        clist->add(t2);
        clist->add(t3);

        ArrayList<TestData1> clist2 = createArrayList<TestData1>();
        TestData1 t4 = createTestData1();
        t4->i = 4;

        TestData1 t5 = createTestData1();
        t5->i = 5;

        clist2->add(t4);
        clist2->add(t5);

        clist->insertFirst(clist2);

        TestData1 tt0 = clist->get(0);
        TestData1 tt1 = clist->get(1);
        TestData1 tt2 = clist->get(2);
        TestData1 tt3 = clist->get(3);
        TestData1 tt4 = clist->get(4);
        if(tt0->i != 4 || tt1->i != 5 || tt2->i != 1 || tt3->i != 2 || tt4->i != 3) {
          printf("---[ArrayList<T> Test {insertFirst(ArrayList<T> list)} case1] [FAILED]--- \n");
          break;
        }

        int size = clist->size();
        ArrayList<TestData1>clist3 = createArrayList<TestData1>();
        clist->insertFirst(clist3);
        if(clist->size() != size) {
          printf("---[ArrayList<T> Test {insertFirst(ArrayList<T> list)} case2] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {insertFirst(ArrayList<T> list)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {void insertLast(T v)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->insertLast(t1);
        clist->insertLast(t2);
        clist->insertLast(t3);

        TestData1 tt0 = clist->get(0);
        TestData1 tt1 = clist->get(1);
        TestData1 tt2 = clist->get(2);

        if(tt0->i != 1 || tt1->i != 2 || tt2->i != 3) {
          printf("---[ArrayList<T> Test {void insertLast(T v)}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {void insertLast(T v)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {insertLast(ArrayList<T> list)} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        TestData1 t1 = createTestData1();
        t1->i = 1;

        TestData1 t2 = createTestData1();
        t2->i = 2;

        TestData1 t3 = createTestData1();
        t3->i = 3;

        clist->insertLast(t1);
        clist->insertLast(t2);
        clist->insertLast(t3);

        ArrayList<TestData1> clist2 = createArrayList<TestData1>();
        TestData1 t4 = createTestData1();
        t4->i = 4;

        TestData1 t5 = createTestData1();
        t5->i = 5;

        clist2->add(t4);
        clist2->add(t5);
        clist->add(clist2);

        TestData1 tt0 = clist->get(0);
        TestData1 tt1 = clist->get(1);
        TestData1 tt2 = clist->get(2);
        TestData1 tt3 = clist->get(3);
        TestData1 tt4 = clist->get(4);

        if(tt0->i != 1 || tt1->i != 2 || tt2->i != 3 || tt3->i != 4 || tt4->i != 5) {
          printf("---[ArrayList<T> Test {void insertLast(T v)}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {void insertLast(T v)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {size()} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        if(clist->size() != 0) {
          printf("---[ArrayList<T> Test {size()} case1] [FAILED]--- \n");
          break;
        }

        TestData1 t1 = createTestData1();
        t1->i = 1;
        clist->add(t1);
        clist->add(t1);
        clist->add(t1);
        clist->add(t1);
        clist->add(t1);
        if(clist->size() != 5) {
          printf("---[ArrayList<T> Test {size()} case2] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {size()}] [OK]--- \n");
        break;
      }

      //---[ArrayList<T> Test {getIterator()} Start]---
      while(1) {
        ArrayList<TestData1> clist = createArrayList<TestData1>();
        ListIterator<TestData1> iterate = clist->getIterator();
        if(iterate == nullptr) {
          printf("---[ArrayList<T> Test {getIterator()}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {getIterator()}] [OK]--- \n");
        break;
      }


  //---[ListIterator<T> Test Start]---

    //---[ListIterator<T> Test {ListIterator(ArrayList<T> list)} Start]---
    while(1) {
      ArrayList<TestData1> clist = createArrayList<TestData1>();
      TestData1 t1 = createTestData1();
      t1->i = 1;

      TestData1 t2 = createTestData1();
      t2->i = 2;

      TestData1 t3 = createTestData1();
      t3->i = 3;

      clist->add(t1);
      clist->add(t2);
      clist->add(t3);
      ListIterator<TestData1> iterator = createListIterator<TestData1>(clist);

      int index = 1;
      bool isOk = true;
      while(iterator->hasValue()) {
          if(iterator->getValue()->i != index) {
              isOk = false;
              break;
          }
          index++;
          iterator->next();
      }

      if(!isOk) {
        printf("---[ArrayList<T> Test {getValue()/hasValue()/next()}] [FAILED]--- \n");
        break;
      }

      printf("---[ArrayList<T> Test {getValue()/hasValue()/next()}] [OK]--- \n");
      break;
    }

    //---[ListIterator<T> Test {getValue()} Start]---
    while(1) {
      ArrayList<TestData1> clist = createArrayList<TestData1>();
      TestData1 t1 = createTestData1();
      t1->i = 1;

      TestData1 t2 = createTestData1();
      t2->i = 2;

      TestData1 t3 = createTestData1();
      t3->i = 3;

      clist->add(t1);
      clist->add(t2);
      clist->add(t3);

      ListIterator<TestData1> iterator = clist->getIterator();
      int index = 1;
      bool isOk = true;
      while(iterator->hasValue()) {
          if(iterator->getValue()->i != index) {
              isOk = false;
              break;
          }
          index++;
          iterator->next();
      }

      if(!isOk) {
        printf("---[ArrayList<T> Test {getValue()} case1] [FAILED]--- \n");
        break;
      }

      ArrayList<TestData1> clist2 = createArrayList<TestData1>();
      ListIterator<TestData1> iterator2 = clist2->getIterator();
      bool isException = false;
      try {
        iterator2->getValue();
      }catch(ArrayIndexOutOfBoundsException e) {
           isException = true;
      }

      if(!isException) {
        printf("---[ArrayList<T> Test {getValue()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[ArrayList<T> Test {getValue()}] [OK]--- \n");
      break;
    }

  //--[_ListIterator<T> Test {remove()} Start]---
  while(1) {
    ArrayList<TestData1> list = createArrayList<TestData1>();
    TestData1 t1 = createTestData1();
    t1->i = 1;

    TestData1 t2 = createTestData1();
    t2->i = 2;

    TestData1 t3 = createTestData1();
    t3->i = 3;

    TestData1 t4 = createTestData1();
    t4->i = 4;

    TestData1 t5 = createTestData1();
    t5->i = 5;

    list->add(t1);
    list->add(t2);
    list->add(t3);
    list->add(t4);
    list->add(t5);

    ListIterator<TestData1> iterator = list->getIterator();
    while(iterator->hasValue()) {
      if(iterator->getValue()->i == 3) {
        iterator->remove();
      }else {
        iterator->next();
      }
    }

    if(list->size() != 4) {
        printf("---[ListIterator<T> Test {remove()} case0] [FAILED]--- \n");
        break;
    }

    if(list->get(0)->i != 1 ||list->get(1)->i != 2
      ||list->get(2)->i != 4||list->get(3)->i != 5) {
        printf("---[ListIterator<T> Test {remove()} case2] [FAILED]--- \n");
        break;
    }

    printf("---[ListIterator<T> Test {remove()} case3] [OK]--- \n");
    break;
  }

}
