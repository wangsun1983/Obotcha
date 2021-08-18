#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"
#include "Integer.hpp"

using namespace obotcha;

DECLARE_CLASS(TT2) {
public:
  int i;
};

void testHashMapInteger() {
    //test null and 0
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      TT2 tt = createTT2();
      tt->i = 100;
      map->put(nullptr,tt);

      TT2 tt2 = createTT2();
      tt2->i = 1;
      map->put(createInteger(0),tt2);

      if(map->get(createInteger(0))->i != 1) {
        printf("---[HashMap Integer Test {null test} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Integer Test {null test} case2] [Success]--- \n");
      break;
    }

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
        Integer tag = createInteger(1);
        TT2 tt = createTT2();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Integer Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        TT2 tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Integer Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(createInteger(2),nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Integer Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        TT2 tt3 = map->get(nullptr);
        if(tt3 != nullptr) {
          printf("---[HashMap Integer Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Integer Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      Integer tag = createInteger(1);
      TT2 tt = createTT2();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createInteger(1));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Integer Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap Integer Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(createInteger(1));
      if(map->size() != 0) {
        printf("---[HashMap Integer Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Integer Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      Integer tag = createInteger(1);
      TT2 tt = createTT2();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Integer Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(createInteger(1));
      if(!map->isEmpty()) {
        printf("---[HashMap Integer Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Integer Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      Integer tag = createInteger(1);
      TT2 tt = createTT2();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createInteger(2),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Integer Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<Integer,TT2> map2 = createHashMap<Integer,TT2>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Integer Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Integer Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      Integer tag = createInteger(1);
      TT2 tt = createTT2();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createInteger(2),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Integer Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Integer Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      for(int index = 0;index < 100;index++) {
        TT2 tt = createTT2();
        tt->i = index;
        map->put(createInteger(index),tt);
      }

      ArrayList<Integer> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Integer Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        Integer key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Integer Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Integer,TT2> map2 = createHashMap<Integer,TT2>();
      ArrayList<Integer>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Integer Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Integer Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      for(int index = 0;index < 100;index++) {
        TT2 tt = createTT2();
        tt->i = index;
        map->put(createInteger(index),tt);
      }

      ArrayList<TT2> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        TT2 key1 = keys->get(index);
        if(map->get(createInteger(key1->i)) == nullptr) {
          printf("---[HashMap Integer Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Integer,TT2> map2 = createHashMap<Integer,TT2>();
      ArrayList<TT2>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Integer Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Integer Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<Integer,TT2> map = createHashMap<Integer,TT2>();
      for(int index = 0;index < 100;index++) {
        TT2 tt = createTT2();
        tt->i = index;
        map->put(createInteger(index),tt);
      }

      int index = 0;
      MapIterator<Integer,TT2> iterator = map->getIterator();
      while(iterator->hasValue()) {
          Integer key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Integer Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          TT2 t1 = iterator->getValue();
          if(t1->i != key->toValue()) {
            printf("---[MapIterator Integer Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Integer Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }

    while(1) {
      HashMap<Integer,String> map = createHashMap<Integer,String>();
      map->put(createInteger(1),createString("hello"));
      map->put(createInteger(1),createString("hello3"));
      String str = map->get(createInteger(1));
      if(str == nullptr) {
        printf("---[MapIterator Integer Test special equal case1] [FAIL]--- \n");
        break;
      }

      if(!str->equals("hello3")) {
        printf("---[MapIterator Integer Test special equal case2] [FAIL]--- \n");
        break;
      }

      printf("---[MapIterator Integer Test special equal case3] [OK]--- \n");
      break;
    }
}
