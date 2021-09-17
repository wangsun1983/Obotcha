#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Long.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(HashmapDataLong) {
public:
  HashMap<Long,Long> maps;
  DECLARE_REFLECT_FIELD(HashmapDataLong,maps)
};

void testHashMapLongLong() {
    while(1) {
      HashMap<Long,Long> maps = createHashMap<Long,Long>();
      maps->put(createLong(1),createLong(10));
      maps->put(createLong(2),createLong(20));
      maps->put(createLong(3),createLong(30));
      JsonWriter writer = createJsonWriter("./tmp/hashmap_Long_Long_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(maps);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_Long_Long_test1.json"));
      JsonValue value2 = reader->get();

      HashMap<Long,Long> maps2 = createHashMap<Long,Long>();
      value2->reflectTo(maps2);
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Long Long Test case1] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createLong(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Long Long Test case2] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createLong(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Long Long Test case3] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createLong(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Long Long Test case4] [FAILED]--- \n");
        break;
      }

      break;
    }

    while(1) {
      HashmapDataLong data = createHashmapDataLong();
      HashMap<Long,Long> maps = createHashMap<Long,Long>();
      maps->put(createLong(1),createLong(10));
      maps->put(createLong(2),createLong(20));
      maps->put(createLong(3),createLong(30));
      data->maps = maps;

      JsonWriter writer = createJsonWriter("./tmp/hashmap_Long_Long_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_Long_Long_test2.json"));
      JsonValue value2 = reader->get();

      HashmapDataLong data2 = createHashmapDataLong();
      value2->reflectTo(data2);
      HashMap<Long,Long> maps2 = data2->maps;
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Long Long Test case5] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createLong(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Long Long Test case6] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createLong(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Long Long Test case7] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createLong(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Long Long Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect HashMap Long Long Test case100] [OK]--- \n");
}
