#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Double.hpp"
#include "Double.hpp"

using namespace obotcha;

DECLARE_CLASS(SimpleDoubleData) {
public:
  double i;
};

void testHashMapSimpleDouble() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
        double tag = 1;
        SimpleDoubleData tt = createSimpleDoubleData();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Simple Double Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        SimpleDoubleData tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Simple Double Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(2,nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Simple Double Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Simple Double Test {put(T t,U u)/get(T t)} case5] [OK]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      double tag = 1;
      SimpleDoubleData tt = createSimpleDoubleData();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(1);
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Simple Double Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      if(map->size() != 1) {
        printf("---[HashMap Simple Double Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(1);
      if(map->size() != 0) {
        printf("---[HashMap Simple Double Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Double Test {remove(T t)} case4] [OK]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      double tag = 1;
      SimpleDoubleData tt = createSimpleDoubleData();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Simple Double Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(1);
      if(!map->isEmpty()) {
        printf("---[HashMap Simple Double Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Double Test {isEmpty()} case3] [OK]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      double tag = 1;
      SimpleDoubleData tt = createSimpleDoubleData();
      tt->i = 100;
      map->put(tag,tt);
      map->put(2,tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Simple Double Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<double,SimpleDoubleData> map2 = createHashMap<double,SimpleDoubleData>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Simple Double Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Double Test {clear()} case3] [OK]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      double tag = 1;
      SimpleDoubleData tt = createSimpleDoubleData();
      tt->i = 100;
      map->put(tag,tt);
      map->put(2,tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Simple Double Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Double Test {size()} case1] [OK]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      for(int index = 0;index < 100;index++) {
        SimpleDoubleData tt = createSimpleDoubleData();
        tt->i = index;
        map->put(index,tt);
      }

      ArrayList<double> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Simple Double Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        double key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Simple Double Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<double,SimpleDoubleData> map2 = createHashMap<double,SimpleDoubleData>();
      ArrayList<double>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Simple Double Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Simple Double Test {keySet()} case4] [OK]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      for(int index = 0;index < 100;index++) {
        SimpleDoubleData tt = createSimpleDoubleData();
        tt->i = index;
        map->put(index,tt);
      }

      ArrayList<SimpleDoubleData> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        SimpleDoubleData key1 = keys->get(index);
        if(map->get(key1->i) == nullptr) {
          printf("---[HashMap Simple Double Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<double,SimpleDoubleData> map2 = createHashMap<double,SimpleDoubleData>();
      ArrayList<SimpleDoubleData>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Simple Double Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Simple Double Test {entrySet()} case3] [OK]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<double,SimpleDoubleData> map = createHashMap<double,SimpleDoubleData>();
      for(int index = 0;index < 100;index++) {
        SimpleDoubleData tt = createSimpleDoubleData();
        tt->i = index;
        map->put(index,tt);
      }

      int index = 0;
      MapIterator<double,SimpleDoubleData> iterator = map->getIterator();
      while(iterator->hasValue()) {
          double key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Double Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          SimpleDoubleData t1 = iterator->getValue();
          if(t1->i != key) {
            printf("---[MapIterator Double Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Double Test {getKey/getValue()} case3] [OK]--- \n");
      break;

    }


}
