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
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(ArrayItemUserdata) {
public:
    int data1;
    long data2;
    DECLARE_REFLECT_FIELD(ArrayItemUserdata,data1,data2)
};

DECLARE_CLASS(Userdatas) {
public:
    ArrayList<ArrayItemUserdata> item;
    DECLARE_REFLECT_FIELD(Userdatas,item)
};

void testArrayUserData() {
    while(1) {
      ArrayList<ArrayItemUserdata> list = createArrayList<ArrayItemUserdata>();
      ArrayItemUserdata d1 = createArrayItemUserdata();
      d1->data1 = 1;
      d1->data2 = 1;

      ArrayItemUserdata d2 = createArrayItemUserdata();
      d2->data1 = 2;
      d2->data2 = 2;

      ArrayItemUserdata d3 = createArrayItemUserdata();
      d3->data1 = 3;
      d3->data2 = 3;

      list->add(d1);
      list->add(d2);
      list->add(d3);

      JsonWriter writer = createJsonWriter("./tmp/list_userdata_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_userdata_test1.json"));
      JsonValue value2 = reader->get();

      ArrayList<ArrayItemUserdata> list2 = createArrayList<ArrayItemUserdata>();
      value2->reflectTo(list2);

      if(list2->size() != 3) {
        printf("---[JsonReflect ArrayList Userdata Test case1] [FAILED]--- \n");
        break;
      }

      if(list2->get(0)->data1 != 1 || list2->get(0)->data2 != 1) {
        printf("---[JsonReflect ArrayList Userdata Test case2] [FAILED]--- \n");
        break;
      }

      if(list2->get(1)->data1 != 2 || list2->get(1)->data2 != 2) {
        printf("---[JsonReflect ArrayList Userdata Test case3] [FAILED]--- \n");
        break;
      }

      if(list2->get(2)->data1 != 3 || list2->get(2)->data2 != 3) {
        printf("---[JsonReflect ArrayList Userdata Test case4] [FAILED]--- \n");
        break;
      }

      break;
    }

    while(1) {
      Userdatas data = createUserdatas();
      ArrayList<ArrayItemUserdata> list = createArrayList<ArrayItemUserdata>();
      ArrayItemUserdata d1 = createArrayItemUserdata();
      d1->data1 = 1;
      d1->data2 = 1;

      ArrayItemUserdata d2 = createArrayItemUserdata();
      d2->data1 = 2;
      d2->data2 = 2;

      ArrayItemUserdata d3 = createArrayItemUserdata();
      d3->data1 = 3;
      d3->data2 = 3;

      list->add(d1);
      list->add(d2);
      list->add(d3);
      data->item = list;

      JsonWriter writer = createJsonWriter("./tmp/list_userdata_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_userdata_test2.json"));
      JsonValue value2 = reader->get();

      Userdatas data2 = createUserdatas();
      value2->reflectTo(data2);

      ArrayList<ArrayItemUserdata> list2 = data2->item;

      if(list2->size() != 3) {
        printf("---[JsonReflect ArrayList Userdata Test case5] [FAILED]--- \n");
        break;
      }

      if(list2->get(0)->data1 != 1 || list2->get(0)->data2 != 1) {
        printf("---[JsonReflect ArrayList Userdata Test case6] [FAILED]--- \n");
        break;
      }

      if(list2->get(1)->data1 != 2 || list2->get(1)->data2 != 2) {
        printf("---[JsonReflect ArrayList Userdata Test case7] [FAILED]--- \n");
        break;
      }

      if(list2->get(2)->data1 != 3 || list2->get(2)->data2 != 3) {
        printf("---[JsonReflect ArrayList Userdata Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect ArrayList Userdata Test case100] [OK]--- \n");
}
