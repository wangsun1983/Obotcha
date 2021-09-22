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

DECLARE_CLASS(MyData1) {
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
    DECLARE_REFLECT_FIELD(MyData1,intData,byteData,doubleData,
                          floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                          uint64Data,boolData)
};

DECLARE_CLASS(MyData2) {
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
    DECLARE_REFLECT_FIELD(MyData2,intData,byteData,doubleData,
                          floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                          uint64Data,boolData)
};


void testReflectFieldRead() {
    //test1
    while(1) {
      MyData1 data1 = createMyData1();
      data1->intData = 1;
      data1->byteData = 2;
      data1->doubleData = 1.1;
      data1->floatData = 2.2;
      data1->longData = 3;
      data1->stringData = createString("a");
      data1->uint8Data = 4;
      data1->uint16Data = 5;
      data1->uint32Data = 6;
      data1->uint64Data = 7;
      data1->boolData = false;

      //check field
      Field f = data1->getField("intData");
      if(f->getIntValue() != 1 || f->getType() != st(Field)::FieldTypeInt) {
        printf("Reflect Reflect Field Read test1-------[FAIL] \n");
        break;
      }

      f = data1->getField("byteData");
      if(f->getByteValue() != 2 || f->getType() != st(Field)::FieldTypeByte) {
        printf("v is %d,type is %d \n",f->getByteValue(),st(Field)::FieldTypeByte);
        printf("Reflect Reflect Field Read test2-------[FAIL] \n");
        break;
      }

      f = data1->getField("doubleData");
      if(f->getDoubleValue() != 1.1 || f->getType() != st(Field)::FieldTypeDouble) {
        printf("Reflect Reflect Field Read test3-------[FAIL] \n");
        break;
      }

      f = data1->getField("floatData");
      if(st(Math)::compareFloat(2.2,f->getFloatValue()) != st(Math)::AlmostEqual || f->getType() != st(Field)::FieldTypeFloat) {
        printf("v is %lf,type is %d \n",f->getFloatValue(),f->getType());
        printf("Reflect Reflect Field Read test4-------[FAIL] \n");
        break;
      }

      f = data1->getField("longData");
      if(f->getLongValue() != 3 || f->getType() != st(Field)::FieldTypeLong) {
        printf("Reflect Reflect Field Read test5-------[FAIL] \n");
        break;
      }

      f = data1->getField("stringData");
      String v = f->getStringValue();
      if(v == nullptr || !v->equals("a")|| f->getType() != st(Field)::FieldTypeString) {
        printf("Reflect Reflect Field Read test6-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint8Data");
      if(f->getByteValue() != 4 || f->getType() != st(Field)::FieldTypeUint8) {
        printf("uint8 value is %d,type is %d \n",f->getByteValue(),f->getType());
        printf("Reflect Reflect Field Read test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint16Data");
      if(f->getUint16Value() != 5 || f->getType() != st(Field)::FieldTypeUint16) {
        printf("Reflect Reflect Field Read test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint32Data");
      if(f->getUint32Value() != 6 || f->getType() != st(Field)::FieldTypeUint32) {
        printf("uint32 value is %d,type is %d \n",f->getUint32Value(),f->getType());
        printf("Reflect Reflect Field Read test8-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint64Data");
      if(f->getUint64Value() != 7 || f->getType() != st(Field)::FieldTypeUint64) {
        printf("Reflect Reflect Field Read test9-------[FAIL] \n");
        break;
      }

      f = data1->getField("boolData");
      if(f->getBoolValue() || f->getType() != st(Field)::FieldTypeBool) {
        printf("Reflect Reflect Field Read test10-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Field Read test11-------[OK] \n");
      break;
    }

    //test2
    while(1) {
      MyData2 data2 = createMyData2();
      data2->intData = createInteger(1);
      data2->byteData = createByte(2);
      data2->doubleData = createDouble(1.1);
      data2->floatData = createFloat(2.2);
      data2->longData = createLong(3);
      data2->stringData = createString("a");
      data2->uint8Data = createUint8(4);
      data2->uint16Data = createUint16(5);
      data2->uint32Data = createUint32(6);
      data2->uint64Data = createUint64(7);
      data2->boolData = createBoolean(false);

      //check field
      Field f = data2->getField("intData");
      Integer intV = Cast<Integer>(f->getObjectValue());
      if(intV == nullptr ||intV->toValue() != 1|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test12-------[FAIL] \n");
        break;
      }

      f = data2->getField("byteData");
      Byte byteV = Cast<Byte>(f->getObjectValue());
      if(byteV == nullptr ||byteV->toValue() != 2|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test13-------[FAIL] \n");
        break;
      }

      f = data2->getField("doubleData");
      Double doubleV = Cast<Double>(f->getObjectValue());
      if(doubleV == nullptr ||doubleV->toValue() != 1.1|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test14-------[FAIL] \n");
        break;
      }

      f = data2->getField("floatData");
      Float floatV = Cast<Float>(f->getObjectValue());
      if(floatV == nullptr
        ||st(Math)::compareFloat(floatV->toValue(),2.2) != st(Math)::AlmostEqual
        || f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test15-------[FAIL] \n");
        break;
      }

      f = data2->getField("longData");
      Long longV = Cast<Long>(f->getObjectValue());
      if(longV == nullptr ||longV->toValue() != 3|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test16-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint8Data");
      Uint8 uint8V = Cast<Uint8>(f->getObjectValue());
      if(uint8V == nullptr ||uint8V->toValue() != 4|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test17-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint16Data");
      Uint16 uint16V = Cast<Uint16>(f->getObjectValue());
      if(uint16V == nullptr ||uint16V->toValue() != 5|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test18-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint32Data");
      Uint32 uint32V = Cast<Uint32>(f->getObjectValue());
      if(uint32V == nullptr ||uint32V->toValue() != 6|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test19-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint64Data");
      Uint64 uint64V = Cast<Uint64>(f->getObjectValue());
      if(uint64V == nullptr ||uint64V->toValue() != 7|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test20-------[FAIL] \n");
        break;
      }

      f = data2->getField("boolData");
      Boolean boolV = Cast<Boolean>(f->getObjectValue());
      if(boolV == nullptr ||boolV->toValue()|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field Read test21-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Field Read test22-------[OK] \n");
      break;
    }
}
