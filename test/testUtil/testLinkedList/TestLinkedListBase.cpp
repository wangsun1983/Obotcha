#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

void testLinkeListBase() {

    //case1 string putLast
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        std::vector<std::string> list;
        list.push_back("a");
        list.push_back("b");
        list.push_back("c");

        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        if(mList->size() != 3) {
          printf("LinkedList base test1-------[FAIL] \n");
          break;
        }

        LinkedListIterator<String> iterator = mList->getIterator();
        int count = 0;
        while(iterator->hasValue()) {
          String v1 = iterator->getValue();
          if(!v1->equals(list[count])) {
            printf("v1 is %s,vv is %s \n",v1->toChars(),list[count].c_str());
            printf("LinkedList base test2-------[FAIL] \n");
            break;
          }
          iterator->next();
          count++;
        }

        break;
    }

    //case2 int putLast
    while(1) {
        LinkedList<int> mList = createLinkedList<int>();

        std::vector<int> list;
        list.push_back(4);
        list.push_back(5);
        list.push_back(6);

        mList->putLast(4);
        mList->putLast(5);
        mList->putLast(6);

        if(mList->size() != 3) {
          printf("LinkedList base test3-------[FAIL],size is %d \n",mList->size());
          break;
        }

        LinkedListIterator<int> iterator = mList->getIterator();
        int count = 0;
        while(iterator->hasValue()) {
          int v1 = iterator->getValue();
          if(v1 != list[count]) {
            printf("v1 is %d,vv is %d \n",v1,list[count]);
            printf("LinkedList base test4-------[FAIL] \n");
            break;
          }
          iterator->next();
          count++;
        }

        break;
    }

    //case3 string putFirst
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        std::vector<std::string> list;
        list.push_back("c");
        list.push_back("b");
        list.push_back("a");

        mList->putFirst(createString("a"));
        mList->putFirst(createString("b"));
        mList->putFirst(createString("c"));

        if(mList->size() != 3) {
          printf("LinkedList base test5-------[FAIL] \n");
          break;
        }

        LinkedListIterator<String> iterator = mList->getIterator();
        int count = 0;
        while(iterator->hasValue()) {
          String v1 = iterator->getValue();
          if(!v1->equals(list[count])) {
            printf("v1 is %s,vv is %s \n",v1->toChars(),list[count].c_str());
            printf("LinkedList base test5-------[FAIL] \n");
            break;
          }
          iterator->next();
          count++;
        }

        break;
    }

    //case4 int putFirst
    while(1) {
        LinkedList<int> mList = createLinkedList<int>();

        std::vector<int> list;
        list.push_back(6);
        list.push_back(5);
        list.push_back(4);

        mList->putFirst(4);
        mList->putFirst(5);
        mList->putFirst(6);

        if(mList->size() != 3) {
          printf("LinkedList base test6-------[FAIL],size is %d \n",mList->size());
          break;
        }

        LinkedListIterator<int> iterator = mList->getIterator();
        int count = 0;
        while(iterator->hasValue()) {
          int v1 = iterator->getValue();
          if(v1 != list[count]) {
            printf("v1 is %d,vv is %d \n",v1,list[count]);
            printf("LinkedList base test7-------[FAIL] \n");
            break;
          }
          iterator->next();
          count++;
        }

        break;
    }

    //case4 String iterator remove
    while(1) {
      LinkedList<String> mList = createLinkedList<String>();
      std::vector<std::string> list;
      list.push_back("a");
      //list.push_back("b");
      list.push_back("c");

      mList->putLast("a");
      mList->putLast("b");
      mList->putLast("c");

      LinkedListIterator<String> iterator = mList->getIterator();
      while(iterator->hasValue()) {
        String v = iterator->getValue();
        if(v->equals("b")) {
          iterator->remove();
          continue;
        }
        iterator->next();
      }

      if(mList->size() != 2) {
        printf("LinkedList base test8-------[FAIL] \n");
      }

      iterator = mList->getIterator();
      int count = 0;
      while(iterator->hasValue()) {
          String v = iterator->getValue();
          if(!v->equals(list[count])) {
            printf("v1 is %s,vv is %s \n",v->toChars(),list[count].c_str());
            printf("LinkedList base test9-------[FAIL] \n");
            break;
          }
          iterator->next();
          count++;
      }
      break;
    }

    //case5 String iterator remove
    while(1) {
      LinkedList<Integer> mList = createLinkedList<Integer>();
      std::vector<int> list;
      list.push_back(4);
      //list.push_back(5);
      list.push_back(6);

      mList->putLast(createInteger(4));
      mList->putLast(createInteger(5));
      mList->putLast(createInteger(6));

      LinkedListIterator<Integer> iterator = mList->getIterator();
      while(iterator->hasValue()) {
        int v = iterator->getValue()->toValue();
        if(v == 5) {
          iterator->remove();
          continue;
        }
        iterator->next();
      }

      if(mList->size() != 2) {
        printf("LinkedList base test10-------[FAIL] \n");
      }

      iterator = mList->getIterator();
      int count = 0;
      while(iterator->hasValue()) {
          int v = iterator->getValue()->toValue();
          if(v != list[count]) {
            printf("v1 is %d,vv is %d \n",v,list[count]);
            printf("LinkedList base test11-------[FAIL] \n");
            break;
          }
          iterator->next();
          count++;
      }
      break;
    }

    printf("LinkedList base test100-------[OK] \n");

}
