#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int realDataTest() {
    printf("---[JsonReader Real Data Test Start]--- \n");

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_01.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case1] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 8589934592) {
        printf("---[JsonReader Real Data Test case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case3] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_02.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case4] [FAILED]--- \n");
        break;
      }

      Long v_int = value->getLong();
      if(v_int == nullptr || v_int->toValue() != -4294967295) {
        printf("---[JsonReader Real Data Test case5] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case6] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_03.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case7] [FAILED]--- \n");
        break;
      }

      Long v_int = value->getLong();
      if(v_int == nullptr || v_int->toValue() != -4294967295) {
        printf("---[JsonReader Real Data Test case8] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case9] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_04.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case10] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != 1.2345678) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case11] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case12] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_05.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case10] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != 1.2345678) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case11] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case12] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_06.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case13] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != -1.2345678) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case14] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case15] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_07.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case13] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != -1234567.8) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case14] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case15] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_07.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case13] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != -1234567.8) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case14] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case15] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_08.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case16] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 4300000001) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case17] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case18] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_09.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case19] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != 19000000000000000001) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case20] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case21] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_10.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case19] [FAILED]--- \n");
        break;
      }

      Long v_int = value->getLong();
      if(v_int == nullptr || v_int->toValue() != -2200000001) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case20] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case21] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_11.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case19] [FAILED]--- \n");
        break;
      }

      Double v_int = value->getDouble();
      if(v_int == nullptr || v_int->toValue() != -9300000000000000001) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case20] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case21] [OK]--- \n");
      break;
    }

/*
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_real_12.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader Real Data Test case22] [FAILED]--- \n");
        break;
      }

      Uint64 v_int = value->getUint64();
      if(v_int == nullptr || v_int->toValue() != 18446744073709551616) {
        printf("v_int is %lf \n",v_int->toValue());
        printf("---[JsonReader Real Data Test case23] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader Real Data Test case24] [OK]--- \n");
      break;
    }
*/
}
