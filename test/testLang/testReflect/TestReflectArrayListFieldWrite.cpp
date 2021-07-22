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

DECLARE_SIMPLE_CLASS(ArrayData2) {
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
  DECLARE_REFLECT_FIELD(ArrayData2,intData,byteData,doubleData,
                        floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                        uint64Data,boolData)
};

DECLARE_SIMPLE_CLASS(ListCollection2) {
public:
  ArrayList<ArrayData2> mylist;
  DECLARE_REFLECT_FIELD(ListCollection2,mylist);
};

int testReflectArrayListFieldWrite() {
    //test1
    while(1) {
      ListCollection2 collection = createListCollection2();
      Field arrayField = collection->getField("mylist");
      arrayField->createObject();
      Object data1 = collection->getField("mylist")->createListItemObject();
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
      collection->getField("mylist")->addListItemObject(data1);
      //data2
      Object data2 = collection->getField("mylist")->createListItemObject();
      f = data2->getField("intData");
      f->setValue(11);

      f = data2->getField("byteData");
      f->setValue(12);

      f = data2->getField("doubleData");
      f->setValue(11.1);

      f = data2->getField("floatData");
      f->setValue(12.2);

      f = data2->getField("longData");
      f->setValue(13);

      f = data2->getField("stringData");
      f->setValue(createString("b"));

      f = data2->getField("uint8Data");
      f->setValue(14);

      f = data2->getField("uint16Data");
      f->setValue(15);

      f = data2->getField("uint32Data");
      f->setValue(16);

      f = data2->getField("uint64Data");
      f->setValue(17);

      f = data2->getField("boolData");
      f->setValue(false);
      collection->getField("mylist")->addListItemObject(data2);

      if(collection->mylist->size() != 2) {
        printf("Reflect ArrayList Field Write test1-------[FAIL],size is %d \n",collection->mylist->size());
        break;
      }

      ArrayData2 d1 = collection->mylist->get(0);
      if(d1->intData != 1) {
        printf("Reflect ArrayList Field Write test1_1-------[FAIL] \n");
        break;
      }

      if(d1->byteData != 2) {
        printf("Reflect ArrayList Field Write test2-------[FAIL] \n");
        break;
      }

      if(d1->doubleData != 1.1) {
        printf("Reflect ArrayList Field Write test3-------[FAIL] \n");
        break;
      }

      if(st(Math)::compareFloat(d1->floatData,2.2) != st(Math)::AlmostEqual) {
        printf("Reflect ArrayList Field Write test4-------[FAIL] \n");
        break;
      }

      if(d1->longData != 3) {
        printf("Reflect ArrayList Field Write test5-------[FAIL] \n");
        break;
      }

      if(!d1->stringData->equals("a")) {
        printf("Reflect ArrayList Field Write test6-------[FAIL] \n");
        break;
      }

      if(d1->uint8Data != 4) {
        printf("Reflect ArrayList Field Write test7-------[FAIL] \n");
        break;
      }

      if(d1->uint16Data != 5) {
        printf("Reflect ArrayList Field Write test8-------[FAIL] \n");
        break;
      }

      if(d1->uint32Data != 6) {
        printf("Reflect ArrayList Field Write test9-------[FAIL] \n");
        break;
      }

      if(d1->uint64Data != 7) {
        printf("Reflect ArrayList Field Write test10-------[FAIL] \n");
        break;
      }

      if(d1->boolData) {
        printf("Reflect ArrayList Field Write test11-------[FAIL] \n");
        break;
      }

      ArrayData2 d2 = collection->mylist->get(1);
      if(d2->intData != 11) {
        printf("Reflect ArrayList Field Write test12-------[FAIL] \n");
        break;
      }

      if(d2->byteData != 12) {
        printf("Reflect ArrayList Field Write test13-------[FAIL] \n");
        break;
      }

      if(d2->doubleData != 11.1) {
        printf("Reflect ArrayList Field Write test14-------[FAIL] \n");
        break;
      }

      if(st(Math)::compareFloat(d2->floatData,12.2) != st(Math)::AlmostEqual) {
        printf("Reflect ArrayList Field Write test15-------[FAIL] \n");
        break;
      }

      if(d2->longData != 13) {
        printf("Reflect ArrayList Field Write test16-------[FAIL] \n");
        break;
      }

      if(!d2->stringData->equals("b")) {
        printf("Reflect ArrayList Field Write test17-------[FAIL] \n");
        break;
      }

      if(d2->uint8Data != 14) {
        printf("Reflect ArrayList Field Write test18-------[FAIL] \n");
        break;
      }

      if(d2->uint16Data != 15) {
        printf("Reflect ArrayList Field Write test19-------[FAIL] \n");
        break;
      }

      if(d2->uint32Data != 16) {
        printf("Reflect ArrayList Field Write test20-------[FAIL] \n");
        break;
      }

      if(d2->uint64Data != 17) {
        printf("Reflect ArrayList Field Write test21-------[FAIL] \n");
        break;
      }

      if(d2->boolData) {
        printf("Reflect ArrayList Field Write test22-------[FAIL] \n");
        break;
      }

      printf("Reflect ArrayList Field Write test23-------[OK] \n");
      break;
    }
}
