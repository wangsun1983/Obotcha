#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Double.hpp"
#include "Double.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TT3) {
public:
  double i;
};

void testHashMapDouble() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<Double,TT3> map = createHashMap<Double,TT3>();
        Double tag = createDouble(1);
        TT3 tt = createTT3();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Double Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        TT3 tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Double Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(createDouble(2),nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Double Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        TT3 tt3 = map->get(nullptr);
        if(tt3 != nullptr) {
          printf("---[HashMap Double Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Double Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      Double tag = createDouble(1);
      TT3 tt = createTT3();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createDouble(1));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Double Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap Double Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(createDouble(1));
      if(map->size() != 0) {
        printf("---[HashMap Double Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Double Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      Double tag = createDouble(1);
      TT3 tt = createTT3();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Double Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(createDouble(1));
      if(!map->isEmpty()) {
        printf("---[HashMap Double Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Double Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      Double tag = createDouble(1);
      TT3 tt = createTT3();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createDouble(2),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Double Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<Double,TT3> map2 = createHashMap<Double,TT3>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Double Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Double Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      Double tag = createDouble(1);
      TT3 tt = createTT3();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createDouble(2),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Double Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Double Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      for(int index = 0;index < 100;index++) {
        TT3 tt = createTT3();
        tt->i = index;
        map->put(createDouble(index),tt);
      }

      ArrayList<Double> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Double Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        Double key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Double Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Double,TT3> map2 = createHashMap<Double,TT3>();
      ArrayList<Double>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Double Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Double Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      for(int index = 0;index < 100;index++) {
        TT3 tt = createTT3();
        tt->i = index;
        map->put(createDouble(index),tt);
      }

      ArrayList<TT3> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        TT3 key1 = keys->get(index);
        if(map->get(createDouble(key1->i)) == nullptr) {
          printf("---[HashMap Double Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Double,TT3> map2 = createHashMap<Double,TT3>();
      ArrayList<TT3>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Double Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Double Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<Double,TT3> map = createHashMap<Double,TT3>();
      for(int index = 0;index < 100;index++) {
        TT3 tt = createTT3();
        tt->i = index;
        map->put(createDouble(index),tt);
      }

      int index = 0;
      MapIterator<Double,TT3> iterator = map->getIterator();
      while(iterator->hasValue()) {
          Double key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Double Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          TT3 t1 = iterator->getValue();
          if(t1->i != key->toValue()) {
            printf("---[MapIterator Double Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Double Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }


}
