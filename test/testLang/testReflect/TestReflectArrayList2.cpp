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

DECLARE_CLASS(ArrayData2) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(ArrayData2,data1,data2)
};

DECLARE_CLASS(ArrayDataList2) {
public:
  ArrayList<ArrayList<ArrayData2>> lists;
  DECLARE_REFLECT_FIELD(ArrayDataList2,lists)
};

DECLARE_CLASS(ArrayData3) {
public:
  ArrayList<Integer> list;
  DECLARE_REFLECT_FIELD(ArrayData3,list)
};

DECLARE_CLASS(ArrayDataList3) {
public:
  ArrayList<ArrayList<ArrayData3>> lists;
  DECLARE_REFLECT_FIELD(ArrayDataList3,lists)
};


int testReflectArrayList2() {
  while(1) {
    ArrayDataList3 ll = createArrayDataList3();
    ll->lists = createArrayList<ArrayList<ArrayData3>>();

    ArrayList<ArrayData3> ll_1 = createArrayList<ArrayData3>();
    ArrayData3 d3_1 = createArrayData3();
    d3_1->list = createArrayList<Integer>();
    d3_1->list->add(createInteger(1));
    d3_1->list->add(createInteger(2));
    ll_1->add(d3_1);

    ArrayData3 d3_2 = createArrayData3();
    d3_2->list = createArrayList<Integer>();
    d3_2->list->add(createInteger(3));
    d3_2->list->add(createInteger(4));
    ll_1->add(d3_2);

    ArrayData3 d3_3 = createArrayData3();
    d3_3->list = createArrayList<Integer>();
    d3_3->list->add(createInteger(5));
    d3_3->list->add(createInteger(6));

    ArrayList<ArrayData3> ll_2 = createArrayList<ArrayData3>();
    ll_2->add(d3_1);
    ll_2->add(d3_2);
    ll_2->add(d3_3);
    
    ll->lists->add(ll_1);
    ll->lists->add(ll_2);
    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(ll);

    JsonWriter jwriter = createJsonWriter("output_arraylist_case2_2.json");
    jwriter->write(jvalue);


    JsonReader reader = createJsonReader(createFile("output_arraylist_case2_2.json"));
    JsonValue readValue = reader->get();

    ArrayDataList3 ll_chk = createArrayDataList3();
    readValue->reflectTo(ll_chk);

    if(ll_chk->lists == nullptr) {
      printf("Reflect ArrayList2 test11-------[FAIL] \n");
      break;
    }

    if(ll_chk->lists->size() != 2) {
      printf("Reflect ArrayList2 test12-------[FAIL] \n");
      break;
    }

    ArrayList<ArrayData3> ll_0 = ll_chk->lists->get(0);
    if(ll_0 == nullptr || ll_0->size() != 2) {
      printf("Reflect ArrayList2 test13-------[FAIL] \n");
      break;
    }

    ArrayData3 ll_0_1 = ll_0->get(0);
    if(ll_0_1->list->size() != 2) {
      printf("Reflect ArrayList2 test13-------[FAIL] \n");
      break;
    }

    if(ll_0_1->list->get(0)->toValue() != 1 ||ll_0_1->list->get(1)->toValue() != 2) {
      printf("Reflect ArrayList2 test14-------[FAIL] \n");
      break;
    }

    ArrayData3 ll_0_2 = ll_0->get(1);
    if(ll_0_2->list->size() != 2) {
      printf("Reflect ArrayList2 test15-------[FAIL] \n");
      break;
    }

    if(ll_0_2->list->get(0)->toValue() != 3 ||ll_0_2->list->get(1)->toValue() != 4) {
      printf("Reflect ArrayList2 test16-------[FAIL] \n");
      break;
    }

    ll_1 = ll_chk->lists->get(1);
    if(ll_1 == nullptr || ll_1->size() != 3) {
      printf("Reflect ArrayList2 test17-------[FAIL] \n");
      break;
    }

    ArrayData3 ll_1_1 = ll_1->get(0);
    if(ll_1_1->list->size() != 2) {
      printf("Reflect ArrayList2 test18-------[FAIL] \n");
      break;
    }

    if(ll_1_1->list->get(0)->toValue() != 1 ||ll_1_1->list->get(1)->toValue() != 2) {
      printf("Reflect ArrayList2 test19-------[FAIL] \n");
      break;
    }

    ArrayData3 ll_1_2 = ll_1->get(1);
    if(ll_1_2->list->size() != 2) {
      printf("Reflect ArrayList2 test20-------[FAIL] \n");
      break;
    }

    if(ll_1_2->list->get(0)->toValue() != 3 ||ll_1_2->list->get(1)->toValue() != 4) {
      printf("Reflect ArrayList2 test21-------[FAIL] \n");
      break;
    }

    ArrayData3 ll_1_3 = ll_1->get(2);
    if(ll_1_3->list->size() != 2) {
      printf("Reflect ArrayList2 test22-------[FAIL] \n");
      break;
    }

    if(ll_1_3->list->get(0)->toValue() != 5 ||ll_1_3->list->get(1)->toValue() != 6) {
      printf("Reflect ArrayList2 test23-------[FAIL] \n");
      break;
    }

    break;
  }

  //test1
  while(1) {
    ArrayDataList2 ll = createArrayDataList2();
    ll->lists = createArrayList<ArrayList<ArrayData2>>();

    ArrayList<ArrayData2> l1 = createArrayList<ArrayData2>();
    ArrayData2 d1 = createArrayData2();
    d1->data1 = 1;
    d1->data2 = 2;

    ArrayData2 d2 = createArrayData2();
    d2->data1 = 1;
    d2->data2 = 2;
    l1->add(d1);
    l1->add(d2);

    ArrayList<ArrayData2> sl1 = createArrayList<ArrayData2>();
    ArrayData2 sd1 = createArrayData2();
    sd1->data1 = 1;
    sd1->data2 = 2;

    ArrayData2 sd2 = createArrayData2();
    sd2->data1 = 1;
    sd2->data2 = 2;
    sl1->add(d1);
    sl1->add(d2);


    ll->lists->add(l1);
    ll->lists->add(sl1);

    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(ll);

    JsonWriter jwriter = createJsonWriter("output_arraylist_case2_1.json");
    jwriter->write(jvalue);


    JsonReader reader = createJsonReader(createFile("output_arraylist_case2_1.json"));
    JsonValue readValue = reader->get();

    ArrayDataList2 ll2 = createArrayDataList2();
    readValue->reflectTo(ll2);

    if(ll2 == nullptr) {
      printf("Reflect ArrayList2 test1-------[FAIL] \n");
      break;
    }

    if(ll2->lists == nullptr) {
      printf("Reflect ArrayList2 test2-------[FAIL] \n");
      break;
    }

    if(ll2->lists->size() != 2) {
      printf("Reflect ArrayList2 test3-------[FAIL] \n");
      break;
    }

    ArrayList<ArrayData2> list_t1 = ll2->lists->get(0);
    if(list_t1->size() != 2) {
      printf("Reflect ArrayList2 test4-------[FAIL] \n");
      break;
    }

    ArrayData2 v_t1 = list_t1->get(0);
    if(v_t1->data1 != 1 || v_t1->data2 != 2) {
      printf("Reflect ArrayList2 test5-------[FAIL] \n");
      break;
    }

    ArrayData2 v_t2 = list_t1->get(1);
    if(v_t2->data1 != 1 || v_t2->data2 != 2) {
      printf("Reflect ArrayList2 test6-------[FAIL] \n");
      break;
    }

    ArrayList<ArrayData2> list_t2 = ll2->lists->get(1);
    if(list_t2->size() != 2) {
      printf("Reflect ArrayList2 test7-------[FAIL] \n");
      break;
    }

    ArrayData2 v2_t1 = list_t2->get(0);
    if(v2_t1->data1 != 1 || v2_t1->data2 != 2) {
      printf("Reflect ArrayList2 test8-------[FAIL] \n");
      break;
    }

    ArrayData2 v2_t2 = list_t1->get(1);
    if(v2_t2->data1 != 1 || v2_t2->data2 != 2) {
      printf("Reflect ArrayList2 test9-------[FAIL] \n");
      break;
    }

    printf("Reflect ArrayList2 test10-------[OK] \n");
    break;
  }

  return 0;
}
