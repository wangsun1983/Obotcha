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

using namespace obotcha;

DECLARE_CLASS(IntArray) {
public:
  ArrayList<Integer> intlists;
  ArrayList<Long> longlists;
  ArrayList<Boolean> boollists;
  ArrayList<Double> doublelists;
  ArrayList<Float> floatlists;
  ArrayList<Uint8> uint8lists;
  ArrayList<Uint16> uint16lists;
  ArrayList<Uint32> uint32lists;
  ArrayList<Uint64> uint64lists;
  ArrayList<String> stringlists;
  DECLARE_REFLECT_FIELD(IntArray,intlists,longlists,boollists,
                        doublelists,floatlists,uint8lists,uint16lists,
                      uint32lists,uint64lists,stringlists)
};

int testReflectToSimpleArrayJson() {
  //test1
  while(1) {
    IntArray data = createIntArray();
    data->intlists = createArrayList<Integer>();
    data->intlists->add(createInteger(1));
    data->intlists->add(createInteger(2));

    data->longlists = createArrayList<Long>();
    data->longlists->add(createLong(1));
    data->longlists->add(createLong(2));

    data->boollists = createArrayList<Boolean>();
    data->boollists->add(createBoolean(true));
    data->boollists->add(createBoolean(false));

    data->doublelists = createArrayList<Double>();
    data->doublelists->add(createDouble(1.1));
    data->doublelists->add(createDouble(2.2));

    data->floatlists = createArrayList<Float>();
    data->floatlists->add(createFloat(1.1));
    data->floatlists->add(createFloat(2.2));

    data->uint8lists = createArrayList<Uint8>();
    data->uint8lists->add(createUint8(1));
    data->uint8lists->add(createUint8(2));

    data->uint16lists = createArrayList<Uint16>();
    data->uint16lists->add(createUint16(1));
    data->uint16lists->add(createUint16(2));

    data->uint32lists = createArrayList<Uint32>();
    data->uint32lists->add(createUint32(1));
    data->uint32lists->add(createUint32(2));

    data->uint64lists = createArrayList<Uint64>();
    data->uint64lists->add(createUint64(1));
    data->uint64lists->add(createUint64(2));

    data->stringlists = createArrayList<String>();
    data->stringlists->add(createString("a"));
    data->stringlists->add(createString("b"));

    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(data);
    JsonWriter jwriter = createJsonWriter("output3.json");
    jwriter->write(jvalue);

    JsonReader reader = createJsonReader(createFile("output3.json"));
    JsonValue readValue = reader->get();

    IntArray rdata3 = createIntArray();
    readValue->reflectTo(rdata3);

    if(rdata3->intlists == nullptr || rdata3->intlists->size() != 2) {
      printf("Reflect ArrayList To File test1-------[FAIL] \n");
      break;
    }
    //intlists
    Integer v0 = rdata3->intlists->get(0);
    if(v0 == nullptr || v0->toValue() != 1) {
      printf("Reflect ArrayList To File test2-------[FAIL] \n");
      break;
    }

    Integer v1 = rdata3->intlists->get(1);
    if(v1 == nullptr || v1->toValue() != 2) {
      printf("Reflect ArrayList To File test3-------[FAIL] \n");
      break;
    }

    //longlists
    Long vv1 = rdata3->longlists->get(0);
    if(vv1 == nullptr || vv1->toValue() != 1) {
      printf("Reflect ArrayList To File test4-------[FAIL] \n");
      break;
    }

    Long vv2 = rdata3->longlists->get(1);
    if(vv2 == nullptr || vv2->toValue() != 2) {
      printf("Reflect ArrayList To File test5-------[FAIL] \n");
      break;
    }

    //ArrayList<Boolean> boollists;
    Boolean vv3 = rdata3->boollists->get(0);
    if(vv3 == nullptr || vv3->toValue() != true) {
      printf("Reflect ArrayList To File test6-------[FAIL] \n");
      break;
    }

    Boolean vv4 = rdata3->boollists->get(1);
    if(vv4 == nullptr || vv4->toValue() != false) {
      printf("Reflect ArrayList To File test7-------[FAIL] \n");
      break;
    }

    //ArrayList<Double> doublelists;
    Double doubleValue = rdata3->doublelists->get(0);
    if(doubleValue == nullptr || doubleValue->toValue() != 1.1) {
      printf("Reflect ArrayList To File test7_1-------[FAIL] \n");
      break;
    }

    Double doubleValue2 = rdata3->doublelists->get(1);
    if(doubleValue2 == nullptr || doubleValue2->toValue() != 2.2) {
      printf("Reflect ArrayList To File test7_2-------[FAIL] \n");
      break;
    }

    //ArrayList<Float> floatlists;
    Float floatValue = rdata3->floatlists->get(0);
    if(floatValue == nullptr || st(Math)::compareFloat(floatValue->toValue(),1.1) != st(Math)::AlmostEqual) {
      printf("Reflect ArrayList To File test7_3-------[FAIL] \n");
      break;
    }

    Float floatValue2 = rdata3->floatlists->get(1);
    if(floatValue2 == nullptr || st(Math)::compareFloat(floatValue2->toValue(),2.2) != st(Math)::AlmostEqual) {
      printf("Reflect ArrayList To File test7_4-------[FAIL] \n");
      break;
    }

    //ArrayList<Uint8> uint8lists;
    Uint8 vv5 = rdata3->uint8lists->get(0);
    if(vv5 == nullptr || vv5->toValue() != 1) {
      printf("Reflect ArrayList To File test8-------[FAIL] \n");
      break;
    }

    Uint8 vv6 = rdata3->uint8lists->get(1);
    if(vv6 == nullptr || vv6->toValue() != 2) {
      printf("Reflect ArrayList To File test9-------[FAIL] \n");
      break;
    }

    //ArrayList<Uint16> uint16lists;
    Uint16 vv7 = rdata3->uint16lists->get(0);
    if(vv7 == nullptr || vv7->toValue() != 1) {
      printf("Reflect ArrayList To File test10-------[FAIL] \n");
      break;
    }

    Uint16 vv8 = rdata3->uint16lists->get(1);
    if(vv8 == nullptr || vv8->toValue() != 2) {
      printf("Reflect ArrayList To File test11-------[FAIL] \n");
      break;
    }

    //ArrayList<Uint32> uint32lists;
    Uint32 v4 = rdata3->uint32lists->get(0);
    if(v4 == nullptr || v4->toValue() != 1) {
      printf("Reflect ArrayList To File test12-------[FAIL] \n");
      break;
    }

    Uint32 v5 = rdata3->uint32lists->get(1);
    if(v5 == nullptr || v5->toValue() != 2) {
      printf("Reflect ArrayList To File test13-------[FAIL] \n");
      break;
    }

    //ArrayList<Uint64> uint64lists;
    Uint64 v6 = rdata3->uint64lists->get(0);
    if(v6 == nullptr || v6->toValue() != 1) {
      printf("Reflect ArrayList To File test14-------[FAIL] \n");
      break;
    }

    Uint64 v7 = rdata3->uint64lists->get(1);
    if(v7 == nullptr || v7->toValue() != 2) {
      printf("Reflect ArrayList To File test15-------[FAIL] \n");
      break;
    }

    //ArrayList<String> stringlists;
    String v8 = rdata3->stringlists->get(0);
    if(v8 == nullptr || !v8->equals("a")) {
      printf("Reflect ArrayList To File test16-------[FAIL] \n");
      break;
    }

    String v9 = rdata3->stringlists->get(1);
    if(v9 == nullptr || !v9->equals("b")) {
      printf("Reflect ArrayList To File test17-------[FAIL] \n");
      break;
    }

    printf("Reflect ArrayList To File test18-------[OK] \n");
    break;
  }
}
