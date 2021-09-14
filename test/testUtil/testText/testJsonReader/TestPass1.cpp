#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"
#include "File.hpp"

#include "Log.hpp"

using namespace obotcha;

int testpass1() {
    JsonReader mReader = createJsonReader(createFile("pass1.json"));
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
    if(value7 != nullptr) {
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

        //"slash": "/ & \/",
        String value8_12 = value8->getString("slash");
        if(!value8_12->equals("/ & \/")) {
          printf("---[JsonReader testPass case20],[FAILED]--- \n");
          return 0;
        }

        //"alpha": "abcdefghijklmnopqrstuvwyz",
        String value8_13 = value8->getString("alpha");
        if(!value8_13->equals("abcdefghijklmnopqrstuvwyz")) {
          printf("---[JsonReader testPass case21],[FAILED]--- \n");
          return 0;
        }

        //"ALPHA": "ABCDEFGHIJKLMNOPQRSTUVWYZ",
        String value8_14 = value8->getString("ALPHA");
        if(!value8_14->equals("ABCDEFGHIJKLMNOPQRSTUVWYZ")) {
          printf("---[JsonReader testPass case21],[FAILED]--- \n");
          return 0;
        }

        //"digit": "0123456789",
        String value8_15 = value8->getString("digit");
        if(!value8_15->equals("0123456789")) {
          printf("---[JsonReader testPass case21],[FAILED]--- \n");
          return 0;
        }

        //"0123456789": "digit",
        String value8_16 = value8->getString("0123456789");
        if(!value8_16->equals("digit")) {
          printf("---[JsonReader testPass case22],[FAILED]--- \n");
          return 0;
        }

        //"special": "`1~!@#$%^&*()_+-={':[,]}|;.</>?",
        String value8_17 = value8->getString("special");
        if(!value8_17->equals("`1~!@#$%^&*()_+-={':[,]}|;.</>?")) {
          printf("---[JsonReader testPass case23],[FAILED]--- \n");
          return 0;
        }

        //"hex": "\u0123\u4567\u89AB\uCDEF\uabcd\uef4A",
        String value8_18 = value8->getString("hex");
        if(!value8_18->equals("\u0123\u4567\u89AB\uCDEF\uabcd\uef4A")) {
          printf("---[JsonReader testPass case24],[FAILED]--- \n");
          return 0;
        }

        //"true": true,
        Boolean value8_19 = value8->getBoolean("true");
        if(!value8_19->toValue()) {
          printf("---[JsonReader testPass case25],[FAILED]--- \n");
          return 0;
        }

        //"false": false,
        Boolean value8_20 = value8->getBoolean("false");
        if(value8_20->toValue()) {
          printf("---[JsonReader testPass case26],[FAILED]--- \n");
          return 0;
        }

        //"null": null,
        JsonValue value8_21 = value8->getValue("null");
        if(!value8_21->isNull()) {
          printf("---[JsonReader testPass case27],[FAILED]--- \n");
          return 0;
        }

        //"array":[  ],
        JsonValue value8_22 = value8->getValue("array");
        if(value8_22->size() != 0) {
          printf("---[JsonReader testPass case28],[FAILED]--- \n");
          return 0;
        }

        //"object":{  },
        JsonValue value8_23 = value8->getValue("object");
        if(!value8_23->isNull()) {
          printf("---[JsonReader testPass case29],[FAILED]--- \n");
          return 0;
        }

        //"address": "50 St. James Street",
        String value8_24 = value8->getString("address");
        if(!value8_24->equals("50 St. James Street")) {
          printf("---[JsonReader testPass case30],[FAILED]--- \n");
          return 0;
        }

        //"url": "http://www.JSON.org/",
        String value8_25 = value8->getString("url");
        if(!value8_25->equals("http://www.JSON.org/")) {
          printf("---[JsonReader testPass case31],[FAILED]--- \n");
          return 0;
        }

        //"comment": "// /* <!-- --",
        String value8_26 = value8->getString("comment");
        if(!value8_26->equals("// /* <!-- --")) {
          printf("---[JsonReader testPass case32],[FAILED]--- \n");
          return 0;
        }

        //"# -- --> */": " ",
        String value8_27 = value8->getString("# -- --> */");
        if(!value8_27->equals(" ")) {
          printf("---[JsonReader testPass case33],[FAILED]--- \n");
          return 0;
        }

        //" s p a c e d " :[1,2 , 3
        //
        //,
        //
        //4 , 5        ,          6           ,7        ],
        JsonValue value8_28 = value8->getValue(" s p a c e d ");
        if(value8_28->size() != 7) {
          printf("---[JsonReader testPass case34],[FAILED]--- \n");
          return 0;
        }

        for(int i = 0;i<7;i++) {
          if(value8_28->getIntegerAt(i)->toValue() != (i+1)) {
            //printf("v1 is %d,i is %d \n",value8_28->getIntegerAt(i)->toValue(),i);
            printf("---[JsonReader testPass case35],[FAILED]--- \n");
            return 0;
          }
        }

        //"compact":[1,2,3,4,5,6,7],
        JsonValue value8_29 = value8->getValue("compact");
        if(value8_29->size() != 7) {
          printf("---[JsonReader testPass case36],[FAILED]--- \n");
          return 0;
        }

        for(int i = 0;i<7;i++) {
          if(value8_29->getIntegerAt(i)->toValue() != (i+1)) {
            printf("---[JsonReader testPass case37],[FAILED]--- \n");
            return 0;
          }
        }

        //"jsontext": "{\"object with 1 member\":[\"array with 1 element\"]}",
        String value8_30 = value8->getString("jsontext");
        if(value8_30 == nullptr) {
          printf("---[JsonReader testPass case38],[FAILED]--- \n");
          return 0;
        }
            //"{\"object with 1 member\":[\"array with 1 element\"]}",
            JsonReader reader = createJsonReader(value8_30);
            JsonValue value8_30_1 = reader->get();
            JsonValue value8_30_1_1 = value8_30_1->getValue("object with 1 member");
            if(!value8_30_1_1->getStringAt(0)->equals("array with 1 element")) {
              printf("---[JsonReader testPass case39],[FAILED]--- \n");
              return 0;
            }

        //"quotes": "&#34; \u0022 %22 0x22 034 &#x22;",
        String value8_31 = value8->getString("quotes");
        if(!value8_31->equals("&#34; \u0022 %22 0x22 034 &#x22;")) {
          printf("---[JsonReader testPass case41],[FAILED]--- \n");
          return 0;
        }

        //"\/\\\"\uCAFE\uBABE\uAB98\uFCDE\ubcda\uef4A\b\f\n\r\t`1~!@#$%^&*()_+-=[]{}|;:',./<>?"
        //: "A key can be any string"
        String value8_32 = value8->getString("\/\\\"\uCAFE\uBABE\uAB98\uFCDE\ubcda\uef4A\b\f\n\r\t`1~!@#$%^&*()_+-=[]{}|;:',./<>?");
        if(!value8_32->equals("A key can be any string")) {
          printf("---[JsonReader testPass case42],[FAILED]--- \n");
          return 0;
        }

    //0.5 ,
    Double value9 = root->getDoubleAt(9);
    if(value9->toValue() != 0.5) {
      printf("---[JsonReader testPass case41] [FAILED]--- \n");
      return 0;
    }

    //98.6
    Double value10 = root->getDoubleAt(10);
    if(value10->toValue() != 98.6) {
      printf("---[JsonReader testPass case42] [FAILED]--- \n");
      return 0;
    }

    //99.44
    Double value11 = root->getDoubleAt(11);
    if(value11->toValue() != 99.44) {
      printf("---[JsonReader testPass case43] [FAILED]--- \n");
      return 0;
    }

    //1066,
    Integer value12 = root->getIntegerAt(12);
    if(value12->toValue() != 1066) {
      printf("---[JsonReader testPass case44] [FAILED]--- \n");
      return 0;
    }

    //1e1,
    Double value13 = root->getDoubleAt(13);
    if(value13->toValue() != 1e1) {
      printf("---[JsonReader testPass case45] [FAILED]--- \n");
      return 0;
    }

    //0.1e1,
    Double value14 = root->getDoubleAt(14);
    if(value14->toValue() != 0.1e1) {
      printf("---[JsonReader testPass case46] [FAILED]--- \n");
      return 0;
    }

    //1e-1,
    Double value15 = root->getDoubleAt(15);
    if(value15->toValue() != 1e-1) {
      printf("---[JsonReader testPass case47] [FAILED]--- \n");
      return 0;
    }

    //1e00,
    Double value16 = root->getDoubleAt(16);
    if(value16->toValue() != 1e00) {
      printf("---[JsonReader testPass case48] [FAILED]--- \n");
      return 0;
    }

    //2e+00,
    Double value17 = root->getDoubleAt(17);
    if(value17->toValue() != 2e+00) {
      printf("---[JsonReader testPass case49] [FAILED]--- \n");
      return 0;
    }

    //2e-00
    Double value18 = root->getDoubleAt(18);
    if(value18->toValue() != 2e-00) {
      printf("---[JsonReader testPass case50] [FAILED]--- \n");
      return 0;
    }

    printf("---[JsonReader testPass case...] [OK]--- \n");
    return 0;
}
