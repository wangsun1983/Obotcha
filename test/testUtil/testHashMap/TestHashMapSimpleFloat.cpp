#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Float.hpp"
#include "Float.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(SimpleFloatData) {
public:
  float i;
};

void testHashMapSimpleFloat() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
        float tag = 1;
        SimpleFloatData tt = createSimpleFloatData();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Simple Float Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        SimpleFloatData tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Simple Float Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(2,nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Simple Float Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Simple Float Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      float tag = 1;
      SimpleFloatData tt = createSimpleFloatData();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(1);
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Simple Float Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      if(map->size() != 1) {
        printf("---[HashMap Simple Float Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(1);
      if(map->size() != 0) {
        printf("---[HashMap Simple Float Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Float Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      float tag = 1;
      SimpleFloatData tt = createSimpleFloatData();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Simple Float Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(1);
      if(!map->isEmpty()) {
        printf("---[HashMap Simple Float Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Float Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      float tag = 1;
      SimpleFloatData tt = createSimpleFloatData();
      tt->i = 100;
      map->put(tag,tt);
      map->put(2,tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Simple Float Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<float,SimpleFloatData> map2 = createHashMap<float,SimpleFloatData>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Simple Float Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Float Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      float tag = 1;
      SimpleFloatData tt = createSimpleFloatData();
      tt->i = 100;
      map->put(tag,tt);
      map->put(2,tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Simple Float Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Float Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      for(int index = 0;index < 100;index++) {
        SimpleFloatData tt = createSimpleFloatData();
        tt->i = index;
        map->put(index,tt);
      }

      ArrayList<float> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Simple Float Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        float key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Simple Float Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<float,SimpleFloatData> map2 = createHashMap<float,SimpleFloatData>();
      ArrayList<float>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Simple Float Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Simple Float Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      for(int index = 0;index < 100;index++) {
        SimpleFloatData tt = createSimpleFloatData();
        tt->i = index;
        map->put(index,tt);
      }

      ArrayList<SimpleFloatData> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        SimpleFloatData key1 = keys->get(index);
        if(map->get(key1->i) == nullptr) {
          printf("---[HashMap Simple Float Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<float,SimpleFloatData> map2 = createHashMap<float,SimpleFloatData>();
      ArrayList<SimpleFloatData>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Simple Float Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Simple Float Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<float,SimpleFloatData> map = createHashMap<float,SimpleFloatData>();
      for(int index = 0;index < 100;index++) {
        SimpleFloatData tt = createSimpleFloatData();
        tt->i = index;
        map->put(index,tt);
      }

      int index = 0;
      MapIterator<float,SimpleFloatData> iterator = map->getIterator();
      while(iterator->hasValue()) {
          float key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Simple Float Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          SimpleFloatData t1 = iterator->getValue();
          if(t1->i != key) {
            printf("---[MapIterator Simple Float Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Simple Float Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }


}
