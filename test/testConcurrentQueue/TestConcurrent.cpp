#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

void dump(ConcurrentQueue<Integer> list) {
    int size = list->size();
    for(int i = 0;i<size;i++) {
        Integer val = list->get(i);
        printf("list value is %d \n",val->toValue());
    }
}

int main() {

    printf("---[ConcurrentQueue Test Start]--- \n");
    {
        ConcurrentQueue<Integer> list1 = createConcurrentQueue<Integer>();
        //set value
        for(int i = 0;i<1024;i++) {
            list1->enQueueLast(i);
        }

        //check value
        bool result = true;
        for(int i = 0;i<1024;i++) {
            if(list1->get(i)->toValue() != i) {
              result = false;
              break;
            }
        }

        if(result) {
          printf("ConcurrentQueue add test1-------[OK] \n");
        } else {
          printf("ConcurrentQueue add test1-------[FAIL] \n");
        }
    }

    //test void add(T val)
    {
      ConcurrentQueue<Integer> list = createConcurrentQueue<Integer>();
      list->enQueueLast(createInteger(100));
      if(list->size() == 1
         && (list->get(0)->toValue() == 100)) {
           printf("ConcurrentQueue add test2-------[OK] \n");
         } else {
           printf("ConcurrentQueue add test2-------[FAIL] \n");
         }
    }

    //test void add(ConcurrentQueue<T> list)
    {
      ConcurrentQueue<Integer> list1 = createConcurrentQueue<Integer>();
      ConcurrentQueue<Integer> list2 = createConcurrentQueue<Integer>();

      list1->enQueueLast(1);
      list1->enQueueLast(2);
      list1->enQueueLast(3);
      //list1->add(list2);

      bool result = true;
      if(list1->get(0)->toValue() != 1) {
        result = false;
      } else if(list1->get(1)->toValue() != 2) {
        result = false;
      } else if(list1->get(2)->toValue() != 3) {
        result = false;
      }

      if(result) {
        printf("ConcurrentQueue add test3-------[OK] \n");
      } else {
        printf("ConcurrentQueue add test3-------[FAIL] \n");
      }
    }

}
