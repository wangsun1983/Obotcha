#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"
#include <vector>

using namespace obotcha;
DECLARE_SIMPLE_CLASS(BaseImportData) {
public:
  int baseData1;
  DECLARE_REFLECT_FIELD(BaseImportData,baseData1)
};

DECLARE_SIMPLE_CLASS(SubImportData) {
public:
  int subData1;
  long subData2;
  String subData3;
  ArrayList<BaseImportData> subData4;
  DECLARE_REFLECT_FIELD(SubImportData,subData1,subData2,subData3,subData4)
};

DECLARE_SIMPLE_CLASS(ImportData){
public:
  int data1;
  long data2;
  SubImportData data3;
  ArrayList<SubImportData> data4;
  DECLARE_REFLECT_FIELD(ImportData,data1,data2,data3,data4)
};

void testImport() {
  /*
    JsonValue value = createJsonValue();
    ImportData importData = createImportData();
    importData->data1 = 1;
    importData->data2 = 123;

    importData->data3 = createSubImportData();
    importData->data3->subData1 = 222;
    importData->data3->subData2 = 777;
    importData->data3->subData3 = createString("hello world");

    importData->data4 = createArrayList<SubImportData>();
    SubImportData t1 = createSubImportData();
    t1->subData1 = 1;
    t1->subData2 = 1111;
    t1->subData3 = createString("this is one");
    t1->subData4 = createArrayList<BaseImportData>();
    BaseImportData tt1 = createBaseImportData();
    tt1->baseData1 = 1122;
    t1->subData4->add(tt1);

    SubImportData t2 = createSubImportData();
    t2->subData1 = 2;
    t2->subData2 = 2222;
    t2->subData3 = createString("this is two");
    t2->subData4 = createArrayList<BaseImportData>();
    BaseImportData tt2 = createBaseImportData();
    tt2->baseData1 = 3344;
    t2->subData4->add(tt2);

    importData->data4->add(t1);
    importData->data4->add(t2);

    value->importFrom(importData);
    JsonWriter writer = createJsonWriter(createString("wangslabc.json"));
    writer->write(value);
    writer->close();*/
    JsonReader reader = createJsonReader(createFile("wangslabc.json"));
    JsonValue value = reader->get();

    ImportData info = createImportData();
    value->reflectTo(info);

    printf("data1 is %d \n",info->data1);
    printf("data2 is %ld \n",info->data2);
}
