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

DECLARE_CLASS(ArrayData) {
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
  DECLARE_REFLECT_FIELD(ArrayData,intData,byteData,doubleData,
                        floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                        uint64Data,boolData)
};

DECLARE_CLASS(ListCollection) {
public:
  ArrayList<ArrayData> mylist;
  DECLARE_REFLECT_FIELD(ListCollection,mylist);
};

void testReflectArrayListFieldRead() {
    //test1
    while(1) {
      ListCollection collection = createListCollection();
      collection->mylist = createArrayList<ArrayData>();
      ArrayData arrayData1 = createArrayData();
      arrayData1->intData = 1;
      arrayData1->byteData = 2;
      arrayData1->doubleData = 1.1;
      arrayData1->floatData = 2.2;
      arrayData1->longData = 3;
      arrayData1->stringData = createString("a");
      arrayData1->uint8Data = 4;
      arrayData1->uint16Data = 5;
      arrayData1->uint32Data = 6;
      arrayData1->uint64Data = 7;
      arrayData1->boolData = false;
      collection->mylist->add(arrayData1);

      ArrayData arrayData2 = createArrayData();
      arrayData2->intData = 11;
      arrayData2->byteData = 12;
      arrayData2->doubleData = 11.1;
      arrayData2->floatData = 12.2;
      arrayData2->longData = 13;
      arrayData2->stringData = createString("b");
      arrayData2->uint8Data = 14;
      arrayData2->uint16Data = 15;
      arrayData2->uint32Data = 16;
      arrayData2->uint64Data = 17;
      arrayData2->boolData = false;
      collection->mylist->add(arrayData2);

      Field field = collection->getField("mylist");
      Object data1 = field->getListItemObject(0);
      //check field
      Field f = data1->getField("intData");
      if(f->getIntValue() != 1 || f->getType() != st(Field)::FieldTypeInt) {
        printf("Reflect ArrayList Field Read test1-------[FAIL] \n");
        break;
      }

      f = data1->getField("byteData");
      if(f->getByteValue() != 2 || f->getType() != st(Field)::FieldTypeByte) {
        printf("v is %d,type is %d \n",f->getByteValue(),st(Field)::FieldTypeByte);
        printf("Reflect ArrayList Field Read test2-------[FAIL] \n");
        break;
      }

      f = data1->getField("doubleData");
      if(f->getDoubleValue() != 1.1 || f->getType() != st(Field)::FieldTypeDouble) {
        printf("Reflect ArrayList Field Read test3-------[FAIL] \n");
        break;
      }

      f = data1->getField("floatData");
      if(st(Math)::compareFloat(2.2,f->getFloatValue()) != st(Math)::AlmostEqual || f->getType() != st(Field)::FieldTypeFloat) {
        printf("v is %lf,type is %d \n",f->getFloatValue(),f->getType());
        printf("Reflect ArrayList Field Read test4-------[FAIL] \n");
        break;
      }

      f = data1->getField("longData");
      if(f->getLongValue() != 3 || f->getType() != st(Field)::FieldTypeLong) {
        printf("Reflect ArrayList Field Read test5-------[FAIL] \n");
        break;
      }

      f = data1->getField("stringData");
      String v = f->getStringValue();
      if(v == nullptr || !v->equals("a")|| f->getType() != st(Field)::FieldTypeString) {
        printf("Reflect ArrayList Field Read test6-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint8Data");
      if(f->getByteValue() != 4 || f->getType() != st(Field)::FieldTypeUint8) {
        printf("uint8 value is %d,type is %d \n",f->getByteValue(),f->getType());
        printf("Reflect ArrayList Field Read test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint16Data");
      if(f->getUint16Value() != 5 || f->getType() != st(Field)::FieldTypeUint16) {
        printf("Reflect ArrayList Field Read test7-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint32Data");
      if(f->getUint32Value() != 6 || f->getType() != st(Field)::FieldTypeUint32) {
        printf("uint32 value is %d,type is %d \n",f->getUint32Value(),f->getType());
        printf("Reflect ArrayList Field Read test8-------[FAIL] \n");
        break;
      }

      f = data1->getField("uint64Data");
      if(f->getUint64Value() != 7 || f->getType() != st(Field)::FieldTypeUint64) {
        printf("Reflect ArrayList Field Read test9-------[FAIL] \n");
        break;
      }

      f = data1->getField("boolData");
      if(f->getBoolValue() || f->getType() != st(Field)::FieldTypeBool) {
        printf("Reflect ArrayList Field Read test10-------[FAIL] \n");
        break;
      }

      printf("Reflect ArrayList Field Read test11-------[OK] \n");
      break;
    }

}
