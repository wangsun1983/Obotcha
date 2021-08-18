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

DECLARE_CLASS(ArrayListMember) {
public:
    int intMember;
    bool boolMember;
    uint64_t uint64Member;
    String stringMember;
    DECLARE_REFLECT_FIELD(ArrayListMember,intMember,boolMember,uint64Member,stringMember)
};

DECLARE_CLASS(ReflectArrayListData) {
public:
  ArrayList<ArrayListMember> lists;
  DECLARE_REFLECT_FIELD(ReflectArrayListData,lists)
};

int testReflectToArrayJson() {
  //test1
  while(1) {
    ReflectArrayListData data = createReflectArrayListData();
    data->lists = createArrayList<ArrayListMember>();

    ArrayListMember m1 = createArrayListMember();
    m1->intMember = 1;
    m1->boolMember = true;
    m1->uint64Member = 1;
    m1->stringMember = createString("1");
    data->lists->add(m1);

    ArrayListMember m2 = createArrayListMember();
    m2->intMember = 21;
    m2->boolMember = true;
    m2->uint64Member = 21;
    m2->stringMember = createString("2");
    data->lists->add(m2);

    ArrayListMember m3 = createArrayListMember();
    m3->intMember = 31;
    m3->boolMember = true;
    m3->uint64Member = 31;
    m3->stringMember = createString("3");
    data->lists->add(m3);

    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(data);
    JsonWriter jwriter = createJsonWriter("output2.json");
    jwriter->write(jvalue);

    JsonReader reader = createJsonReader(createFile("output2.json"));
    JsonValue readValue = reader->get();
    printf("trace1 \n");
    ReflectArrayListData rdata3 = createReflectArrayListData();
    readValue->reflectTo(rdata3);
    printf("trace2 \n");
    if(rdata3 == nullptr || rdata3->lists == nullptr || rdata3->lists->size() != 3) {
      printf("Reflect ArrayList To File test1-------[FAIL],rddata3 size is %d \n",rdata3->lists->size());
      break;
    }

    ArrayListMember r1 = rdata3->lists->get(0);
    if(m1->intMember != r1->intMember) {
      printf("m1->intMember is %d,r1->intMember is %d \n",m1->intMember,r1->intMember);
      printf("Reflect ArrayList To File test2-------[FAIL] \n");
      break;
    }

    if(m1->boolMember != r1->boolMember) {
      printf("m1->boolMember is %d,r1->boolMember is %d \n",m1->boolMember,r1->boolMember);
      printf("Reflect ArrayList To File test2_1-------[FAIL] \n");
      break;
    }

    if(m1->uint64Member != r1->uint64Member) {
      printf("Reflect ArrayList To File test3-------[FAIL] \n");
      break;
    }

    if(!m1->stringMember->equals(r1->stringMember)) {
      printf("Reflect ArrayList To File test4-------[FAIL] \n");
      break;
    }

    ArrayListMember r2 = rdata3->lists->get(1);
    if(m2->intMember != r2->intMember) {
      printf("Reflect ArrayList To File test5-------[FAIL] \n");
      break;
    }

    if(m2->boolMember != r2->boolMember) {
      printf("Reflect ArrayList To File test6-------[FAIL] \n");
      break;
    }

    if(m2->uint64Member != r2->uint64Member) {
      printf("Reflect ArrayList To File test7-------[FAIL] \n");
      break;
    }

    if(!m2->stringMember->equals(r2->stringMember)) {
      printf("Reflect ArrayList To File test8-------[FAIL] \n");
      break;
    }

    ArrayListMember r3 = rdata3->lists->get(2);
    if(m3->intMember != r3->intMember) {
      printf("Reflect ArrayList To File test9-------[FAIL] \n");
      break;
    }

    if(m3->boolMember != r3->boolMember) {
      printf("Reflect ArrayList To File test10-------[FAIL] \n");
      break;
    }

    if(m3->uint64Member != r3->uint64Member) {
      printf("Reflect ArrayList To File test11-------[FAIL] \n");
      break;
    }

    if(!m3->stringMember->equals(r3->stringMember)) {
      printf("Reflect ArrayList To File test10-------[FAIL] \n");
      break;
    }

    printf("Reflect ArrayList To File test11-------[OK] \n");
    break;
  }
}
