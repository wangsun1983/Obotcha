#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Long.hpp"
#include "Long.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TT4) {
public:
  long i;
};

void testHashMapLong() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<Long,TT4> map = createHashMap<Long,TT4>();
        Long tag = createLong(1);
        TT4 tt = createTT4();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Long Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        TT4 tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Long Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(createLong(2),nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Long Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        TT4 TT4 = map->get(nullptr);
        if(TT4 != nullptr) {
          printf("---[HashMap Long Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Long Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      Long tag = createLong(1);
      TT4 tt = createTT4();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createLong(1));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Long Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap Long Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(createLong(1));
      if(map->size() != 0) {
        printf("---[HashMap Long Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Long Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      Long tag = createLong(1);
      TT4 tt = createTT4();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Long Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(createLong(1));
      if(!map->isEmpty()) {
        printf("---[HashMap Long Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Long Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      Long tag = createLong(1);
      TT4 tt = createTT4();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createLong(2),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Long Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<Long,TT4> map2 = createHashMap<Long,TT4>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Long Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Long Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      Long tag = createLong(1);
      TT4 tt = createTT4();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createLong(2),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Long Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Long Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      for(int index = 0;index < 100;index++) {
        TT4 tt = createTT4();
        tt->i = index;
        map->put(createLong(index),tt);
      }

      ArrayList<Long> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Long Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        Long key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Long Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Long,TT4> map2 = createHashMap<Long,TT4>();
      ArrayList<Long>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Long Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Long Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      for(int index = 0;index < 100;index++) {
        TT4 tt = createTT4();
        tt->i = index;
        map->put(createLong(index),tt);
      }

      ArrayList<TT4> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        TT4 key1 = keys->get(index);
        if(map->get(createLong(key1->i)) == nullptr) {
          printf("---[HashMap Long Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Long,TT4> map2 = createHashMap<Long,TT4>();
      ArrayList<TT4>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Long Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Long Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<Long,TT4> map = createHashMap<Long,TT4>();
      for(int index = 0;index < 100;index++) {
        TT4 tt = createTT4();
        tt->i = index;
        map->put(createLong(index),tt);
      }

      int index = 0;
      MapIterator<Long,TT4> iterator = map->getIterator();
      while(iterator->hasValue()) {
          Long key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Long Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          TT4 t1 = iterator->getValue();
          if(t1->i != key->toValue()) {
            printf("---[MapIterator Long Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Long Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }


}
