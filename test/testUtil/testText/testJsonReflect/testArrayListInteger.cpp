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
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(IntegerList) {
public:
    ArrayList<Integer>lists;
    DECLARE_REFLECT_FIELD(IntegerList,lists)
};

DECLARE_CLASS(IntegerList2) {
public:
    ArrayList<Integer>list1;
    ArrayList<Integer>list2;
    DECLARE_REFLECT_FIELD(IntegerList2,list1,list2)
};

void testArrayListInteger() {
    while(1) {
      ArrayList<Integer> list = createArrayList<Integer>();
      list->add(createInteger(1));
      list->add(createInteger(2));
      list->add(createInteger(3));
      list->add(createInteger(4));
      list->add(createInteger(5));

      JsonWriter writer = createJsonWriter("./tmp/list_Integer_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_Integer_test1.json"));
      JsonValue value2 = reader->get();

      ArrayList<Integer> list2 = createArrayList<Integer>();
      value2->reflectTo(list2);

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList Integer Test case1] [FAILED]--- \n");
        break;
      }

      if(list2->get(0)->toValue() != 1
        ||list2->get(1)->toValue() != 2
        ||list2->get(2)->toValue() != 3
        ||list2->get(3)->toValue() != 4
        ||list2->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Integer Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      IntegerList2 list = createIntegerList2();
      list->list1 = createArrayList<Integer>();
      list->list2 = createArrayList<Integer>();

      list->list1->add(createInteger(1));
      list->list1->add(createInteger(2));
      list->list1->add(createInteger(3));
      list->list1->add(createInteger(4));
      list->list1->add(createInteger(5));

      list->list2->add(createInteger(6));
      list->list2->add(createInteger(7));
      list->list2->add(createInteger(8));
      list->list2->add(createInteger(9));
      list->list2->add(createInteger(10));

      JsonWriter writer = createJsonWriter("./tmp/list_Integer_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_Integer_test2.json"));
      JsonValue value2 = reader->get();

      IntegerList2 list2 = createIntegerList2();
      value2->reflectTo(list2);

      if(list2->list1->get(0)->toValue() != 1
        ||list2->list1->get(1)->toValue() != 2
        ||list2->list1->get(2)->toValue() != 3
        ||list2->list1->get(3)->toValue() != 4
        ||list2->list1->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Integer Test case3] [FAILED]--- \n");
          break;
      }

      if(list2->list2->get(0)->toValue() != 6
        ||list2->list2->get(1)->toValue() != 7
        ||list2->list2->get(2)->toValue() != 8
        ||list2->list2->get(3)->toValue() != 9
        ||list2->list2->get(4)->toValue() != 10) {
          printf("---[JsonReflect ArrayList Integer Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect ArrayList Integer Test case100] [OK]--- \n");
}
