#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int objectDataTest() {
    printf("---[JsonReader Object Data Test Start]--- \n");

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_object_01.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Object Data Test case1] [FAILED]--- \n");
        break;
      }

      if(!value->isNull()) {
        printf("---[JsonReader Object Data Test case1_1] [FAILED]--- \n");
        break;
      }

      JsonValue v = value->getValue(0);
      if(v != nullptr) {
        printf("---[JsonReader Object Data Test case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Object Data Test case2] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_object_02.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Object Data Test case3] [FAILED]--- \n");
        break;
      }

      Integer v = value->getInteger("count");
      if(v == nullptr || v->toValue() != 1234) {
        printf("---[JsonReader Object Data Test case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Object Data Test case5] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_object_03.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Object Data Test case3] [FAILED]--- \n");
        break;
      }

      Integer v = value->getInteger("count");
      if(v == nullptr || v->toValue() != 1234) {
        printf("---[JsonReader Object Data Test case4] [FAILED]--- \n");
        break;
      }

      String v2 = value->getString("name");
      if(v2 == nullptr || !v2->equals("test")) {
        printf("---[JsonReader Object Data Test case5] [FAILED]--- \n");
        break;
      }

      String v3 = value->getString("attribute");
      if(v3 == nullptr || !v3->equals("random")) {
        printf("---[JsonReader Object Data Test case6] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Object Data Test case5] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_object_04.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Object Data Test case6] [FAILED]--- \n");
        break;
      }

      String v2 = value->getString("");
      if(v2 == nullptr || !v2->equals("1234")) {
        printf("---[JsonReader Object Data Test case7] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Object Data Test case8] [OK]--- \n");
      break;
    }

}
