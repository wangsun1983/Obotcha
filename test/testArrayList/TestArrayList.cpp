#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

void dump(ArrayList<Integer> list) {
    int size = list->size();
    for(int i = 0;i<size;i++) {
        Integer val = list->get(i);
        printf("list[%d] is %d \n",i,val->toValue());
    }
}

DECLARE_SIMPLE_CLASS(TestData1) {
public:
  int i;
};

int main() {

    //---[ArrayList<T> Test Start]---
    {
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

            TestData1 tt1 = clist->remove(0);
            TestData1 tt2 = clist->remove(1);

            if(tt1->i != 1 || tt2->i != 3 || clist->size() != 1) {
              printf("---[ArrayList<T> Test {remove(int index)} case1] [FAILED]--- \n");
              break;
            }

            TestData1 tt3 = clist->remove(100);
            if(tt3 != nullptr) {
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
          int result = clist->set(8,t4);
          if(result != -1) {
            printf("---[ArrayList<T> Test {set(int index,T val)} case1] [FAILED]--- \n");
            break;
          }

          int size = clist->size();

          result = clist->set(2,t4);
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

          TestData1 t1_4 = clist->get(200);
          if(t1_4 != nullptr) {
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

          result = clist->insert(100,clist2);
          if(result != -1) {
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

          result = clist->insert(100,clist2,2);
          if(result != -1) {
            printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case3] [FAILED]--- \n");
            break;
          }

          result = clist->insert(1,clist2,100);
          if(tt0->i != 1 || tt1->i != 4 || tt2->i != 5 || tt3->i != 2 || tt4->i != 3) {
            printf("---[ArrayList<T> Test {insert(int index,ArrayList<T> list,int length)} case4] [FAILED]--- \n");
            break;
          }

          result = clist->insert(-1,clist2,100);
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
    }

    //---[ListIterator<T> Test Start]---
    {
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
        if(iterator2->getValue() != nullptr) {
          printf("---[ArrayList<T> Test {getValue()} case2] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<T> Test {getValue()}] [OK]--- \n");
        break;
      }
  }


  //---[ArrayList<String> Test Start]---
  {
      //---[ArrayList<String> Test {add(char *val)} Start]---
      while(1) {
          ArrayList<String> list = createArrayList<String>();
          list->add("a");
          list->add("b");
          list->add(createString("c"));
          if(!list->get(0)->equals("a")
          || !list->get(1)->equals("b")
          || !list->get(2)->equals("c")) {
              printf("---[ArrayList<String> Test {add(char * val)} case1] [FAILED]--- \n");
              break;
          }

          int size = list->size();
          list->add(nullptr);
          if(list->size() != size) {
            printf("---[ArrayList<String> Test {add(char * val)} case2] [FAILED]--- \n");
            break;
          }

          printf("---[ArrayList<String> Test {add(char * val)}] [OK]--- \n");
          break;
      }

      //---[ArrayList<String> Test {add(std::string v)} Start]---
      while(1) {
          ArrayList<String> list = createArrayList<String>();

          std::string s1("a");
          std::string s2("b");
          std::string s3("c");

          list->add(s1);
          list->add(s2);
          list->add(s3);

          if(!list->get(0)->equals("a")
          || !list->get(1)->equals("b")
          || !list->get(2)->equals("c")) {
              printf("---[ArrayList<String> Test {add(std::string val) case1] [FAILED]--- \n");
              break;
          }

          printf("---[ArrayList<String> Test {add(std::string val)] [OK]--- \n");
          break;
      }

      //---[ArrayList<String> Test {add(String val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add(createString("c"));
        if(!list->get(0)->equals("a")
        || !list->get(1)->equals("b")
        || !list->get(2)->equals("c")) {
            printf("---[ArrayList<String> Test {add(String val)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[ArrayList<String> Test {add(String val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {add(ArrayList<String> list)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");

        ArrayList<String> list2 = createArrayList<String>();
        list2->add("c");
        list2->add("d");

        list->add(list2);

        if(!list->get(0)->equals("a")
        || !list->get(1)->equals("b")
        || !list->get(2)->equals("c")
        || !list->get(3)->equals("d")) {
            printf("---[ArrayList<String> Test {add(ArrayList<String> list)}] [FAILED]--- \n");
            break;
        }

        printf("---[ArrayList<String> Test {add(ArrayList<String> list)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {clear()} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("1");
        int size = list->size();
        list->clear();
        if(list->size() != 0 || size != 1) {
          printf("---[ArrayList<String> Test {clear()}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {clear()}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {remove(int index)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        String v = list->remove(1);
        if(!v->equals("b")) {
          printf("---[ArrayList<String> Test {remove(int index)} case1] [FAILED]--- \n");
          break;
        }

        if(list->size() != 2) {
          printf("---[ArrayList<String> Test {remove(int index)} case2] [FAILED]--- \n");
          break;
        }

        v = list->remove(5);
        if(v != nullptr) {
          printf("---[ArrayList<String> Test {remove(int index)} case3] [FAILED]--- \n");
          break;
        }

        v = list->remove(0);
        v = list->remove(0);
        v = list->remove(0);
        v = list->remove(0);
        if(v != nullptr) {
          printf("---[ArrayList<String> Test {remove(int index)} case4] [FAILED]--- \n");
          break;
        }

        v = list->remove(-1);
        if(v != nullptr) {
          printf("---[ArrayList<String> Test {remove(int index)} case5] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {remove(int index)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {remove(String v)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        int result = list->remove("a");
        if(result == -1) {
          printf("---[ArrayList<String> Test {remove(String v)} case1] [FAILED]--- \n");
          break;
        }

        if(list->size() != 2) {
          printf("---[ArrayList<String> Test {remove(String v)} case2] [FAILED]--- \n");
          break;
        }

        String s;
        result = list->remove(s);
        if(result != -1) {
          printf("---[ArrayList<String> Test {remove(String v)} case3] [FAILED]--- \n");
          break;
        }

        if(list->size() != 2) {
          printf("---[ArrayList<String> Test {remove(String v)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {remove(String v)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {indexOf(String v)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        if(list->indexOf("a") < 0
        ||list->indexOf("b") < 0
        ||list->indexOf("c") < 0) {
          printf("---[ArrayList<String> Test {indexOf(String v)} case1] [FAILED]--- \n");
          break;
        }

        String s;
        int index = list->indexOf(s);
        if(list->indexOf(s) != -1) {
          printf("---[ArrayList<String> Test {indexOf(String v)} case2] [FAILED]--- \n");
          break;
        }

        if(list->indexOf("d") >= 0) {
          printf("---[ArrayList<String> Test {indexOf(String v)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {indexOf(String v)}] [OK]--- \n");
        break;
      }
      //---[ArrayList<String> Test {set(int index,String val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        list->set(0,"d");
        if(!list->get(0)->equals("d")
        || !list->get(1)->equals("b")
        || !list->get(2)->equals("c")) {
            printf("---[ArrayList<String> Test {set(int index,String val)} case1] [FAILED]--- \n");
            break;
        }

        int result = list->set(100,"a");
        if(result != -1) {
          printf("---[ArrayList<String> Test {set(int index,String val)} case2] [FAILED]--- \n");
          break;
        }

        result = list->set(-1,"a");
        if(result != -1) {
          printf("---[ArrayList<String> Test {set(int index,String val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {set(int index,String val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {get(int index)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("c")) {
          printf("---[ArrayList<String> Test {get(int index)} case1] [FAILED]--- \n");
          break;
        }

        String str = list->get(-1);
        if(str != nullptr) {
          printf("---[ArrayList<String> Test {get(int index)} case2] [FAILED]--- \n");
          break;
        }

        String str2 = list->get(1000);
        if(str2 != nullptr) {
          printf("---[ArrayList<String> Test {get(int index)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {get(int index)}] [OK]--- \n");
        break;
      }
      //---[ArrayList<String> Test {insert(int index,String val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(createString("a"));
        list->add(createString("b"));
        list->add(createString("c"));

        list->insert(1,createString("d"));
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("d")
        ||!list->get(2)->equals("b")
        ||!list->get(3)->equals("c")) {
          printf("---[ArrayList<String> Test {insert(int index,String val)} case1] [FAILED]--- \n");
          break;
        }

        int result = list->insert(50,"d");
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,String val)} case2] [FAILED]--- \n");
          break;
        }

        result = list->insert(-1,"d");
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,String val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,String val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,char* val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        list->insert(1,"d");
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("d")
        ||!list->get(2)->equals("b")
        ||!list->get(3)->equals("c")) {
          printf("---[ArrayList<String> Test {insert(int index,char* val)} case1] [FAILED]--- \n");
          break;
        }

        int result = list->insert(50,"d");
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,char* val)} case2] [FAILED]--- \n");
          break;
        }

        result = list->insert(-1,"d");
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,char* val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,char* val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,std::string val)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add(std::string("a"));
        list->add(std::string("b"));
        list->add(std::string("c"));

        list->insert(1,std::string("d"));
        if(!list->get(0)->equals(std::string("a"))
        ||!list->get(1)->equals(std::string("d"))
        ||!list->get(2)->equals(std::string("b"))
        ||!list->get(3)->equals(std::string("c"))) {
          printf("---[ArrayList<String> Test {insert(int index,std::string val)} case1] [FAILED]--- \n");
          break;
        }

        int result = list->insert(50,std::string("d"));
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,std::string val)} case2] [FAILED]--- \n");
          break;
        }

        result = list->insert(-1,std::string("d"));
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,std::string val)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,std::string val)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        ArrayList<String> list2 = createArrayList<String>();
        list2->add("d");
        list2->add("e");

        list->insert(2,list2);
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("d")
        ||!list->get(3)->equals("e")
        ||!list->get(4)->equals("c")){
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case1] [FAILED]--- \n");
          break;
        }

        int result = list->insert(200,list2);
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case2] [FAILED]--- \n");
          break;
        }

        result = list->insert(-1,list2);
        if(result != -1) {
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case3] [FAILED]--- \n");
          break;
        }

        int size = list->size();
        ArrayList<String> list3 = createArrayList<String>();
        list->insert(0,list3);

        if(size != list->size()) {
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list)}] [OK]--- \n");
        break;
      }

      //---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)} Start]---
      while(1) {
        ArrayList<String> list = createArrayList<String>();
        list->add("a");
        list->add("b");
        list->add("c");

        ArrayList<String> list2 = createArrayList<String>();
        list2->add("d");
        list2->add("e");
        list2->add("f");

        list->insert(2,list2,2);
        //printf("list->get(0) is %s \n",list->get(0)->toChars());
        //printf("list->get(1) is %s \n",list->get(1)->toChars());
        //printf("list->get(2) is %s \n",list->get(2)->toChars());
        //printf("list->get(3) is %s \n",list->get(3)->toChars());
        //printf("list->get(4) is %s \n",list->get(4)->toChars());
        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("d")
        ||!list->get(3)->equals("e")
        ||!list->get(4)->equals("c")){
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)} case1] [FAILED]--- \n");
          break;
        }


        list->clear();
        list->add("a");
        list->add("b");
        list->add("c");
        list->insert(2,list2,100);
        //printf("list->get(0) is %s \n",list->get(0)->toChars());
        //printf("list->get(1) is %s \n",list->get(1)->toChars());
        //printf("list->get(2) is %s \n",list->get(2)->toChars());
        //printf("list->get(3) is %s \n",list->get(3)->toChars());
        //printf("list->get(4) is %s \n",list->get(4)->toChars());
        //printf("list->get(5) is %s \n",list->get(5)->toChars());

        if(!list->get(0)->equals("a")
        ||!list->get(1)->equals("b")
        ||!list->get(2)->equals("d")
        ||!list->get(3)->equals("e")
        ||!list->get(4)->equals("f")
        ||!list->get(5)->equals("c")){
          printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)}] [FAILED]--- \n");
          break;
        }

        printf("---[ArrayList<String> Test {insert(int index,ArrayList<String> list,int length)}] [OK]--- \n");
        break;
      }
  }
  //---[ArrayList<String> Test {insertFirst(String val)} Start]---
  while(1){
    ArrayList<String> list = createArrayList<String>();
    list->add(createString("a"));
    list->add(createString("b"));
    list->add(createString("c"));

    list->insertFirst(createString("d"));
    if(!list->get(0)->equals("d")
    ||!list->get(1)->equals("a")
    ||!list->get(2)->equals("b")
    ||!list->get(3)->equals("c")){
      printf("---[ArrayList<String> Test {insertFirst(String val)} case1] [FAILED]--- \n");
      break;
    }

    String str1;
    int size = list->size();
    list->insertFirst(str1);
    if(list->size() != size) {
      printf("---[ArrayList<String> Test {insertFirst(String val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertFirst(String val)}] [OK]--- \n");
    break;
  }

  //---[ArrayList<String> Test {insertFirst(const char * val)} Start]---
  while(1){
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");

    list->insertFirst(createString("d"));
    if(!list->get(0)->equals("d")
    ||!list->get(1)->equals("a")
    ||!list->get(2)->equals("b")
    ||!list->get(3)->equals("c")){
      printf("---[ArrayList<String> Test {insertFirst(const char * val)} case1] [FAILED]--- \n");
      break;
    }

    String str1;
    int size = list->size();
    list->insertFirst(str1);
    if(list->size() != size) {
      printf("---[ArrayList<String> Test {insertFirst(const char * val)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertFirst(const char * val)}] [OK]--- \n");
    break;
  }

  //---[ArrayList<String> Test {insertFirst(ArrayList<String> list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");

    ArrayList<String> list2 = createArrayList<String>();
    list2->add("e");
    list2->add("f");
    list2->add("g");

    list->insertFirst(list2);
    if(!list->get(0)->equals("e")
    ||!list->get(1)->equals("f")
    ||!list->get(2)->equals("g")
    ||!list->get(3)->equals("a")
    ||!list->get(4)->equals("b")
    ||!list->get(5)->equals("c")){
      //printf("list->get(0) is %s \n",list->get(0)->toChars());
      //printf("list->get(1) is %s \n",list->get(1)->toChars());
      //printf("list->get(2) is %s \n",list->get(2)->toChars());
      //printf("list->get(3) is %s \n",list->get(3)->toChars());
      //printf("list->get(4) is %s \n",list->get(4)->toChars());
      //printf("list->get(5) is %s \n",list->get(5)->toChars());
      printf("---[ArrayList<String> Test {insertFirst(ArrayList<String> list)} case1] [FAILED]--- \n");
      break;
    }

    ArrayList<String> list3;
    int size = list->size();
    list->add(list3);
    if(size != list->size()) {
      printf("---[ArrayList<String> Test {insertFirst(ArrayList<String> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertFirst(ArrayList<String> list)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {insertLast(String v)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");

    list->insertLast(createString("d"));
    if(!list->get(0)->equals("a")
    ||!list->get(1)->equals("b")
    ||!list->get(2)->equals("c")
    ||!list->get(3)->equals("d")){
      printf("---[ArrayList<String> Test {insertLast(String v)} case1] [FAILED]--- \n");
      break;
    }

    String s;
    int size = list->size();
    list->insertLast(s);
    if(size != list->size()) {
      printf("---[ArrayList<String> Test {insertLast(String v)} case2] [FAILED]--- \n");
      break;
    }
    printf("---[ArrayList<String> Test {insertLast(String v)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {insertLast(const char *s)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");

    list->insertLast("d");
    if(!list->get(0)->equals("a")
    ||!list->get(1)->equals("b")
    ||!list->get(2)->equals("c")
    ||!list->get(3)->equals("d")){
      printf("---[ArrayList<String> Test {insertLast(const char * s)} case1] [FAILED]--- \n");
      break;
    }

    char *p = nullptr;
    int size = list->size();
    list->insertLast(p);
    if(size != list->size()) {
      printf("---[ArrayList<String> Test {insertLast(const char *s )} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertLast(const char *s)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {insertLast(ArrayList<String> list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");

    ArrayList<String> list2 = createArrayList<String>();
    list2->add("e");
    list2->add("f");
    list2->add("g");

    list->insertLast(list2);
    if(!list->get(0)->equals("a")
    ||!list->get(1)->equals("b")
    ||!list->get(2)->equals("c")
    ||!list->get(3)->equals("e")
    ||!list->get(4)->equals("f")
    ||!list->get(5)->equals("g")){
      printf("---[ArrayList<String> Test {insertLast(ArrayList<String> list)} case1] [FAILED]--- \n");
      break;
    }

    int size = list->size();
    ArrayList<String> list3;
    list->insertLast(list3);
    if(size != list->size()) {
      printf("---[ArrayList<String> Test {insertLast(ArrayList<String> list)} case2] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {insertLast(ArrayList<String> list)}] [OK]--- \n");
    break;
  }
  //---[ArrayList<String> Test {size()} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    if(list->size() != 1) {
      printf("---[ArrayList<String> Test {size()} case1] [FAILED]--- \n");
      break;
    }

    list->clear();
    if(list->size() != 0) {
      printf("---[ArrayList<String> Test {size()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {size()}] [OK]--- \n");
    break;
  }

  //---[ArrayList<String> Test {getIterator()} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    if(list->getIterator()== nullptr) {
      printf("---[ArrayList<String> Test {getIterator()} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {getIterator()}] [OK]--- \n");
    break;
  }
  //--[_ListIterator<String> Test {_ListIterator(ArrayList<String> list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");
    list->add("d");

    ListIterator<String> iterator = createListIterator<String>(list);
    int index = 0;
    bool isOk = true;
    while(iterator->hasValue()) {
      if(!iterator->getValue()->equals(list->get(index))) {
        isOk = false;
        break;
      }
      iterator->next();
      index++;
    }

    if(!isOk) {
      printf("---[ArrayList<String> Test {_ListIterator(ArrayList<String> list)} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {_ListIterator(ArrayList<String> list)}] [OK]--- \n");
    break;
  }

  //--[_ListIterator<String> Test {_ListIterator(_ArrayList<String> *list)} Start]---
  while(1) {
    ArrayList<String> list = createArrayList<String>();
    list->add("a");
    list->add("b");
    list->add("c");
    list->add("d");

    ListIterator<String> iterator = list->getIterator();
    int index = 0;
    bool isOk = true;
    while(iterator->hasValue()) {
      if(!iterator->getValue()->equals(list->get(index))) {
        isOk = false;
        break;
      }
      iterator->next();
      index++;
    }

    if(!isOk) {
      printf("---[ArrayList<String> Test {_ListIterator(_ArrayList<String> *list)} case0] [FAILED]--- \n");
      break;
    }

    printf("---[ArrayList<String> Test {_ListIterator(_ArrayList<String> *list)}] [OK]--- \n");
    break;
  }
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
}
