#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int stringDataTest() {
    printf("---[JsonReader String Data Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_01.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Data Test case1] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")) {
        printf("---[JsonReader String Data Test case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Data Test case3] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_02.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Data Test case4] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")) {
        printf("---[JsonReader String Data Test case5] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Data Test case6] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_03.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Data Test case7] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("http:\/\/jsoncpp.sourceforge.net\/")) {
        printf("---[JsonReader String Data Test case8] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Data Test case9] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_04.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Data Test case10] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("\"abc\\def\"")) {
        printf("---[JsonReader String Data Test case11] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Data Test case12] [OK]--- \n");
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("./test/data/test_string_05.json"));
      JsonValue value = reader->get();
      if(value == nullptr) {
        printf("---[JsonReader String Data Test case13] [FAILED]--- \n");
        break;
      }

      String v_int = value->getString();
      if(v_int == nullptr || !v_int->equals("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\")) {
        printf("---[JsonReader String Data Test case14] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader String Data Test case15] [OK]--- \n");
      break;
    }

}
