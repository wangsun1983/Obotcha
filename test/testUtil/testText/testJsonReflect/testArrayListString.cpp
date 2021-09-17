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

DECLARE_CLASS(StringStringList) {
public:
    ArrayList<String>lists;
    DECLARE_REFLECT_FIELD(StringStringList,lists)
};

DECLARE_CLASS(StringStringList2) {
public:
    ArrayList<String>lists1;
    ArrayList<String>lists2;
    DECLARE_REFLECT_FIELD(StringStringList2,lists1,lists2)
};

void testArrayListString() {
    while(1) {
      ArrayList<String> list = createArrayList<String>();
      list->add(S("val1"));
      list->add(S("val2"));
      list->add(S("val3"));
      list->add(S("val4"));
      list->add(S("val5"));

      JsonWriter writer = createJsonWriter("./tmp/list_string_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_string_test1.json"));
      JsonValue value2 = reader->get();

      ArrayList<String> list2 = createArrayList<String>();
      value2->reflectTo(list2);

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList String Test case1] [FAILED]--- \n");
        break;
      }

      if(!list2->get(0)->equals("val1")
        ||!list2->get(1)->equals("val2")
        ||!list2->get(2)->equals("val3")
        ||!list2->get(3)->equals("val4")
        ||!list2->get(4)->equals("val5")) {
          printf("---[JsonReflect ArrayList String Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      StringStringList ll = createStringStringList();
      ArrayList<String> list = createArrayList<String>();
      list->add(S("val1"));
      list->add(S("val2"));
      list->add(S("val3"));
      list->add(S("val4"));
      list->add(S("val5"));
      ll->lists = list;

      JsonWriter writer = createJsonWriter("./tmp/list_string_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(ll);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_string_test2.json"));
      JsonValue value2 = reader->get();

      //ArrayList<String> list2 = createArrayList<String>();
      StringStringList ll2 = createStringStringList();
      value2->reflectTo(ll2);

      auto list2 = ll2->lists;

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList String Test case3] [FAILED]--- \n");
        break;
      }

      if(!list2->get(0)->equals("val1")
        ||!list2->get(1)->equals("val2")
        ||!list2->get(2)->equals("val3")
        ||!list2->get(3)->equals("val4")
        ||!list2->get(4)->equals("val5")) {
          printf("---[JsonReflect ArrayList String Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect ArrayList String Test case100] [OK]--- \n");
}
