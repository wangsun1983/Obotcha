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

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyData3) {
public:
    int intData;
    byte byteData;
    double doubleData;
    float floatData;
    long longData;
    String stringData;
    uint8_t uint8Data;
    uint16_t uint16Data;
    uint32_t uint32Data;
    uint64_t uint64Data;
    bool boolData;
    DECLARE_REFLECT_FIELD(MyData3,intData,byteData,doubleData,
                          floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                          uint64Data,boolData)
};

DECLARE_SIMPLE_CLASS(MyData4) {
public:
    Integer intData;
    Byte byteData;
    Double doubleData;
    Float floatData;
    Boolean boolData;
    Long longData;
    String stringData;
    Uint8 uint8Data;
    Uint16 uint16Data;
    Uint32 uint32Data;
    Uint64 uint64Data;
    DECLARE_REFLECT_FIELD(MyData4,intData,byteData,doubleData,
                          floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                          uint64Data,boolData)
};


int testReflectFieldWrite() {
    //test1
    while(1) {
      MyData3 data1 = createMyData3();
      //check field
      Field f = data1->getField("intData");
      f->setValue(1);

      f = data1->getField("byteData");
      f->setValue(2);

      f = data1->getField("doubleData");
      f->setValue(1.1);

      f = data1->getField("floatData");
      f->setValue(2.2);

      f = data1->getField("longData");
      f->setValue(3);

      f = data1->getField("stringData");
      f->setValue(createString("a"));

      f = data1->getField("uint8Data");
      f->setValue(4);

      f = data1->getField("uint16Data");
      f->setValue(5);

      f = data1->getField("uint32Data");
      f->setValue(6);

      f = data1->getField("uint64Data");
      f->setValue(7);

      f = data1->getField("boolData");
      f->setValue(false);
      if(data1->intData != 1) {
        printf("Reflect Reflect Field Write test1-------[FAIL] \n");
        break;
      }

      if(data1->byteData != 2) {
        printf("Reflect Reflect Field Write test2-------[FAIL] \n");
        break;
      }

      if(data1->doubleData != 1.1) {
        printf("Reflect Reflect Field Write test3-------[FAIL] \n");
        break;
      }

      if(st(Math)::compareFloat(data1->floatData,2.2) != st(Math)::AlmostEqual) {
        printf("Reflect Reflect Field Write test4-------[FAIL] \n");
        break;
      }

      if(data1->longData != 3) {
        printf("Reflect Reflect Field Write test5-------[FAIL] \n");
        break;
      }

      if(!data1->stringData->equals("a")) {
        printf("Reflect Reflect Field Write test6-------[FAIL] \n");
        break;
      }

      if(data1->uint8Data != 4) {
        printf("Reflect Reflect Field Write test7-------[FAIL] \n");
        break;
      }

      if(data1->uint16Data != 5) {
        printf("Reflect Reflect Field Write test8-------[FAIL] \n");
        break;
      }

      if(data1->uint32Data != 6) {
        printf("Reflect Reflect Field Write test9-------[FAIL] \n");
        break;
      }

      if(data1->uint64Data != 7) {
        printf("Reflect Reflect Field Write test10-------[FAIL] \n");
        break;
      }

      if(data1->boolData) {
        printf("Reflect Reflect Field Write test11-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Field test12-------[OK] \n");
      break;
    }

    //test1
    while(1) {
      MyData4 data1 = createMyData4();
      //check field
      Field f = data1->getField("intData");
      Integer v1 = Cast<Integer>(f->createObject());
      v1->update(1);

      f = data1->getField("byteData");
      Byte v2 = Cast<Byte>(f->createObject());
      v2->update(2);

      f = data1->getField("doubleData");
      Double v3 = Cast<Double>(f->createObject());
      v3->update(1.1);

      f = data1->getField("floatData");
      Float v4 = Cast<Float>(f->createObject());
      v4->update(2.2);

      f = data1->getField("longData");
      Long v5 = Cast<Long>(f->createObject());
      v5->update(3);

      f = data1->getField("stringData");
      f->setValue(createString("a"));

      f = data1->getField("uint8Data");
      Uint8 v7 = Cast<Uint8>(f->createObject());
      v7->update(4);

      f = data1->getField("uint16Data");
      Uint16 v7_1 = Cast<Uint16>(f->createObject());
      v7_1->update(5);

      f = data1->getField("uint32Data");
      Uint32 v8 = Cast<Uint32>(f->createObject());
      v8->update(6);

      f = data1->getField("uint64Data");
      Uint64 v9 = Cast<Uint64>(f->createObject());
      v9->update(7);

      f = data1->getField("boolData");
      Boolean v10 = Cast<Boolean>(f->createObject());
      v10->update(false);

      if(data1->intData == nullptr||data1->intData->toValue() != 1) {
        printf("Reflect Reflect Field Write test13-------[FAIL] \n");
        break;
      }

      if(data1->byteData == nullptr || data1->byteData->toValue() != 2) {
        printf("Reflect Reflect Field Write test14-------[FAIL] \n");
        break;
      }

      if(data1->doubleData == nullptr ||data1->doubleData->toValue() != 1.1) {
        printf("Reflect Reflect Field Write test15-------[FAIL] \n");
        break;
      }

      if(data1->floatData == nullptr
        ||st(Math)::compareFloat(data1->floatData->toValue(),2.2) != st(Math)::AlmostEqual) {
        printf("Reflect Reflect Field Write test16-------[FAIL] \n");
        break;
      }

      if(data1->longData == nullptr ||data1->longData->toValue() != 3) {
        printf("Reflect Reflect Field Write test17-------[FAIL] \n");
        break;
      }

      if(data1->stringData == nullptr ||!data1->stringData->equals("a")) {
        printf("Reflect Reflect Field Write test18-------[FAIL] \n");
        break;
      }

      if(data1->uint8Data == nullptr ||data1->uint8Data->toValue() != 4) {
        printf("Reflect Reflect Field Write test19-------[FAIL] \n");
        break;
      }

      if(data1->uint16Data == nullptr ||data1->uint16Data->toValue() != 5) {
        printf("Reflect Reflect Field Write test20-------[FAIL] \n");
        break;
      }

      if(data1->uint32Data == nullptr ||data1->uint32Data->toValue() != 6) {
        printf("Reflect Reflect Field Write test21-------[FAIL] \n");
        break;
      }

      if(data1->uint64Data == nullptr ||data1->uint64Data->toValue() != 7) {
        printf("Reflect Reflect Field Write test22-------[FAIL] \n");
        break;
      }

      if(data1->boolData == nullptr ||data1->boolData->toValue()) {
        printf("Reflect Reflect Field Write test23-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Field test24-------[OK] \n");
      break;
    }

}
