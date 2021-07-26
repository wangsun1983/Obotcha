#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int commentTest() {
    printf("---[JsonReader Comment Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_comment_01.json"));
      JsonValue root = reader->get();
      JsonValue v = root->getValue("test");
      JsonValue vv1 = v->getValueAt(0);
      String vv1_str = vv1->getString("a");
      if(vv1_str == nullptr || !vv1_str->equals("aaa")) {
        printf("---[JsonReader commonTest case1] [FAILED]--- \n");
        break;
      }

      JsonValue vv2 = v->getValueAt(1);
      String vv2_str = vv2->getString("b");
      if(vv2_str == nullptr || !vv2_str->equals("bbb")) {
        printf("---[JsonReader commonTest case2] [FAILED]--- \n");
        break;
      }

      JsonValue vv3 = v->getValueAt(2);
      String vv3_str = vv3->getString("c");
      if(vv3_str == nullptr || !vv3_str->equals("ccc")) {
        printf("---[JsonReader commonTest case3] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader commonTest case4] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_preserve_comment_01.json"));
      JsonValue root = reader->get();
      Integer v1 = root->getInteger("first");
      if(v1 == nullptr || v1->toValue() != 1) {
        printf("---[JsonReader commonTest case5] [FAILED]--- \n");
        break;
      }

      Integer v2 = root->getInteger("second");
      if(v2 == nullptr || v2->toValue() != 2) {
        printf("---[JsonReader commonTest case6] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader commonTest case7] [OK]--- \n");
      break;
    }

    printf("---[JsonReader commonTest case100] [OK]--- \n");
    return 0;
}
