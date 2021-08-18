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

DECLARE_CLASS(MyWriteMember) {
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
  DECLARE_REFLECT_FIELD(MyWriteMember,intData,byteData,doubleData,
                        floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                        uint64Data,boolData)
};

DECLARE_CLASS(MyComplexWriteMember) {
public:
  MyWriteMember complexMember1;
  MyWriteMember complexMember2;

  DECLARE_REFLECT_FIELD(MyComplexWriteMember,complexMember1,complexMember2)
};

DECLARE_CLASS(MyData6) {
public:
    MyComplexWriteMember data1;
    DECLARE_REFLECT_FIELD(MyData6,data1)
};

int testReflectComplexFieldWrite() {
    //test1
    while(1) {
      MyData6 data = createMyData6();
      Object _data = data->getField("data1")->createObject();
      Object data1 = _data->getField("complexMember1")->createObject();
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

      if(data->data1->complexMember1->intData != 1) {
        printf("Reflect Reflect Complex Write test1-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->byteData != 2) {
        printf("Reflect Reflect Complex Write test2-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->doubleData != 1.1) {
        printf("Reflect Reflect Complex Write test3-------[FAIL] \n");
        break;
      }

      if(st(Math)::compareFloat(data->data1->complexMember1->floatData,2.2) != st(Math)::AlmostEqual) {
        printf("Reflect Reflect Complex Write test4-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->longData != 3) {
        printf("Reflect Reflect Complex Write test5-------[FAIL] \n");
        break;
      }

      if(!data->data1->complexMember1->stringData->equals("a")) {
        printf("Reflect Reflect Complex Write test6-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->uint8Data != 4) {
        printf("Reflect Reflect Complex Write test7-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->uint16Data != 5) {
        printf("Reflect Reflect Complex Write test8-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->uint32Data != 6) {
        printf("Reflect Reflect Complex Write test9-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->uint64Data != 7) {
        printf("Reflect Reflect Complex Write test10-------[FAIL] \n");
        break;
      }

      if(data->data1->complexMember1->boolData) {
        printf("Reflect Reflect Complex Write test11-------[FAIL] \n");
        break;
      }

      printf("Reflect Reflect Complex Write test12-------[OK] \n");
      break;
    }
}
