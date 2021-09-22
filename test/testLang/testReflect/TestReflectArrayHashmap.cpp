#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <type_traits>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Reflect.hpp"
#include "String.hpp"
#include "Math.hpp"
#include "Field.hpp"
#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "HashMap.hpp"

using namespace obotcha;

DECLARE_CLASS(ItemData) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(ItemData,data1,data2)
};

DECLARE_CLASS(ArrayHashMap) {
public:
  ArrayList<HashMap<String,ItemData>> datas;
  DECLARE_REFLECT_FIELD(ArrayHashMap,datas)
};


void testReflectArrayHashmap() {
  while(1) {
    ArrayHashMap map = createArrayHashMap();
    map->datas = createArrayList<HashMap<String,ItemData>>();

    HashMap<String,ItemData> map1 = createHashMap<String,ItemData>();
    ItemData d1 = createItemData();
    d1->data1 = 1;
    d1->data2 = 2;

    ItemData d2 = createItemData();
    d2->data1 = 3;
    d2->data2 = 4;

    map1->put(createString("value1"),d1);
    map1->put(createString("value2"),d2);
    map->datas->add(map1);


    HashMap<String,ItemData> map2 = createHashMap<String,ItemData>();
    ItemData d3 = createItemData();
    d3->data1 = 5;
    d3->data2 = 6;

    ItemData d4 = createItemData();
    d4->data1 = 7;
    d4->data2 = 8;

    map2->put(createString("data1"),d3);
    map2->put(createString("data2"),d4);
    map->datas->add(map2);

    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(map);

    JsonWriter jwriter = createJsonWriter("output_array_hashmap_case1_1.json");
    jwriter->write(jvalue);


    JsonReader reader = createJsonReader(createFile("output_array_hashmap_case1_1.json"));
    JsonValue readValue = reader->get();
    ArrayHashMap result = createArrayHashMap();
    readValue->reflectTo(result);

    if(result->datas == nullptr || result->datas->size() != 2) {
      printf("Reflect Array HashMap test1-------[FAIL] \n");
      break;
    }

    HashMap<String,ItemData> m1 = result->datas->get(0);
    ItemData item1 = m1->get(createString("value1"));
    if(item1 == nullptr || item1->data1 != 1 || item1->data2 != 2) {
      printf("Reflect Array HashMap test2-------[FAIL] \n");
      break;
    }

    ItemData item2 = m1->get(createString("value2"));
    if(item2 == nullptr || item2->data1 != 3 || item2->data2 != 4) {
      printf("Reflect Array HashMap test3-------[FAIL] \n");
      break;
    }

    HashMap<String,ItemData> m2 = result->datas->get(1);
    ItemData item3 = m2->get(createString("data1"));
    if(item3 == nullptr || item3->data1 != 5 || item3->data2 != 6) {
      printf("Reflect Array HashMap test4-------[FAIL] \n");
      break;
    }

    ItemData item4 = m2->get(createString("data2"));
    if(item4 == nullptr || item4->data1 != 7 || item4->data2 != 8) {
      printf("Reflect Array HashMap test5-------[FAIL] \n");
      break;
    }

    printf("Reflect Array HashMap test6-------[OK] \n");
    break;
  }
}
