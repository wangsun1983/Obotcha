#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TT1) {
public:
  int i;
};

void testHashMapString() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<String,TT1> map = createHashMap<String,TT1>();
        String tag = createString("tag1");
        TT1 tt = createTT1();
        tt->i = 100;
        map->put(tag,tt);

        if(map->size() != 1) {
            printf("---[HashMap String Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }
        TT1 tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap String Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put("tag2",nullptr);
        if(map->size() != 2) {
          printf("---[HashMap String Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }
        TT1 tt3 = map->get(nullptr);
        if(tt3 != nullptr) {
          printf("---[HashMap String Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap String Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      String tag = createString("tag1");
      TT1 tt = createTT1();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createString("tag1"));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap String Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap String Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove("tag2");
      if(map->size() != 1) {
        printf("---[HashMap String Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      String tag = createString("tag1");
      TT1 tt = createTT1();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap String Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove("tag1");
      if(!map->isEmpty()) {
        printf("---[HashMap String Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      String tag = createString("tag1");
      TT1 tt = createTT1();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createString("tag2"),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap String Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<String,TT1> map2 = createHashMap<String,TT1>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap String Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      String tag = createString("tag1");
      TT1 tt = createTT1();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createString("tag2"),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap String Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      for(int index = 0;index < 100;index++) {
        TT1 tt = createTT1();
        tt->i = index;
        //printf("put index is %d \n",index);
        map->put(createString(index),tt);
      }

      ArrayList<String> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap String Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        String key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toBasicInt(),index);
          printf("---[HashMap String Test {keySet(),index is %d} case2] [FAILED]--- \n",index);
          break;
        }
      }

      HashMap<String,TT1> map2 = createHashMap<String,TT1>();
      ArrayList<String>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap String Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap String Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      for(int index = 0;index < 100;index++) {
        TT1 tt = createTT1();
        tt->i = index;
        map->put(createString(index),tt);
      }

      ArrayList<TT1> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        TT1 key1 = keys->get(index);
        if(map->get(createString(key1->i)) == nullptr) {
          printf("---[HashMap String Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<String,TT1> map2 = createHashMap<String,TT1>();
      ArrayList<TT1>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap String Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap String Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<String,TT1> map = createHashMap<String,TT1>();
      for(int index = 0;index < 100;index++) {
        TT1 tt = createTT1();
        tt->i = index;
        map->put(createString(index),tt);
      }

      int index = 0;
      MapIterator<String,TT1> iterator = map->getIterator();
      while(iterator->hasValue()) {
          String key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator String Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          TT1 t1 = iterator->getValue();
          if(t1->i != key->toBasicInt()) {
            printf("---[MapIterator String Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator String Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }

}
