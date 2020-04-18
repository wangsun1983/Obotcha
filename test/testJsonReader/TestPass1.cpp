#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int testpass1() {
    JsonReader mReader = createJsonReader("pass1.json");
    JsonValue root = mReader->get();

    //first array;
    //"JSON Test Pattern pass1",
    String v1 = root->getStringAt(0);
    if(!v1->equals("JSON Test Pattern pass1")) {
      printf("---[JsonReader testPass case1] [FAILED]--- \n");
      return 0;
    }

    //{"object with 1 member":["array with 1 element"]},
    JsonValue value1 = root->getValueAt(1);
    JsonValue value1_1 = value1->getValue("object with 1 member");
    String value1_2 = value1_1->getStringAt(0);
    if(!value1_2->equals("array with 1 element")) {
      printf("---[JsonReader testPass case2] [FAILED]--- \n");
      return 0;
    }

    if(value1_1->size() != 1) {
      printf("---[JsonReader testPass case3] [FAILED]--- \n");
      return 0;
    }

    //{},
    JsonValue value2 = root->getValueAt(2);
    if(value2->size() != 0) {
      printf("---[JsonReader testPass case4] [FAILED]--- \n");
      return 0;
    }

    //[],
    JsonValue value3 = root->getValueAt(3);
    if(value3->size() != 0) {
      printf("---[JsonReader testPass case4] [FAILED]--- \n");
      return 0;
    }

    //-42,
    Integer value4 = root->getIntegerAt(4);
    if(value4->toValue() != -42) {
      printf("---[JsonReader testPass case5] [FAILED]--- \n");
      return 0;
    }

    //true,
    Boolean value5 = root->getBooleanAt(5);
    if(!value5->toValue()) {
      printf("---[JsonReader testPass case6] [FAILED]--- \n");
      return 0;
    }

    //false,
    Boolean value6 = root->getBooleanAt(6);
    if(value6->toValue()) {
      printf("---[JsonReader testPass case7] [FAILED]--- \n");
      return 0;
    }

    //null,
    JsonValue value7 = root->getValueAt(7);
    if(value7->size() != 0) {
      printf("---[JsonReader testPass case8] [FAILED]--- \n");
      return 0;
    }

    //new json value
        //"integer": 1234567890,
        JsonValue value8 = root->getValueAt(8);

        Integer value8_1 = value8->getInteger("integer");
        if(value8_1->toValue() != 1234567890) {
          printf("---[JsonReader testPass case9] [FAILED]--- \n");
          return 0;
        }

        //"real": -9876.543210,
        Double value8_2 = value8->getDouble("real");
        if(value8_2->toValue() != -9876.543210) {
          printf("---[JsonReader testPass case10] [FAILED]--- \n");
          return 0;
        }

        //"e": 0.123456789e-12,
        Double value8_3 = value8->getDouble("e");
        if(value8_3->toValue() != 0.123456789e-12) {
          printf("---[JsonReader testPass case11] [FAILED]--- \n");
          return 0;
        }

        //"E": 1.234567890E+34,
        #if 0
        Double value8_4 = value8->getDouble("E");
        if(value8_3->toValue() != 1.234567890E+34) {
          printf("---[JsonReader testPass case12] [FAILED]--- \n");
          return 0;
        }
        #endif

        //"":  23456789012E66,
        Double value8_5 = value8->getDouble("");
        if(value8_5->toValue() != 23456789012E66) {
          printf("---[JsonReader testPass case13],value is %f [FAILED]--- \n",value8_5->toValue());
          return 0;
        }

        //"zero": 0,
        Double value8_6 = value8->getDouble("zero");
        if(value8_6->toValue() != 0) {
          printf("---[JsonReader testPass case14],value is %f [FAILED]--- \n",value8_6->toValue());
          return 0;
        }

        //"one": 1,
        Integer value8_7 = value8->getInteger("one");
        if(value8_7->toValue() != 1) {
          printf("---[JsonReader testPass case15],[FAILED]--- \n");
          return 0;
        }

        //"space": " ",
        String value8_8 = value8->getString("space");
        if(!value8_8->equals(" ")) {
          printf("---[JsonReader testPass case16],[FAILED]--- \n");
          return 0;
        }

        //"quote": "\"",
        String value8_9 = value8->getString("quote");
        if(!value8_9->equals("\"")) {
          printf("---[JsonReader testPass case17],[FAILED]--- \n");
          return 0;
        }

        //"backslash": "\\",
        String value8_10 = value8->getString("backslash");
        if(!value8_10->equals("\\")) {
          printf("---[JsonReader testPass case18],[FAILED]--- \n");
          return 0;
        }

        //"controls": "\b\f\n\r\t",
        String value8_11 = value8->getString("controls");
        if(!value8_11->equals("\b\f\n\r\t")) {
          printf("---[JsonReader testPass case19],[FAILED]--- \n");
          return 0;
        }

    printf("---[JsonReader testPass case...] [OK]--- \n");
    return 0;
}
