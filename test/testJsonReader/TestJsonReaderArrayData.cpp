#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int arrayDataTest() {
    printf("---[JsonReader Array Data Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_01.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case1] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case2] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case3] [FAILED]--- \n");
        break;
      }

      if(value->size() != 0) {
        printf("---[JsonReader SimpleRead {data test} case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {data test} case5] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_02.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case6] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case7] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case8] [FAILED]--- \n");
        break;
      }

      if(value->size() != 1) {
        printf("---[JsonReader SimpleRead {data test} case9] [FAILED]--- \n");
        break;
      }

      Integer v = value->getIntegerAt(0);
      if(v == nullptr || v->toValue() != 1) {
        printf("---[JsonReader SimpleRead {data test} case10] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {data test} case11] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_03.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case12] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case13] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case14] [FAILED]--- \n");
        break;
      }

      if(value->size() != 5) {
        printf("---[JsonReader SimpleRead {data test} case15] [FAILED]--- \n");
        break;
      }

      Integer v0 = value->getIntegerAt(0);
      Integer v1 = value->getIntegerAt(1);
      Integer v2 = value->getIntegerAt(2);
      Integer v3 = value->getIntegerAt(3);
      Integer v4 = value->getIntegerAt(4);
      if(v0 == nullptr || v0->toValue() != 1
        ||v1 == nullptr || v1->toValue() != 2
        ||v2 == nullptr || v2->toValue() != 3
        ||v3 == nullptr || v3->toValue() != 4
        ||v4 == nullptr || v4->toValue() != 5) {
        printf("---[JsonReader SimpleRead {data test} case16] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {data test} case17] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_04.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case18] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case19] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case20] [FAILED]--- \n");
        break;
      }

      if(value->size() != 4) {
        printf("---[JsonReader SimpleRead {data test} case21] [FAILED]--- \n");
        break;
      }

      Integer v0 = value->getIntegerAt(0);
      String v1 = value->getStringAt(1);
      Double v2 = value->getDoubleAt(2);
      Integer v3 = value->getIntegerAt(3);
      if(v0 == nullptr || v0->toValue() != 1
        ||v2 == nullptr || v2->toValue() != 12.3
        ||v1 == nullptr || !v1->equals("abc")
        ||v3 == nullptr || v3->toValue() != -4) {
        printf("---[JsonReader SimpleRead {data test} case22] [FAILED]--- \n");
        break;
      }

      if(value->getIntegerAt(4) != nullptr) {
        printf("---[JsonReader SimpleRead {data test} case22_1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {data test} case23] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_05.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case24] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case25] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case25] [FAILED]--- \n");
        break;
      }

      if(value->size() != 99) {
        printf("---[JsonReader SimpleRead {data test} case26] [FAILED]--- \n");
        break;
      }

      for(int i = 0;i < 99;i++) {
        Integer vv = value->getIntegerAt(i);
        if(vv == nullptr || vv->toValue() != (i+1)) {
          printf("case27 vv is %d,index is %d \n",vv->toValue(),i);
          printf("---[JsonReader SimpleRead {data test} case27] [FAILED]--- \n");
          break;
        }
      }

      printf("---[JsonReader SimpleRead {data test} case28] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_06.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case29] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case30] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case31] [FAILED]--- \n");
        break;
      }

      if(value->size() != 4) {
        printf("---[JsonReader SimpleRead {data test} case32] [FAILED]--- \n");
        break;
      }

      String str1 = value->getStringAt(0);
      String str2 = value->getStringAt(1);
      String str3 = value->getStringAt(2);
      String str4 = value->getStringAt(3);

      if(str1 == nullptr || !str1->equals("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
        ||str2 == nullptr || !str2->equals("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")
        ||str3 == nullptr || !str3->equals("ccccccccccccccccccccccc")
        ||str4 == nullptr || !str4->equals("dddddddddddddddddddddddddddddddddddddddddddddddddddd")) {
          printf("---[JsonReader SimpleRead {data test} case33] [FAILED]--- \n");
          break;
      }


      printf("---[JsonReader SimpleRead {data test} case28] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_array_07.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader SimpleRead {data test} case30] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case31] [FAILED]--- \n");
        break;
      }

      if(!value->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case32] [FAILED]--- \n");
        break;
      }

      if(value->size() != 1) {
        printf("---[JsonReader SimpleRead {data test} case33] [FAILED]--- \n");
        break;
      }

      JsonValue vv1 = value->getValueAt(0);
      if(!vv1->isArray()) {
        printf("---[JsonReader SimpleRead {data test} case34] [FAILED]--- \n");
        break;
      }

      String vv1Value = vv1->getStringAt(0);
      if(vv1Value == nullptr || !vv1Value->equals("A")) {
        printf("---[JsonReader SimpleRead {data test} case35] [FAILED]--- \n");
        break;
      }

      for(int index = 1;index<2120;index++) {
          Integer vInt = vv1->getIntegerAt(index);
          if(vInt->toValue() != (index-1)) {
            printf("---[JsonReader SimpleRead {data test} case36] [FAILED]--- \n");
            break;
          }
      }

      printf("---[JsonReader SimpleRead {data test} case37] [OK]--- \n");
      break;
    }
}
