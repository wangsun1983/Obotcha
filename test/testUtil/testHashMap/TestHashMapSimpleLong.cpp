#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Long.hpp"
#include "Long.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(SimpleLongData) {
public:
  long i;
};

void testHashMapSimpleLong() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
        long tag = 1;
        SimpleLongData tt = createSimpleLongData();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Simple Long Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        SimpleLongData tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Simple Long Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(2,nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Simple Long Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Simple Long Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      long tag = 1;
      SimpleLongData tt = createSimpleLongData();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(1);
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Simple Long Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      if(map->size() != 1) {
        printf("---[HashMap Simple Long Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(1);
      if(map->size() != 0) {
        printf("---[HashMap Simple Long Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Long Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      long tag = 1;
      SimpleLongData tt = createSimpleLongData();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Simple Long Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(1);
      if(!map->isEmpty()) {
        printf("---[HashMap Simple Long Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Long Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      long tag = 1;
      SimpleLongData tt = createSimpleLongData();
      tt->i = 100;
      map->put(tag,tt);
      map->put(2,tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Simple Long Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<long,SimpleLongData> map2 = createHashMap<long,SimpleLongData>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Simple Long Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Long Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      long tag = 1;
      SimpleLongData tt = createSimpleLongData();
      tt->i = 100;
      map->put(tag,tt);
      map->put(2,tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Simple Long Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Simple Long Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      for(int index = 0;index < 100;index++) {
        SimpleLongData tt = createSimpleLongData();
        tt->i = index;
        map->put(index,tt);
      }

      ArrayList<long> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Simple Long Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        long key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Simple Long Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<long,SimpleLongData> map2 = createHashMap<long,SimpleLongData>();
      ArrayList<long>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Simple Long Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Simple Long Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      for(int index = 0;index < 100;index++) {
        SimpleLongData tt = createSimpleLongData();
        tt->i = index;
        map->put(index,tt);
      }

      ArrayList<SimpleLongData> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        SimpleLongData key1 = keys->get(index);
        if(map->get(key1->i) == nullptr) {
          printf("---[HashMap Simple Long Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<long,SimpleLongData> map2 = createHashMap<long,SimpleLongData>();
      ArrayList<SimpleLongData>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Simple Long Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Simple Long Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<long,SimpleLongData> map = createHashMap<long,SimpleLongData>();
      for(int index = 0;index < 100;index++) {
        SimpleLongData tt = createSimpleLongData();
        tt->i = index;
        map->put(index,tt);
      }

      int index = 0;
      MapIterator<long,SimpleLongData> iterator = map->getIterator();
      while(iterator->hasValue()) {
          long key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Simple Long Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          SimpleLongData t1 = iterator->getValue();
          if(t1->i != key) {
            printf("---[MapIterator Simple Long Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Simple Long Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }


}
