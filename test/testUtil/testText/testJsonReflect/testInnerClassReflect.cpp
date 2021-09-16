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

DECLARE_CLASS(InnerData1) {
  public:
    int intData;
    DECLARE_REFLECT_FIELD(InnerData1,intData)
};

DECLARE_CLASS(InnerData2) {
  public:
    String stringData;
    DECLARE_REFLECT_FIELD(InnerData2,stringData)
};

DECLARE_CLASS(OuterData) {
public:
    InnerData1 data1;
    InnerData2 data2;

    DECLARE_REFLECT_FIELD(OuterData,data1,data2)
};

void testInnerClassReflect() {
    while(1) {
        OuterData data = createOuterData();
        data->data1 = createInnerData1();
        data->data1->intData = 1000;
        data->data2 = createInnerData2();
        data->data2->stringData = createString("hello world");

        JsonWriter writer = createJsonWriter("inner_class_test1.json");
        JsonValue value = createJsonValue();
        value->importFrom(data);
        writer->write(value);

        JsonReader reader = createJsonReader(createFile("inner_class_test1.json"));
        JsonValue value2 = reader->get();
        OuterData data2 = createOuterData();
        value2->reflectTo(data2);

        if(data2->data1 == nullptr ||
          data2->data2 == nullptr) {
            printf("---[JsonReflect Inner Data Reflect Test case1] [FAILED]--- \n");
        }

        if(data2->data1->intData != 1000 ||
          !data2->data2->stringData->equals("hello world")) {
            printf("---[JsonReflect Inner Data Reflect Test case2] [FAILED]--- \n");
        }
        break;
    }

    printf("---[JsonReflect UserData Reflect Test case100] [OK]--- \n");
}
