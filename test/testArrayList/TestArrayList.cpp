#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"

void dump(ArrayList<Integer> list) {
    int size = list->size();
    for(int i = 0;i<size;i++) {
        Integer val = list->get(i);
        printf("list[%d] is %d \n",i,val->toValue());
    }
}

int main() {

    printf("---[ArrayList Test Start]--- \n");
    {
        ArrayList<Integer> list1 = createArrayList<Integer>();
        //set value
        for(int i = 0;i<1024;i++) {
            list1->add(i);
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
          printf("ArrayList add test1-------[OK] \n");
        } else {
          printf("ArrayList add test1-------[FAIL] \n");
        }
    }

    //test void add(T val)
    {
      ArrayList<Integer> list = createArrayList<Integer>();
      list->add(createInteger(100));
      if(list->size() == 1
         && (list->get(0)->toValue() == 100)) {
           printf("ArrayList add test2-------[OK] \n");
         } else {
           printf("ArrayList add test2-------[FAIL] \n");
         }
    }

    //test void add(ArrayList<T> list)
    {
      ArrayList<Integer> list1 = createArrayList<Integer>();
      ArrayList<Integer> list2 = createArrayList<Integer>();

      list1->add(1);
      list2->add(2);
      list2->add(3);
      list1->add(list2);

      bool result = true;
      if(list1->get(0)->toValue() != 1) {
        result = false;
      } else if(list1->get(1)->toValue() != 2) {
        result = false;
      } else if(list1->get(2)->toValue() != 3) {
        result = false;
      }

      if(result) {
        printf("ArrayList add test3-------[OK] \n");
      } else {
        printf("ArrayList add test3-------[FAIL] \n");
      }
    }

    //test binnary search
    {
        printf("binary search!!!!! \n");
        ArrayList<Integer> list1 = createArrayList<Integer>();
        list1->add(1);
        list1->add(10);
        list1->add(20);
        list1->add(30);
        list1->add(90);

        int insertVal = 100;
        int start = 0;
        int end = list1->size() - 1;
        int index = 0;
        while(start <= end) {
            //sleep(3);
            index = (start+end)/2;
            printf("start is %d,end is %d,index is %d \n",start,end,index);
            Integer m = list1->get(index);
            if(m->toValue() > insertVal) {
                end = index - 1;
            } else if(m->toValue() < insertVal) {
                start = index + 1;
            } else if(m->toValue() == insertVal) {
                break;
            }
        }

        printf("start is %d,end is %d,index is %d \n",start,end,index);
        list1->insert(start,createInteger(insertVal));

        dump(list1);

    }

}
