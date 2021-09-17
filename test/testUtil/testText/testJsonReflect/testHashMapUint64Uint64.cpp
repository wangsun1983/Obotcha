#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Uint64.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Uint64.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(HashmapDataUint64) {
public:
  HashMap<Uint64,Uint64> maps;
  DECLARE_REFLECT_FIELD(HashmapDataUint64,maps)
};

void testHashMapUint64Uint64() {
    while(1) {
      HashMap<Uint64,Uint64> maps = createHashMap<Uint64,Uint64>();
      maps->put(createUint64(1),createUint64(10));
      maps->put(createUint64(2),createUint64(20));
      maps->put(createUint64(3),createUint64(30));
      JsonWriter writer = createJsonWriter("./tmp/hashmap_Uint64_Uint64_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(maps);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_Uint64_Uint64_test1.json"));
      JsonValue value2 = reader->get();

      HashMap<Uint64,Uint64> maps2 = createHashMap<Uint64,Uint64>();
      value2->reflectTo(maps2);
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case1] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createUint64(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case2] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createUint64(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case3] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createUint64(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case4] [FAILED]--- \n");
        break;
      }

      break;
    }

    while(1) {
      HashmapDataUint64 data = createHashmapDataUint64();
      HashMap<Uint64,Uint64> maps = createHashMap<Uint64,Uint64>();
      maps->put(createUint64(1),createUint64(10));
      maps->put(createUint64(2),createUint64(20));
      maps->put(createUint64(3),createUint64(30));
      data->maps = maps;

      JsonWriter writer = createJsonWriter("./tmp/hashmap_Uint64_Uint64_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_Uint64_Uint64_test2.json"));
      JsonValue value2 = reader->get();

      HashmapDataUint64 data2 = createHashmapDataUint64();
      value2->reflectTo(data2);
      HashMap<Uint64,Uint64> maps2 = data2->maps;
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case5] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createUint64(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case6] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createUint64(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case7] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createUint64(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Uint64 Uint64 Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect HashMap Uint64 Uint64 Test case100] [OK]--- \n");
}
