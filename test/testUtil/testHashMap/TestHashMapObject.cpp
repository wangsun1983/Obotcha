#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"


using namespace obotcha;

DECLARE_CLASS(MyKey) {
public:
  int i;
  _MyKey(int v) {
    i = v;
  }

  int toValue() {
    return i;
  }

  bool equals(MyKey s) {
    return s->i == i;
  }

  bool equals(_MyKey *s) {
    return s->i == i;
  }

  uint64_t hashcode() {
    return i;
  }
};

DECLARE_CLASS(MyValue) {
public:
  int i;

};

void testHashMapObject() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
        MyKey tag = createMyKey(1);
        MyValue tt = createMyValue();
        tt->i = 100;
        map->put(tag,tt);
        if(map->size() != 1) {
            printf("---[HashMap MyKey Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }

        MyValue tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap MyKey Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put(createMyKey(2),nullptr);
        if(map->size() != 2) {
          printf("---[HashMap MyKey Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        MyValue MyValue = map->get(nullptr);
        if(MyValue != nullptr) {
          printf("---[HashMap MyKey Test {put(T t,U u)/get(T t)} case4] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap MyKey Test {put(T t,U u)/get(T t)} case5] [Success]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      MyKey tag = createMyKey(1);
      MyValue tt = createMyValue();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove(createMyKey(1));
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap MyKey Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      map->remove(nullptr);
      if(map->size() != 1) {
        printf("---[HashMap MyKey Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove(createMyKey(1));
      if(map->size() != 0) {
        printf("---[HashMap MyKey Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap MyKey Test {remove(T t)} case4] [Success]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      MyKey tag = createMyKey(1);
      MyValue tt = createMyValue();
      tt->i = 100;
      map->put(tag,tt);

      if(map->isEmpty()) {
        printf("---[HashMap MyKey Test {isEmpty()} case1] [FAILED]--- \n");
        break;
      }

      map->remove(createMyKey(1));
      if(!map->isEmpty()) {
        printf("---[HashMap MyKey Test {isEmpty()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap MyKey Test {isEmpty()} case3] [Success]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      MyKey tag = createMyKey(1);
      MyValue tt = createMyValue();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createMyKey(2),tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap MyKey Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<MyKey,MyValue> map2 = createHashMap<MyKey,MyValue>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap MyKey Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap MyKey Test {clear()} case3] [Success]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      MyKey tag = createMyKey(1);
      MyValue tt = createMyValue();
      tt->i = 100;
      map->put(tag,tt);
      map->put(createMyKey(2),tt);
      if(map->size() != 2 ) {
        printf("---[HashMap MyKey Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap MyKey Test {size()} case1] [Success]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      for(int index = 0;index < 100;index++) {
        MyValue tt = createMyValue();
        tt->i = index;
        map->put(createMyKey(index),tt);
      }

      ArrayList<MyKey> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap MyKey Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        MyKey key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toValue(),index);
          printf("---[HashMap MyKey Test {keySet()} case2] [FAILED]--- \n");
          break;
        }
      }

      HashMap<MyKey,MyValue> map2 = createHashMap<MyKey,MyValue>();
      ArrayList<MyKey>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap MyKey Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap MyKey Test {keySet()} case4] [Success]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      for(int index = 0;index < 100;index++) {
        MyValue tt = createMyValue();
        MyKey kk = createMyKey(index);
        tt->i = index;
        map->put(kk,tt);
      }

      ArrayList<MyKey> keys = map->keySet();
      int size = keys->size();

      for(int index = 0;index < size;index++) {
        MyKey key1 = keys->get(index);
        MyValue v1 = map->get(createMyKey(key1->i));
        if(v1 == nullptr) {
          printf("---[HashMap MyKey Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<MyKey,MyValue> map2 = createHashMap<MyKey,MyValue>();
      ArrayList<MyValue>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap MyKey Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap MyKey Test {entrySet()} case3] [Success]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<MyKey,MyValue> map = createHashMap<MyKey,MyValue>();
      for(int index = 0;index < 100;index++) {
        MyValue tt = createMyValue();
        tt->i = index;
        map->put(createMyKey(index),tt);
      }

      int index = 0;
      MapIterator<MyKey,MyValue> iterator = map->getIterator();
      while(iterator->hasValue()) {
          MyKey key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator MyKey Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          MyValue t1 = iterator->getValue();
          if(t1->i != key->toValue()) {
            printf("---[MapIterator MyKey Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator MyKey Test {getKey/getValue()} case3] [Success]--- \n");
      break;

    }


}
