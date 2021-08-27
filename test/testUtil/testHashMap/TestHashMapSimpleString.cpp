#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_CLASS(SimpleStringData) {
public:
  int i;
};

void testHashMapSimpleString() {

    //void put(T t,U u)/get(T t)
    while(1) {
        HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
        std::string tag = "tag1";
        SimpleStringData tt = createSimpleStringData();
        tt->i = 100;
        map->put(tag,tt);

        if(map->size() != 1) {
            printf("---[HashMap String Test {put(T t,U u)/get(T t)} case1] [FAILED]--- \n");
            break;
        }
        SimpleStringData tt2 = map->get(tag);
        if(tt2 == nullptr || tt2->i != 100) {
          printf("---[HashMap String Test {put(T t,U u)/get(T t)} case2] [FAILED]--- \n");
          break;
        }

        map->put("tag2",nullptr);
        if(map->size() != 2) {
          printf("---[HashMap String Test {put(T t,U u)/get(T t)} case3] [FAILED]--- \n");
          break;
        }

        printf("---[HashMap String Test {put(T t,U u)/get(T t)} case5] [OK]--- \n");
        break;
    }

    //void remove(T t)
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      std::string tag = "tag1";
      SimpleStringData tt = createSimpleStringData();
      tt->i = 100;
      map->put(tag,tt);

      int size = map->size();
      map->remove("tag1");
      if(size != 1 && map->size() != 0) {
        printf("---[HashMap String Test {remove(T t)} case1] [FAILED]--- \n");
        break;
      }

      map->put(tag,tt);
      size = map->size();
      if(map->size() != 1) {
        printf("---[HashMap String Test {remove(T t)} case2] [FAILED]--- \n");
        break;
      }

      map->remove("tag2");
      if(map->size() != 1) {
        printf("---[HashMap String Test {remove(T t)} case3] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {remove(T t)} case4] [OK]--- \n");
      break;
    }

    //bool isEmpty()
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      std::string tag = "tag1";
      SimpleStringData tt = createSimpleStringData();
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

      printf("---[HashMap String Test {isEmpty()} case3] [OK]--- \n");
      break;
    }

    //void clear()
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      std::string tag = "tag1";
      SimpleStringData tt = createSimpleStringData();
      tt->i = 100;
      map->put(tag,tt);
      map->put("tag2",tt);

      int size = map->size();
      map->clear();
      if(size != 2 || map->size() != 0) {
        printf("---[HashMap String Test {clear()} case1] [FAILED]--- \n");
        break;
      }

      HashMap<std::string,SimpleStringData> map2 = createHashMap<std::string,SimpleStringData>();
      map2->clear();
      if(map2->size() != 0) {
        printf("---[HashMap String Test {clear()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {clear()} case3] [OK]--- \n");
      break;
    }

    //int size()
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      std::string tag = "tag1";
      SimpleStringData tt = createSimpleStringData();
      tt->i = 100;
      map->put(tag,tt);
      map->put("tag2",tt);
      if(map->size() != 2 ) {
        printf("---[HashMap String Test {size()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[HashMap String Test {size()} case1] [OK]--- \n");
      break;
    }

    //ArrayList<V> keySet()
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      for(int index = 0;index < 100;index++) {
        SimpleStringData tt = createSimpleStringData();
        tt->i = index;
        //printf("put index is %d \n",index);
        map->put(std::to_string(index),tt);
      }

      ArrayList<std::string> keys = map->keySet();
      int size = keys->size();
      if(size != 100) {
        printf("---[HashMap String Test {keySet()} case1] [FAILED]--- \n");
        break;
      }

      for(int index = 0;index < size;index++) {
        std::string key1 = keys->get(index);
        if(map->get(key1) == nullptr) {
          //printf("key1->int is %d,index is %d \n",key1->toBasicInt(),index);
          printf("---[HashMap String Test {keySet(),index is %d} case2] [FAILED]--- \n",index);
          break;
        }
      }

      HashMap<std::string,SimpleStringData> map2 = createHashMap<std::string,SimpleStringData>();
      ArrayList<std::string>keys2 = map2->keySet();
      if(keys2->size() != 0) {
          printf("---[HashMap String Test {keySet()} case3] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap String Test {keySet()} case4] [OK]--- \n");
      break;
    }

    //ArrayList<V> entrySet()
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      for(int index = 0;index < 100;index++) {
        SimpleStringData tt = createSimpleStringData();
        tt->i = index;
        map->put(std::to_string(index),tt);
      }

      ArrayList<SimpleStringData> keys = map->entrySet();
      int size = keys->size();
      for(int index = 0;index < size;index++) {
        SimpleStringData key1 = keys->get(index);
        if(map->get(std::to_string(key1->i)) == nullptr) {
          printf("---[HashMap String Test {entrySet()} case1] [FAILED]--- \n");
          break;
        }
      }

      HashMap<std::string,SimpleStringData> map2 = createHashMap<std::string,SimpleStringData>();
      ArrayList<SimpleStringData>values = map2->entrySet();
      if(values->size() != 0) {
          printf("---[HashMap String Test {entrySet()} case2] [FAILED]--- \n");
          break;
      }

      printf("---[HashMap String Test {entrySet()} case3] [OK]--- \n");
      break;
    }


    //_MapIterator(getKey/getValue)
    while(1) {
      HashMap<std::string,SimpleStringData> map = createHashMap<std::string,SimpleStringData>();
      for(int index = 0;index < 100;index++) {
        SimpleStringData tt = createSimpleStringData();
        tt->i = index;
        map->put(std::to_string(index),tt);
      }

      int index = 0;
      MapIterator<std::string,SimpleStringData> iterator = map->getIterator();
      while(iterator->hasValue()) {
          std::string key = iterator->getKey();
          if(map->get(key) == nullptr) {
            printf("---[MapIterator String Test {getKey/getValue()} case1] [FAILED]--- \n");
            break;
          }

          SimpleStringData t1 = iterator->getValue();
          if(t1->i != atoi(key.c_str())) {
            printf("---[MapIterator String Test {getKey/getValue()} case2] [FAILED]--- \n");
            break;
          }
          iterator->next();
          index++;
      }

      printf("---[MapIterator String Test {getKey/getValue()} case3] [OK]--- \n");
      break;

    }

}
