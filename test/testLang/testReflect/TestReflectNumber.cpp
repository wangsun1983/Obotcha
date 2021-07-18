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

DECLARE_SIMPLE_CLASS(NumberReflectData) {
public:
  Integer intData;
  Byte byteData;
  Double doubleData;
  Float floatData;
  Long longData;
  String stringData;
  Uint8 uint8Data;
  Uint16 uint16Data;
  Uint32 uint32Data;
  Uint64 uint64Data;
  Boolean boolData;
  DECLARE_REFLECT_FIELD(NumberReflectData,intData,byteData,doubleData,
                        floatData,longData,stringData,uint8Data,uint16Data,uint32Data,
                        uint64Data,boolData)
};

int testReflectNumber() {
  //test1
  while(1) {
      NumberReflectData data = createNumberReflectData();
      data->intData = createInteger(1);
      data->byteData = createByte(1);
      data->doubleData = createDouble(1.1);
      data->floatData = createFloat(2.2);
      data->longData = createLong(3);
      data->stringData = createString("abc");
      data->uint8Data = createUint8(4);
      data->uint16Data = createUint16(5);
      data->uint32Data = createUint32(6);
      data->uint64Data = createUint64(7);
      data->boolData = createBoolean(false);

      JsonValue jvalue = createJsonValue();

      //wangsl
      //auto list = data->getAllFields();
      //printf("size is %d \n",list->size());
      //wangsl

      jvalue->importFrom(data);
      //printf("JsonValue is %s \n",jvalue->toString()->toChars());

      JsonWriter jwriter = createJsonWriter("output4.json");
      jwriter->write(jvalue);
      jwriter->close();


      JsonReader reader = createJsonReader(createFile("output4.json"));
      JsonValue readValue = reader->get();
      printf("JsonValue is %s \n",readValue->toString()->toChars());

      NumberReflectData rdata3 = createNumberReflectData();
      readValue->reflectTo(rdata3);

      if(rdata3->intData == nullptr ||data->intData->toValue() != rdata3->intData->toValue()) {
        printf("Reflect Number To File test1-------[FAIL] \n");
        break;
      }

      if(rdata3->byteData == nullptr ||data->byteData->toValue() != rdata3->byteData->toValue()) {
        printf("Reflect Number To File test2-------[FAIL] \n");
        break;
      }

      if(rdata3->doubleData == nullptr ||data->doubleData->toValue() != rdata3->doubleData->toValue()) {
        printf("Reflect Number To File test3-------[FAIL] \n");
        break;
      }

      if(rdata3->floatData == nullptr
        ||st(Math)::compareFloat(data->floatData->toValue(),rdata3->floatData->toValue()) != st(Math)::AlmostEqual) {
        printf("data->floatData is %lf,rdata3->floatData is %lf \n",data->floatData->toValue(),rdata3->floatData->toValue());
        printf("Reflect Number To File test4-------[FAIL] \n");
        break;
      }

      if(rdata3->longData == nullptr ||data->longData->toValue() != rdata3->longData->toValue()) {
        printf("Reflect Number To File test5-------[FAIL] \n");
        break;
      }

      if(rdata3->uint8Data == nullptr ||data->uint8Data->toValue() != rdata3->uint8Data->toValue()) {
        printf("data->uint8Data is %d,rdata3->uint8Data is %d \n",data->uint8Data->toValue(),rdata3->uint8Data->toValue());
        printf("Reflect Number To File test6-------[FAIL] \n");
        break;
      }

      if(rdata3->uint16Data == nullptr ||data->uint16Data->toValue() != rdata3->uint16Data->toValue()) {
        printf("Reflect Number To File test7-------[FAIL] \n");
        break;
      }

      if(rdata3->uint32Data == nullptr ||data->uint32Data->toValue() != rdata3->uint32Data->toValue()) {
        printf("Reflect Number To File test8-------[FAIL] \n");
        break;
      }

      if(rdata3->uint64Data == nullptr ||data->uint64Data->toValue() != rdata3->uint64Data->toValue()) {
        printf("Reflect Number To File test9-------[FAIL] \n");
        break;
      }

      if(rdata3->boolData == nullptr ||data->boolData->toValue() != rdata3->boolData->toValue()) {
        printf("Reflect Number To File test10-------[FAIL] \n");
        break;
      }

      if(rdata3->stringData == nullptr ||!data->stringData->equals(rdata3->stringData)) {
        printf("Reflect Number To File test11-------[FAIL] \n");
        break;
      }

      printf("Reflect Number To File test12-------[OK] \n");
      break;
  }
}
