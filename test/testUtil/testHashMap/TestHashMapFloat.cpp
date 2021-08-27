#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Float.hpp"
#include "Float.hpp"

using namespace obotcha;

DECLARE_CLASS(TT5) {
public:
  float i;
};

void testHashMapFloat() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<Float,TT5> map = createHashMap<Float,TT5>();
        Float tag = createFloat(1);
        TT5 tt = createTT5();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap Float Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        TT5 tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap Float Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(createFloat(2),nullptr);
        if(map->size() != 2) {
          printf("---[HashMap Float Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        TT5 TT5 = map->get(nullptr);
        if(TT5 != nullptr) {
          printf("---[HashMap Float Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap Float Test {put(T t,U u)/get(T t)} case5] [OK]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      Float tag = createFloat(1);
      TT5 tt = createTT5();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createFloat(1));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap Float Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap Float Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(createFloat(1));
      if(map->size() != 0) {
        printf("---[HashMap Float Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Float Test {remove(T t)} case4] [OK]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      Float tag = createFloat(1);
      TT5 tt = createTT5();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap Float Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(createFloat(1));
      if(!map->isEmpty()) {
        printf("---[HashMap Float Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Float Test {isEmpty()} case3] [OK]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      Float tag = createFloat(1);
      TT5 tt = createTT5();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createFloat(2),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap Float Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<Float,TT5> map2 = createHashMap<Float,TT5>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap Float Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Float Test {clear()} case3] [OK]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      Float tag = createFloat(1);
      TT5 tt = createTT5();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createFloat(2),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap Float Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap Float Test {size()} case1] [OK]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      for(int index = 0;index < 100;index++) {
        TT5 tt = createTT5();
        tt->i = index;
        map->put(createFloat(index),tt);
      }

      ArrayList<Float> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap Float Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        Float key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap Float Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Float,TT5> map2 = createHashMap<Float,TT5>();
      ArrayList<Float>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap Float Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Float Test {keySet()} case4] [OK]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      for(int index = 0;index < 100;index++) {
        TT5 tt = createTT5();
        tt->i = index;
        map->put(createFloat(index),tt);
      }

      ArrayList<TT5> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        TT5 key1 = keys->get(index);
        if(map->get(createFloat(key1->i)) == nullptr) {
          printf("---[HashMap Float Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<Float,TT5> map2 = createHashMap<Float,TT5>();
      ArrayList<TT5>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap Float Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap Float Test {entrySet()} case3] [OK]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<Float,TT5> map = createHashMap<Float,TT5>();
      for(int index = 0;index < 100;index++) {
        TT5 tt = createTT5();
        tt->i = index;
        map->put(createFloat(index),tt);
      }

      int index = 0;
      MapIterator<Float,TT5> iterator = map->getIterator();
      while(iterator->hasValue()) {
          Float key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator Float Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          TT5 t1 = iterator->getValue();
          if(t1->i != key->toValue()) {
            printf("---[MapIterator Float Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator Float Test {getKey/getValue()} case3] [OK]--- \n");
      break;

    }


}
