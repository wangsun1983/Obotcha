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

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ReflectWriteMember) {
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
  DECLARE_REFLECT_FIELD(ReflectWriteMember,intData,byteData,doubleData,
                        floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                        uint64Data,boolData)
};

DECLARE_SIMPLE_CLASS(ReflectData) {
public:
  ReflectWriteMember member1;
  ReflectWriteMember member2;
  DECLARE_REFLECT_FIELD(ReflectData,member1,member2)
};

int testReflectToXml() {
  //test1
  while(1) {
    ReflectData data = createReflectData();
    data->member1 = createReflectWriteMember();
    data->member2 = createReflectWriteMember();

    data->member1->intData = 1;
    data->member1->byteData = 2;
    data->member1->doubleData = 1.1;
    data->member1->floatData = 2.2;
    data->member1->longData = 3;
    data->member1->stringData = createString("a");
    data->member1->uint8Data = 4;
    data->member1->uint16Data = 5;
    data->member1->uint32Data = 6;
    data->member1->uint64Data = 7;
    data->member1->boolData = false;

    data->member2->intData = 11;
    data->member2->byteData = 12;
    data->member2->doubleData = 11.1;
    data->member2->floatData = 12.2;
    data->member2->longData = 13;
    data->member2->stringData = createString("b");
    data->member2->uint8Data = 14;
    data->member2->uint16Data = 15;
    data->member2->uint32Data = 16;
    data->member2->uint64Data = 17;
    data->member2->boolData = false;

    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(data);

    JsonWriter jwriter = createJsonWriter("output1.json");
    jwriter->write(jvalue);
    break;
  }
}
