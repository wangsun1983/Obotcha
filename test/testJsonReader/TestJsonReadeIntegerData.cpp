#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int integerDataTest() {
    printf("---[JsonReader Integer Data Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_01.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case1] [FAILED]--- \n");
        break;
      }

      Integer v_int = value->getInteger();
      if(v_int == nullptr || v_int->toValue() != 2147483647) {
        printf("---[JsonReader Integer Data Test case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case2] [OK]--- \n");
      break;
    }

    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_02.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case3] [FAILED]--- \n");
        break;
      }

      Integer v_int = value->getInteger();
      if(v_int == nullptr || v_int->toValue() != -2147483648) {
        printf("---[JsonReader Integer Data Test case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case5] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_03.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case6] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 4294967295) {
        printf("---[JsonReader Integer Data Test case7] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case8] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_04.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case9] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 0) {
        printf("---[JsonReader Integer Data Test case10] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case11] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_05.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case11] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 1) {
        printf("v_int is %lld \n",v_int->toValue());
        printf("---[JsonReader Integer Data Test case12] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case13] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_06_64bits.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case14] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 9223372036854775808) {
        printf("v_int is %llld \n",v_int->toValue());
        printf("---[JsonReader Integer Data Test case15] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case16] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_07_64bits.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case17] [FAILED]--- \n");
        break;
      }

      Long v_int = value->getLong();
      if(v_int == nullptr || v_int->toValue() != -9223372036854775808) {
        printf("v_int is %llld \n",v_int->toValue());
        printf("---[JsonReader Integer Data Test case18] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case19] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_integer_08_64bits.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Integer Data Test case20] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 18446744073709551615) {
        printf("v_int is %llld \n",v_int->toValue());
        printf("---[JsonReader Integer Data Test case21] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Integer Data Test case22] [OK]--- \n");
      break;
    }

}
