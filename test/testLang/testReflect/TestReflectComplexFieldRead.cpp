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

DECLARE_SIMPLE_CLASS(MyMember) {
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
  DECLARE_REFLECT_FIELD(MyMember,intData,byteData,doubleData,
                        floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                        uint64Data,boolData)
};

DECLARE_SIMPLE_CLASS(MyComplexMember) {
public:
  MyMember complexMember1;
  MyMember complexMember2;

  DECLARE_REFLECT_FIELD(MyComplexMember,complexMember1,complexMember2)
};

DECLARE_SIMPLE_CLASS(MyData5) {
public:
    MyComplexMember data1;
    DECLARE_REFLECT_FIELD(MyData5,data1)
};

int testReflectComplexFieldRead() {
    //test1
    while(1) {
      MyData5 data = createMyData5();
      data->data1 = createMyComplexMember();
      data->data1->complexMember1 = createMyMember();
      data->data1->complexMember1->intData = 1;
      data->data1->complexMember1->byteData = 2;
      data->data1->complexMember1->doubleData = 1.1;
      data->data1->complexMember1->floatData = 2.2;
      data->data1->complexMember1->longData = 3;
      data->data1->complexMember1->stringData = createString("a");
      data->data1->complexMember1->uint8Data = 4;
      data->data1->complexMember1->uint16Data = 5;
      data->data1->complexMember1->uint32Data = 6;
      data->data1->complexMember1->uint64Data = 7;
      data->data1->complexMember1->boolData = false;

      data->data1->complexMember2 = createMyMember();
      data->data1->complexMember2->intData = 11;
      data->data1->complexMember2->byteData = 12;
      data->data1->complexMember2->doubleData = 11.1;
      data->data1->complexMember2->floatData = 12.2;
      data->data1->complexMember2->longData = 13;
      data->data1->complexMember2->stringData = createString("b");
      data->data1->complexMember2->uint8Data = 14;
      data->data1->complexMember2->uint16Data = 15;
      data->data1->complexMember2->uint32Data = 16;
      data->data1->complexMember2->uint64Data = 17;
      data->data1->complexMember2->boolData = false;

      Field memberField = data->getField("data1");
      sp<Object> dd = memberField->getObjectValue();
      sp<Object> data1 = dd->getField("complexMember1")->getObjectValue();
      //check field
      Field f = data1->getField("intData");
      if(f->getIntValue() != 1 || f->getType() != st(Field)::FieldTypeInt) {
        printf("Reflect Complex Field Read test1-------[FAIL] \n");
        break;
      }
      f = data1->getField("byteData");
      if(f->getByteValue() != 2 || f->getType() != st(Field)::FieldTypeByte) {
        printf("v is %d,type is %d \n",f->getByteValue(),st(Field)::FieldTypeByte);
        printf("Reflect Complex Field Read test2-------[FAIL] \n");
        break;
      }

      f = data1->getField("doubleData");
      if(f->getDoubleValue() != 1.1 || f->getType() != st(Field)::FieldTypeDouble) {
        printf("Reflect Complex Field Read test3-------[FAIL] \n");
        break;
      }

      f = data1->getField("floatData");
      if(st(Math)::compareFloat(2.2,f->getFloatValue()) != st(Math)::CompareParamEqual || f->getType() != st(Field)::FieldTypeFloat) {
        printf("v is %lf,type is %d \n",f->getFloatValue(),f->getType());
        printf("Reflect Complex Field Read test4-------[FAIL] \n");
        break;
      }

      f = data1->getField("longData");
      if(f->getLongValue() != 3 || f->getType() != st(Field)::FieldTypeLong) {
        printf("Reflect Complex Field Read test5-------[FAIL] \n");
        break;
      }

      f = data1->getField("stringData");
      String v = f->getStringValue();
      if(v == nullptr || !v->equals("a")|| f->getType() != st(Field)::FieldTypeString) {
        printf("Reflect Complex Field Read test6-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint8Data");
      if(f->getByteValue() != 4 || f->getType() != st(Field)::FieldTypeUint8) {
        printf("uint8 value is %d,type is %d \n",f->getByteValue(),f->getType());
        printf("Reflect Complex Field Read test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint16Data");
      if(f->getUint16Value() != 5 || f->getType() != st(Field)::FieldTypeUint16) {
        printf("Reflect Complex Field Read test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint32Data");
      if(f->getUint32Value() != 6 || f->getType() != st(Field)::FieldTypeUint32) {
        printf("uint32 value is %d,type is %d \n",f->getUint32Value(),f->getType());
        printf("Reflect Complex Field Read test8-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint64Data");
      if(f->getUint64Value() != 7 || f->getType() != st(Field)::FieldTypeUint64) {
        printf("Reflect Complex Field Read test9-------[FAIL] \n");
        break;
      }

      f = data1->getField("boolData");
      if(f->getBoolValue() || f->getType() != st(Field)::FieldTypeBool) {
        printf("Reflect Complex Field Read test10-------[FAIL] \n");
        break;
      }

      //data2
      sp<Object> data2 = dd->getField("complexMember2")->getObjectValue();
      //check field
      f = data2->getField("intData");
      if(f->getIntValue() != 11 || f->getType() != st(Field)::FieldTypeInt) {
        printf("Reflect Complex Field Read test11-------[FAIL] \n");
        break;
      }

      f = data2->getField("byteData");
      if(f->getByteValue() != 12 || f->getType() != st(Field)::FieldTypeByte) {
        printf("v is %d,type is %d \n",f->getByteValue(),st(Field)::FieldTypeByte);
        printf("Reflect Complex Field Read test12-------[FAIL] \n");
        break;
      }

      f = data2->getField("doubleData");
      if(f->getDoubleValue() != 11.1 || f->getType() != st(Field)::FieldTypeDouble) {
        printf("Reflect Complex Field Read test13-------[FAIL] \n");
        break;
      }

      f = data2->getField("floatData");
      if(st(Math)::compareFloat(12.2,f->getFloatValue()) != st(Math)::CompareParamEqual || f->getType() != st(Field)::FieldTypeFloat) {
        printf("v is %lf,type is %d \n",f->getFloatValue(),f->getType());
        printf("Reflect Complex Field Read test14-------[FAIL] \n");
        break;
      }

      f = data2->getField("longData");
      if(f->getLongValue() != 13 || f->getType() != st(Field)::FieldTypeLong) {
        printf("Reflect Complex Field Read test15-------[FAIL] \n");
        break;
      }

      f = data2->getField("stringData");
      v = f->getStringValue();
      if(v == nullptr || !v->equals("b")|| f->getType() != st(Field)::FieldTypeString) {
        printf("Reflect Complex Field Read test16-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint8Data");
      if(f->getByteValue() != 14 || f->getType() != st(Field)::FieldTypeUint8) {
        printf("uint8 value is %d,type is %d \n",f->getByteValue(),f->getType());
        printf("Reflect Complex Field Read test17-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint16Data");
      if(f->getUint16Value() != 15 || f->getType() != st(Field)::FieldTypeUint16) {
        printf("Reflect Complex Field Read test17-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint32Data");
      if(f->getUint32Value() != 16 || f->getType() != st(Field)::FieldTypeUint32) {
        printf("uint32 value is %d,type is %d \n",f->getUint32Value(),f->getType());
        printf("Reflect Complex Field Read test18-------[FAIL] \n");
        break;
      }

      f = data2->getField("uint64Data");
      if(f->getUint64Value() != 17 || f->getType() != st(Field)::FieldTypeUint64) {
        printf("Reflect Complex Field Read test19-------[FAIL] \n");
        break;
      }

      f = data2->getField("boolData");
      if(f->getBoolValue() || f->getType() != st(Field)::FieldTypeBool) {
        printf("Reflect Complex Field Read test10-------[FAIL] \n");
        break;
      }

      printf("Reflect Complex Field Read test11-------[OK] \n");
      break;
    }
}
