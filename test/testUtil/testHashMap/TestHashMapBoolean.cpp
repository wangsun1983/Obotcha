#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Boolean.hpp"
#include "Boolean.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TT6) {
public:
  bool i;
};

void testHashMapBoolean() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
        Boolean tag = createBoolean(true);
        TT6 tt = createTT6();
        tt->i = true;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Boolean Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        TT6 tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != true) {
          printf("---[HashMap Boolean Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(createBoolean(false),nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Boolean Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        TT6 TT6 = map->get(nullptr);
        if(TT6 != nullptr) {
          printf("---[HashMap Boolean Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Boolean Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      Boolean tag = createBoolean(true);
      TT6 tt = createTT6();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createBoolean(true));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Boolean Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap Boolean Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(createBoolean(true));
      if(map->size() != 0) {
        printf("---[HashMap Boolean Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Boolean Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      Boolean tag = createBoolean(true);
      TT6 tt = createTT6();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Boolean Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(createBoolean(true));
      if(!map->isEmpty()) {
        printf("---[HashMap Boolean Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Boolean Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      Boolean tag = createBoolean(true);
      TT6 tt = createTT6();
      tt->i = true;
      map->put(tag,tt);
      map->put(createBoolean(false),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Boolean Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<Boolean,TT6> map2 = createHashMap<Boolean,TT6>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Boolean Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Boolean Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      Boolean tag = createBoolean(true);
      TT6 tt = createTT6();
      tt->i = true;
      map->put(tag,tt);
      map->put(createBoolean(false),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Boolean Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Boolean Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      TT6 tt1 = createTT6();
      tt1->i = true;
      map->put(createBoolean(true),tt1);

      TT6 tt2 = createTT6();
      tt2->i = false;
      map->put(createBoolean(false),tt2);

      ArrayList<Boolean> keys = map->keySet();
      int size = keys->size();
      if(size != 2) {
        printf("---[HashMap Boolean Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < 2;index++) {
        Boolean key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Boolean Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Boolean,TT6> map2 = createHashMap<Boolean,TT6>();
      ArrayList<Boolean>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Boolean Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Boolean Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      TT6 tt1 = createTT6();
      tt1->i = true;
      map->put(createBoolean(true),tt1);

      TT6 tt2 = createTT6();
      tt2->i = false;
      map->put(createBoolean(false),tt2);

      ArrayList<TT6> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        TT6 key1 = keys->get(index);
        if(map->get(createBoolean(key1->i)) == nullptr) {
          printf("---[HashMap Boolean Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Boolean,TT6> map2 = createHashMap<Boolean,TT6>();
      ArrayList<TT6>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Boolean Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Boolean Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<Boolean,TT6> map = createHashMap<Boolean,TT6>();
      TT6 tt1 = createTT6();
      tt1->i = true;
      map->put(createBoolean(true),tt1);

      TT6 tt2 = createTT6();
      tt2->i = false;
      map->put(createBoolean(false),tt2);

      int index = 0;
      MapIterator<Boolean,TT6> iterator = map->getIterator();
      while(iterator->hasValue()) {
          Boolean key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Boolean Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          TT6 t1 = iterator->getValue();
          if(t1->i != key->toValue()) {
            printf("---[MapIterator Boolean Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Boolean Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }


}
