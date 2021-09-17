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

DECLARE_CLASS(ListMapItem) {
public:
    int data1;
    long data2;
    DECLARE_REFLECT_FIELD(ListMapItem,data1,data2)
};

DECLARE_CLASS(ListMapData) {
public:
  ArrayList<HashMap<Integer,ListMapItem>> list;
  DECLARE_REFLECT_FIELD(ListMapData,list)
};

void testArrayListMap() {
    while(1) {
      ArrayList<HashMap<Integer,ListMapItem>> list = createArrayList<HashMap<Integer,ListMapItem>>();
      HashMap<Integer,ListMapItem> item1 = createHashMap<Integer,ListMapItem>();
      ListMapItem d1 = createListMapItem();
      d1->data1 = 1;
      d1->data2 = 2;

      ListMapItem d2 = createListMapItem();
      d2->data1 = 3;
      d2->data2 = 4;

      ListMapItem d3 = createListMapItem();
      d3->data1 = 5;
      d3->data2 = 6;

      item1->put(createInteger(0),d1);
      item1->put(createInteger(1),d2);
      item1->put(createInteger(2),d3);
      list->add(item1);

      HashMap<Integer,ListMapItem> item2 = createHashMap<Integer,ListMapItem>();
      ListMapItem d2_1 = createListMapItem();
      d2_1->data1 = 11;
      d2_1->data2 = 21;

      ListMapItem d2_2 = createListMapItem();
      d2_2->data1 = 31;
      d2_2->data2 = 41;

      ListMapItem d2_3 = createListMapItem();
      d2_3->data1 = 51;
      d2_3->data2 = 61;

      item2->put(createInteger(0),d2_1);
      item2->put(createInteger(1),d2_2);
      item2->put(createInteger(2),d2_3);
      list->add(item2);

      JsonWriter writer = createJsonWriter("./tmp/list_map_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(list);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_map_test1.json"));
      JsonValue value2 = reader->get();

      ArrayList<HashMap<Integer,ListMapItem>> list2 = createArrayList<HashMap<Integer,ListMapItem>>();
      value2->reflectTo(list2);

      if(list2->size() != 2) {
        printf("---[JsonReflect ArrayList Map Test case1] [FAILED]--- \n");
        break;
      }

      auto ll1 = list2->get(0);
      if(ll1->size() != 3) {
        printf("---[JsonReflect ArrayList Map Test case2] [FAILED]--- \n");
        break;
      }

      if(ll1->get(createInteger(0))->data1 != 1 ||ll1->get(createInteger(0))->data2 != 2) {
        printf("---[JsonReflect ArrayList Map Test case3] [FAILED]--- \n");
        break;
      }

      if(ll1->get(createInteger(1))->data1 != 3 ||ll1->get(createInteger(1))->data2 != 4) {
        printf("---[JsonReflect ArrayList Map Test case3] [FAILED]--- \n");
        break;
      }

      if(ll1->get(createInteger(2))->data1 != 5 ||ll1->get(createInteger(2))->data2 != 6) {
        printf("---[JsonReflect ArrayList Map Test case4] [FAILED]--- \n");
        break;
      }

      auto ll2 = list2->get(1);
      if(ll2->size() != 3) {
        printf("---[JsonReflect ArrayList Map Test case5] [FAILED]--- \n");
        break;
      }

      if(ll2->get(createInteger(0))->data1 != 11 ||ll2->get(createInteger(0))->data2 != 21) {
        printf("---[JsonReflect ArrayList Map Test case6] [FAILED]--- \n");
        break;
      }

      if(ll2->get(createInteger(1))->data1 != 31 ||ll2->get(createInteger(1))->data2 != 41) {
        printf("---[JsonReflect ArrayList Map Test case7] [FAILED]--- \n");
        break;
      }

      if(ll2->get(createInteger(2))->data1 != 51 ||ll2->get(createInteger(2))->data2 != 61) {
        printf("---[JsonReflect ArrayList Map Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    while(1) {
      ListMapData data = createListMapData();
      ArrayList<HashMap<Integer,ListMapItem>> list = createArrayList<HashMap<Integer,ListMapItem>>();
      HashMap<Integer,ListMapItem> item1 = createHashMap<Integer,ListMapItem>();
      ListMapItem d1 = createListMapItem();
      d1->data1 = 1;
      d1->data2 = 2;

      ListMapItem d2 = createListMapItem();
      d2->data1 = 3;
      d2->data2 = 4;

      ListMapItem d3 = createListMapItem();
      d3->data1 = 5;
      d3->data2 = 6;

      item1->put(createInteger(0),d1);
      item1->put(createInteger(1),d2);
      item1->put(createInteger(2),d3);
      list->add(item1);

      HashMap<Integer,ListMapItem> item2 = createHashMap<Integer,ListMapItem>();
      ListMapItem d2_1 = createListMapItem();
      d2_1->data1 = 11;
      d2_1->data2 = 21;

      ListMapItem d2_2 = createListMapItem();
      d2_2->data1 = 31;
      d2_2->data2 = 41;

      ListMapItem d2_3 = createListMapItem();
      d2_3->data1 = 51;
      d2_3->data2 = 61;

      item2->put(createInteger(0),d2_1);
      item2->put(createInteger(1),d2_2);
      item2->put(createInteger(2),d2_3);
      list->add(item2);
      data->list = list;

      JsonWriter writer = createJsonWriter("./tmp/list_map_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/list_map_test2.json"));
      JsonValue value2 = reader->get();

      ListMapData data2 = createListMapData();
      value2->reflectTo(data2);
      ArrayList<HashMap<Integer,ListMapItem>> list2 = data->list;

      if(list2->size() != 2) {
        printf("---[JsonReflect ArrayList Map Test case9] [FAILED]--- \n");
        break;
      }

      auto ll1 = list2->get(0);
      if(ll1->size() != 3) {
        printf("---[JsonReflect ArrayList Map Test case10] [FAILED]--- \n");
        break;
      }

      if(ll1->get(createInteger(0))->data1 != 1 ||ll1->get(createInteger(0))->data2 != 2) {
        printf("---[JsonReflect ArrayList Map Test case11] [FAILED]--- \n");
        break;
      }

      if(ll1->get(createInteger(1))->data1 != 3 ||ll1->get(createInteger(1))->data2 != 4) {
        printf("---[JsonReflect ArrayList Map Test case12] [FAILED]--- \n");
        break;
      }

      if(ll1->get(createInteger(2))->data1 != 5 ||ll1->get(createInteger(2))->data2 != 6) {
        printf("---[JsonReflect ArrayList Map Test case13] [FAILED]--- \n");
        break;
      }

      auto ll2 = list2->get(1);
      if(ll2->size() != 3) {
        printf("---[JsonReflect ArrayList Map Test case14] [FAILED]--- \n");
        break;
      }

      if(ll2->get(createInteger(0))->data1 != 11 ||ll2->get(createInteger(0))->data2 != 21) {
        printf("---[JsonReflect ArrayList Map Test case15] [FAILED]--- \n");
        break;
      }

      if(ll2->get(createInteger(1))->data1 != 31 ||ll2->get(createInteger(1))->data2 != 41) {
        printf("---[JsonReflect ArrayList Map Test case16] [FAILED]--- \n");
        break;
      }

      if(ll2->get(createInteger(2))->data1 != 51 ||ll2->get(createInteger(2))->data2 != 61) {
        printf("---[JsonReflect ArrayList Map Test case17] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect ArrayList Map Test case100] [OK]--- \n");
}
