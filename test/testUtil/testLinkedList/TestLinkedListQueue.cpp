#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

int testLinkeListQueue() {

    //case1 string dequeueFirst
    while(1) {
      LinkedList<String> list = createLinkedList<String>();
      list->enQueueLast("a");
      list->enQueueLast("b");
      list->enQueueLast("c");
      list->enQueueLast("d");
      list->enQueueLast("e");

      std::vector<std::string> vect;
      vect.push_back("a");
      vect.push_back("b");
      vect.push_back("c");
      vect.push_back("d");
      vect.push_back("e");

      int size = list->size();
      int count = 0;
      while(size > 0) {
        String ss = list->deQueueFirst();
        if(!ss->equals(vect[count])) {
          printf("LinkedList queue test1-------[FAIL]\n");
        }
        count++;
        size--;
      }
      break;
    }

    //case2 int dequeueFirst
    while(1) {
      LinkedList<Integer> list = createLinkedList<Integer>();
      list->enQueueLast(createInteger(1));
      list->enQueueLast(createInteger(2));
      list->enQueueLast(createInteger(3));
      list->enQueueLast(createInteger(4));
      list->enQueueLast(createInteger(5));

      std::vector<int> vect;
      vect.push_back(1);
      vect.push_back(2);
      vect.push_back(3);
      vect.push_back(4);
      vect.push_back(5);

      int size = list->size();
      int count = 0;
      while(size > 0) {
        int ss = list->deQueueFirst()->toValue();
        if(ss != vect[count]) {
          printf("LinkedList queue test2-------[FAIL]\n");
        }
        count++;
        size--;
      }
      break;
    }

    //case3 string dequeueFirst
    while(1) {
      LinkedList<String> list = createLinkedList<String>();
      list->enQueueLast("a");
      list->enQueueLast("b");
      list->enQueueLast("c");
      list->enQueueLast("d");
      list->enQueueLast("e");

      std::vector<std::string> vect;
      vect.push_back("e");
      vect.push_back("d");
      vect.push_back("c");
      vect.push_back("b");
      vect.push_back("a");

      int size = list->size();
      int count = 0;
      while(size > 0) {
        String ss = list->deQueueLast();
        if(!ss->equals(vect[count])) {
          printf("LinkedList queue test3-------[FAIL]\n");
        }
        count++;
        size--;
      }
      break;
    }

    //case4 int dequeueFirst
    while(1) {
      LinkedList<Integer> list = createLinkedList<Integer>();
      list->enQueueLast(createInteger(1));
      list->enQueueLast(createInteger(2));
      list->enQueueLast(createInteger(3));
      list->enQueueLast(createInteger(4));
      list->enQueueLast(createInteger(5));

      std::vector<int> vect;
      vect.push_back(5);
      vect.push_back(4);
      vect.push_back(3);
      vect.push_back(2);
      vect.push_back(1);

      int size = list->size();
      int count = 0;
      while(size > 0) {
        int ss = list->deQueueLast()->toValue();
        if(ss != vect[count]) {
          printf("LinkedList queue test4-------[FAIL]\n");
        }
        count++;
        size--;
      }
      break;
    }

    printf("LinkedList queue test100-------[OK]\n");


}
