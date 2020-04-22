#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"

using namespace obotcha;

int main() {
    printf("---[JsonWriter Test Start]--- \n");

    //write a json
    JsonWriter writer = createJsonWriter(createString("abc.json"));
    JsonValue value = createJsonValue();
    value->put("a",1);
    value->put("c","nihao");

    JsonValue array = createJsonValue();
    array->append("abc1");
    array->append("abc2");
    array->append("abc3");

    value->put("darr",array);

    writer->write(value);
    writer->close();

    //read a Json
    JsonReader reader = createJsonReader(createString("abc.json"));
    JsonValue value2 = reader->get();
    while(1) {
      Integer i1 = value->getInteger("a");
      if(i1 == nullptr || i1->toValue() != 1) {
        printf("---[JsonWriter Test {write()} case1] [FAILED]--- \n");
        break;
      }

      String s1 = value->getString("c");
      if(s1 == nullptr || !s1->equals("nihao")) {
        printf("---[JsonWriter Test {write()} case2] [FAILED]--- \n");
        break;
      }

      JsonValue arr = value->getValue("darr");
      if(arr == nullptr) {
        printf("---[JsonWriter Test {write()} case3] [FAILED]--- \n");
        break;
      }

      String ss1 = arr->getStringAt(0);
      if(ss1 == nullptr || !ss1->equals("abc1")) {
        printf("---[JsonWriter Test {write()} case4] [FAILED]--- \n");
        break;
      }

      String ss2 = arr->getStringAt(1);
      if(ss2 == nullptr || !ss2->equals("abc2")) {
        printf("---[JsonWriter Test {write()} case5] [FAILED]--- \n");
        break;
      }

      String ss3 = arr->getStringAt(2);
      if(ss3 == nullptr || !ss3->equals("abc3")) {
        printf("---[JsonWriter Test {write()} case6] [FAILED]--- \n");
        break;
      }

      printf("---[JsonWriter Test {write()} case7] [Success]--- \n");
      break;
    }


}
