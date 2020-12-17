#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int stringUnicodeDataTest() {
    printf("---[JsonReader String Unicode Data Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_unicode_01.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Unicode Data Test case1] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("a")) {
        printf("---[JsonReader String Unicode Data Test case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Unicode Data Test case3] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_unicode_02.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Unicode Data Test case4] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("¢")) {
        printf("---[JsonReader String Unicode Data Test case5] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Unicode Data Test case6] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_unicode_03.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Unicode Data Test case7] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("€")) {
        printf("v_int is %s \n",v_int->toChars());
        printf("---[JsonReader String Unicode Data Test case8] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Unicode Data Test case9] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_unicode_04.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Unicode Data Test case10] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("𝄞")) {
        printf("---[JsonReader String Unicode Data Test case11] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Unicode Data Test case12] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_unicode_05.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Unicode Data Test case13] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("Zażółć gęślą jaźń")) {
        printf("---[JsonReader String Unicode Data Test case14] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Unicode Data Test case15] [OK]--- \n");
      break;
    }
}
