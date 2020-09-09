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

DECLARE_SIMPLE_CLASS(ImportData){
public:
  int data1;
  long data2;
  DECLARE_REFLECT_FIELD(ImportData,data1,data2)
};

void testImport() {
    JsonValue value = createJsonValue();
    ImportData importData = createImportData();
    importData->data1 = 1;
    importData->data2 = 123;

    value->importFrom(importData);
    JsonWriter writer = createJsonWriter(createString("wangslabc.json"));
    writer->write(value);
    writer->close();

}
