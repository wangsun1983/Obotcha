#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Uint32.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(Uint32List) {
public:
    ArrayList<Uint32>lists;
    DECLARE_REFLECT_FIELD(Uint32List,lists)
};

DECLARE_CLASS(Uint32List2) {
public:
    ArrayList<Uint32>list1;
    ArrayList<Uint32>list2;
    DECLARE_REFLECT_FIELD(Uint32List2,list1,list2)
};

void testArrayListUint32() {
    while(1) {
      ArrayList<Uint32> list = createArrayList<Uint32>();
      list->add(createUint32(1));
      list->add(createUint32(2));
      list->add(createUint32(3));
      list->add(createUint32(4));
      list->add(createUint32(5));

      JsonWriter writer = createJsonWriter("./tmp/list_Uint32_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_Uint32_test1.json"));
      JsonValue value2 = reader->get();

      ArrayList<Uint32> list2 = createArrayList<Uint32>();
      value2->reflectTo(list2);

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList Uint32 Test case1] [FAILED]--- \n");
        break;
      }

      if(list2->get(0)->toValue() != 1
        ||list2->get(1)->toValue() != 2
        ||list2->get(2)->toValue() != 3
        ||list2->get(3)->toValue() != 4
        ||list2->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Uint32 Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      Uint32List2 list = createUint32List2();
      list->list1 = createArrayList<Uint32>();
      list->list2 = createArrayList<Uint32>();

      list->list1->add(createUint32(1));
      list->list1->add(createUint32(2));
      list->list1->add(createUint32(3));
      list->list1->add(createUint32(4));
      list->list1->add(createUint32(5));

      list->list2->add(createUint32(6));
      list->list2->add(createUint32(7));
      list->list2->add(createUint32(8));
      list->list2->add(createUint32(9));
      list->list2->add(createUint32(10));

      JsonWriter writer = createJsonWriter("./tmp/list_Uint32_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_Uint32_test2.json"));
      JsonValue value2 = reader->get();

      Uint32List2 list2 = createUint32List2();
      value2->reflectTo(list2);

      if(list2->list1->get(0)->toValue() != 1
        ||list2->list1->get(1)->toValue() != 2
        ||list2->list1->get(2)->toValue() != 3
        ||list2->list1->get(3)->toValue() != 4
        ||list2->list1->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Uint32 Test case3] [FAILED]--- \n");
          break;
      }

      if(list2->list2->get(0)->toValue() != 6
        ||list2->list2->get(1)->toValue() != 7
        ||list2->list2->get(2)->toValue() != 8
        ||list2->list2->get(3)->toValue() != 9
        ||list2->list2->get(4)->toValue() != 10) {
          printf("---[JsonReflect ArrayList Uint32 Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect ArrayList Uint32 Test case100] [OK]--- \n");
}
