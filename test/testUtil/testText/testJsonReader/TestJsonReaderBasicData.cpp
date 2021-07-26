#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int basicDataTest() {
    printf("---[JsonReader Basic Data Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_01.json"));
      JsonValue value = reader->get();
      Integer v = value->getInteger();
      if(v == nullptr || v->toValue() != 123456789) {
        printf("---[JsonReader basicDataTest case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case2] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_02.json"));
      JsonValue value = reader->get();
      Integer v = value->getInteger();
      if(v == nullptr || v->toValue() != -123456789) {
        printf("---[JsonReader basicDataTest case3] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case4] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_03.json"));
      JsonValue value = reader->get();
      Double v = value->getDouble();
      if(v == nullptr || v->toValue() != 1.2345678) {
        printf("---[JsonReader basicDataTest case5] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case6] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_04.json"));
      JsonValue value = reader->get();
      String v = value->getString();
      if(v == nullptr || !v->equals("abcdef")) {
        printf("---[JsonReader basicDataTest case7] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case8] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_05.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader basicDataTest case9] [FAILED]--- \n");
        break;
      }

      if(!value->isNull()) {
        printf("---[JsonReader basicDataTest case10] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case11] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_06.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader basicDataTest case12] [FAILED]--- \n");
        break;
      }

      Boolean b = value->getBoolean();
      if(b == nullptr || !b->toValue()) {
        printf("---[JsonReader basicDataTest case13] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case14] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_07.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader basicDataTest case15] [FAILED]--- \n");
        break;
      }

      Boolean b = value->getBoolean();
      if(b == nullptr || b->toValue()) {
        printf("---[JsonReader basicDataTest case16] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case17] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_08.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader basicDataTest case18] [FAILED]--- \n");
        break;
      }

      if(!value->isNull()) {
        printf("---[JsonReader basicDataTest case19] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case20] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_basic_09.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader basicDataTest case21] [FAILED]--- \n");
        break;
      }

      if(!value->isNull()) {
        printf("---[JsonReader basicDataTest case22] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader basicDataTest case23] [OK]--- \n");
      break;
    }

    printf("---[JsonReader basicDataTest case24] [OK]--- \n");
    return 0;
}
