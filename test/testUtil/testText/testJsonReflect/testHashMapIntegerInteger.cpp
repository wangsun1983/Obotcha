#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(HashmapDataInteger) {
public:
  HashMap<Integer,Integer> maps;
  DECLARE_REFLECT_FIELD(HashmapDataInteger,maps)
};

void testHashMapIntegerInteger() {
    while(1) {
      HashMap<Integer,Integer> maps = createHashMap<Integer,Integer>();
      maps->put(createInteger(1),createInteger(10));
      maps->put(createInteger(2),createInteger(20));
      maps->put(createInteger(3),createInteger(30));
      JsonWriter writer = createJsonWriter("./tmp/hashmap_integer_integer_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(maps);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_integer_integer_test1.json"));
      JsonValue value2 = reader->get();

      HashMap<Integer,Integer> maps2 = createHashMap<Integer,Integer>();
      value2->reflectTo(maps2);
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Integer Integer Test case1] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createInteger(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Integer Integer Test case2] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createInteger(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Integer Integer Test case3] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createInteger(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Integer Integer Test case4] [FAILED]--- \n");
        break;
      }

      break;
    }

    while(1) {
      HashmapDataInteger data = createHashmapDataInteger();
      HashMap<Integer,Integer> maps = createHashMap<Integer,Integer>();
      maps->put(createInteger(1),createInteger(10));
      maps->put(createInteger(2),createInteger(20));
      maps->put(createInteger(3),createInteger(30));
      data->maps = maps;

      JsonWriter writer = createJsonWriter("./tmp/hashmap_integer_integer_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_integer_integer_test2.json"));
      JsonValue value2 = reader->get();

      HashmapDataInteger data2 = createHashmapDataInteger();
      value2->reflectTo(data2);
      HashMap<Integer,Integer> maps2 = data2->maps;
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Integer Integer Test case5] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createInteger(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Integer Integer Test case6] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createInteger(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Integer Integer Test case7] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createInteger(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Integer Integer Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect HashMap Integer Integer Test case100] [OK]--- \n");
}
