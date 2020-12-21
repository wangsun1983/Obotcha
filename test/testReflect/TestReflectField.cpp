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

DECLARE_SIMPLE_CLASS(MyData1) {
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

DECLARE_SIMPLE_CLASS(MyData2) {
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


int testReflectField() {
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
        printf("Reflect Reflect Field test1-------[FAIL] \n");
        break;
      }

      f = data1->getField("byteData");
      if(f->getByteValue() != 2 || f->getType() != st(Field)::FieldTypeByte) {
        printf("v is %d,type is %d \n",f->getByteValue(),st(Field)::FieldTypeByte);
        printf("Reflect Reflect Field test2-------[FAIL] \n");
        break;
      }

      f = data1->getField("doubleData");
      if(f->getDoubleValue() != 1.1 || f->getType() != st(Field)::FieldTypeDouble) {
        printf("Reflect Reflect Field test3-------[FAIL] \n");
        break;
      }

      f = data1->getField("floatData");
      if(st(Math)::compareFloat(2.2,f->getFloatValue()) != st(Math)::CompareParamEqual || f->getType() != st(Field)::FieldTypeFloat) {
        printf("v is %lf,type is %d \n",f->getFloatValue(),f->getType());
        printf("Reflect Reflect Field test4-------[FAIL] \n");
        break;
      }

      f = data1->getField("longData");
      if(f->getLongValue() != 3 || f->getType() != st(Field)::FieldTypeLong) {
        printf("Reflect Reflect Field test5-------[FAIL] \n");
        break;
      }

      f = data1->getField("stringData");
      String v = f->getStringValue();
      if(v == nullptr || !v->equals("a")|| f->getType() != st(Field)::FieldTypeString) {
        printf("Reflect Reflect Field test6-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint8Data");
      if(f->getByteValue() != 4 || f->getType() != st(Field)::FieldTypeUint8) {
        printf("uint8 value is %d,type is %d \n",f->getByteValue(),f->getType());
        printf("Reflect Reflect Field test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint16Data");
      if(f->getUint16Value() != 5 || f->getType() != st(Field)::FieldTypeUint16) {
        printf("Reflect Reflect Field test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint32Data");
      if(f->getUint32Value() != 6 || f->getType() != st(Field)::FieldTypeUint32) {
        printf("uint32 value is %d,type is %d \n",f->getUint32Value(),f->getType());
        printf("Reflect Reflect Field test8-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint64Data");
      if(f->getUint64Value() != 7 || f->getType() != st(Field)::FieldTypeUint64) {
        printf("Reflect Reflect Field test9-------[FAIL] \n");
        break;
      }

      f = data1->getField("boolData");
      if(f->getBoolValue() || f->getType() != st(Field)::FieldTypeBool) {
        printf("Reflect Reflect Field test10-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Field test11-------[OK] \n");
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
      Integer intV = cast<tp(Integer)>(f->getObjectValue());
      if(intV != nullptr ||intV->toValue() != 1|| f->getType() != st(Field)::FieldTypeObject) {
        printf("Reflect Reflect Field test2-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Field test21-------[OK] \n");
      break;
    }
}
