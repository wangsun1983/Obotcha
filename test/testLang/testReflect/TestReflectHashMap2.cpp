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

DECLARE_CLASS(MapValue1) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(MapValue1,data1,data2)
};

DECLARE_CLASS(TestMapData1) {
public:
  HashMap<String,MapValue1> mmaps;
  DECLARE_REFLECT_FIELD(TestMapData1,mmaps)
};

//------
DECLARE_CLASS(MapMember) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(MapMember,data1,data2)
};

DECLARE_CLASS(MapValue2) {
public:
  HashMap<String,MapMember> maps;
  DECLARE_REFLECT_FIELD(MapValue2,maps)
};

DECLARE_CLASS(TestMapData2) {
public:
  HashMap<String,MapValue2> maps;
  DECLARE_REFLECT_FIELD(TestMapData2,maps)
};

int testReflectMap2() {
  while(1) {
    TestMapData2 data2 = createTestMapData2();
    data2->maps = createHashMap<String,MapValue2>();

    MapValue2 value2_1 = createMapValue2();
    value2_1->maps = createHashMap<String,MapMember>();
    MapMember member = createMapMember();
    member->data1 = 1;
    member->data2 = 2;
    value2_1->maps->put(createString("member1"),member);

    MapMember member2 = createMapMember();
    member2->data1 = 3;
    member2->data2 = 4;
    value2_1->maps->put(createString("member2"),member2);

    data2->maps->put(createString("value1"),value2_1);

    MapValue2 value2_2 = createMapValue2();
    value2_2->maps = createHashMap<String,MapMember>();
    MapMember member_1 = createMapMember();
    member_1->data1 = 5;
    member_1->data2 = 6;
    value2_2->maps->put(createString("member1"),member_1);

    MapMember member_2 = createMapMember();
    member_2->data1 = 7;
    member_2->data2 = 8;
    value2_2->maps->put(createString("member2"),member_2);
    data2->maps->put(createString("value2"),value2_2);

    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(data2);

    JsonWriter jwriter = createJsonWriter("output_hashmap_case2_2.json");
    jwriter->write(jvalue);


    JsonReader reader = createJsonReader(createFile("output_hashmap_case2_2.json"));
    JsonValue readValue = reader->get();

    TestMapData2 result = createTestMapData2();
    readValue->reflectTo(result);

    if(result->maps == nullptr || result->maps->size() != 2) {
      printf("Reflect HashMap2  test4-------[FAIL] \n");
      break;
    }

    MapValue2 v2_1 = result->maps->get(createString("value1"));
    if(v2_1 == nullptr || v2_1->maps == nullptr || v2_1->maps->size() != 2) {
      printf("Reflect HashMap2  test5-------[FAIL] \n");
      break;
    }

    auto data = v2_1->maps->get(createString("member1"));
    if(data == nullptr || data->data1 != 1 || data->data2 != 2) {
      printf("Reflect HashMap2  test6-------[FAIL] \n");
      break;
    }

    auto dd2 = v2_1->maps->get(createString("member2"));
    if(dd2 == nullptr || dd2->data1 != 3 || dd2->data2 != 4) {
      printf("Reflect HashMap2  test7-------[FAIL] \n");
      break;
    }

    MapValue2 v2_2 = result->maps->get(createString("value2"));
    if(v2_2 == nullptr || v2_2->maps == nullptr || v2_2->maps->size() != 2) {
      printf("Reflect HashMap2  test8-------[FAIL] \n");
      break;
    }

    auto data3 = v2_2->maps->get(createString("member1"));
    if(data3 == nullptr || data3->data1 != 5 || data3->data2 != 6) {
      printf("Reflect HashMap2  test9-------[FAIL] \n");
      break;
    }

    auto data4 = v2_2->maps->get(createString("member2"));
    if(data4 == nullptr || data4->data1 != 7 || data4->data2 != 8) {
      printf("Reflect HashMap2  test10-------[FAIL] \n");
      break;
    }

    printf("Reflect HashMap2  test11-------[OK] \n");
    break;
  }


  while(1) {
    TestMapData1 data1 = createTestMapData1();
    data1->mmaps = createHashMap<String,MapValue1>();
    MapValue1 v1 = createMapValue1();
    v1->data1 = 1;
    v1->data2 = 2;
    data1->mmaps->put(createString("value1"),v1);

    MapValue1 v2 = createMapValue1();
    v2->data1 = 3;
    v2->data2 = 4;
    data1->mmaps->put(createString("value2"),v2);
    
    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(data1);

    JsonWriter jwriter = createJsonWriter("output_hashmap_case2_1.json");
    jwriter->write(jvalue);

    JsonReader reader = createJsonReader(createFile("output_hashmap_case2_1.json"));
    JsonValue readValue = reader->get();

    TestMapData1 result = createTestMapData1();
    readValue->reflectTo(result);

    if(result->mmaps == nullptr || result->mmaps->size() != 2) {
      printf("Reflect HashMap2  test1-------[FAIL] \n");
      break;
    }

    MapValue1 mV1 = result->mmaps->get(createString("value1"));
    if(mV1 == nullptr || mV1->data1 != 1 || mV1->data2 != 2) {
      printf("Reflect HashMap2  test2-------[FAIL] \n");
      break;
    }

    MapValue1 mV2 = result->mmaps->get(createString("value2"));
    if(mV2 == nullptr || mV2->data1 != 3 || mV2->data2 != 4) {
      printf("Reflect HashMap2  test3-------[FAIL] \n");
      break;
    }

    printf("Reflect HashMap2  test100-------[OK] \n");
    break;

  }
}