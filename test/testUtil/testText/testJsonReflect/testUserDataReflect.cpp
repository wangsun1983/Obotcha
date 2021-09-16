#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"
#include "Math.hpp"

using namespace obotcha;

DECLARE_CLASS(ReflectUserData) {
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

    DECLARE_REFLECT_FIELD(ReflectUserData,intData,byteData,doubleData,
                          floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                          uint64Data,boolData)
};

DECLARE_CLASS(ReflectUserObjData) {
public:
    Integer intObjData;
    Long longObjData;
    Uint8 uint8ObjData;
    Uint16 uint16ObjData;
    Uint32 uint32ObjData;
    Uint64 uint64ObjData;
    Boolean boolObjData;
    Float floatObjData;
    Double doubleObjData;
    Byte byteObjData;

    DECLARE_REFLECT_FIELD(ReflectUserObjData,intObjData,longObjData,uint8ObjData,
                          uint16ObjData,uint32ObjData,uint64ObjData,boolObjData,
                          floatObjData,doubleObjData,byteObjData)
};

void testUserDataReflect() {
    while(1) {
      ReflectUserData data = createReflectUserData();
      data->intData = 100;
      data->byteData = 25;
      data->doubleData = 100.10;
      data->floatData = 101.10;
      data->longData = 102;
      data->stringData = S("hhh");
      data->uint8Data = 103;
      data->uint16Data = 104;
      data->uint32Data = 105;
      data->uint64Data = 107;
      data->boolData = true;

      JsonWriter writer = createJsonWriter("userdata_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("userdata_test1.json"));
      JsonValue value2 = reader->get();
      ReflectUserData data2 = createReflectUserData();
      value2->reflectTo(data2);
      if(data2->intData != 100 ||
          data2->byteData != 25 ||
          data2->longData != 102 ||
         !data2->stringData->equals("hhh") ||
          data2->uint8Data != 103 ||
          data2->uint16Data != 104 ||
          data2->uint32Data != 105 ||
          data2->uint64Data != 107 ||
          !data2->boolData) {
            printf("---[JsonReflect UserData Reflect Test case1] [FAILED]--- \n");
      }

      if(st(Math)::compareDouble(data2->doubleData,100.10) != st(Math)::AlmostEqual) {
          printf("---[JsonReflect UserData Reflect Test case1_1] [FAILED]--- \n");
      }

      if(st(Math)::compareFloat(data2->floatData,101.10) != st(Math)::AlmostEqual) {
          printf("---[JsonReflect UserData Reflect Test case1_2] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      ReflectUserObjData data = createReflectUserObjData();
      data->intObjData = createInteger(100);
      data->longObjData = createLong(101);
      data->uint8ObjData = createUint8(102);
      data->uint16ObjData = createUint16(103);
      data->uint32ObjData = createUint32(104);
      data->uint64ObjData = createUint64(105);
      data->boolObjData = createBoolean(true);
      data->floatObjData = createFloat(102.10);
      data->doubleObjData = createDouble(103.20);
      data->byteObjData = createByte(23);

      JsonWriter writer = createJsonWriter("userdata_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("userdata_test2.json"));
      JsonValue value2 = reader->get();
      ReflectUserData data2 = createReflectUserData();
      value2->reflectTo(data2);

      if(data->intObjData == nullptr ||
        data->longObjData == nullptr ||
        data->uint8ObjData == nullptr ||
        data->uint16ObjData == nullptr ||
        data->uint32ObjData == nullptr ||
        data->uint64ObjData == nullptr ||
        data->boolObjData == nullptr||
        data->floatObjData == nullptr ||
        data->doubleObjData == nullptr ||
        data->byteObjData == nullptr) {
          printf("---[JsonReflect UserData Reflect Test case2] [FAILED]--- \n");
        }

      if(data->intObjData->toValue() != 100 ||
        data->longObjData->toValue() != 101 ||
        data->uint8ObjData->toValue() != 102 ||
        data->uint16ObjData->toValue() != 103 ||
        data->uint32ObjData->toValue() != 104 ||
        data->uint64ObjData->toValue() != 105 ||
        !data->boolObjData->toValue() ||
        data->byteObjData->toValue() != 23) {
          printf("---[JsonReflect UserData Reflect Test case3] [FAILED]--- \n");
        }

        if(st(Math)::compareFloat(data->floatObjData->toValue(),102.10) != st(Math)::AlmostEqual) {
            printf("---[JsonReflect UserData Reflect Test case3_1] [FAILED]--- \n");
        }

        if(st(Math)::compareDouble(data->doubleObjData->toValue(),103.20) != st(Math)::AlmostEqual) {
            printf("---[JsonReflect UserData Reflect Test case3_2] [FAILED]--- \n");
        }
        break;
    }
    printf("---[JsonReflect UserData Reflect Test case100] [OK]--- \n");
}
