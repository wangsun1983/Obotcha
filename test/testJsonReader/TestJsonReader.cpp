#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int basetest() {
    printf("---[JsonReader Test Start]--- \n");
    JsonReader reader = createJsonReader(createFile("abc.json"));
    JsonValue value = reader->get();

    //String getString(String tag);
    while(1) {
        Integer v1 = value->getInteger("a");
        if(v1->toValue() != 1) {
          printf("---[JsonReader SimpleRead {getString()} case1] [FAILED]--- \n");
          break;
        }

        Integer v2 = value->getInteger("b");
        if(v2 ==nullptr || v2->toValue() != 2) {
          printf("---[JsonReader SimpleRead {getInteger()} case7] [FAILED]--- \n");
          break;
        }

        String str1 = value->getString("c");
        if(str1 == nullptr || !str1->equals("nihao")) {
          printf("---[JsonReader SimpleRead {getString()} case8] [FAILED]--- \n");
          break;
        }

        JsonValue arr3 = value->getValue("arr2");
        JsonValue vv1 = arr3->getValueAt(0);
        String strvv1 = vv1->getString("vv");
        Integer intvv1 = vv1->getInteger("v1");
        if(strvv1 == nullptr || !strvv1->equals("v1")
           ||intvv1 == nullptr || intvv1->toValue() != 1) {
             printf("---[JsonReader SimpleRead {getValue()} case9] [FAILED]--- \n");
             break;
        }

        JsonValue vv2 = arr3->getValueAt(1);
        String strvv2 = vv2->getString("vv");
        Integer intvv2 = vv2->getInteger("v1");
        if(strvv2 == nullptr || !strvv2->equals("v2")
           ||intvv2 == nullptr || intvv2->toValue() != 2) {
             printf("---[JsonReader SimpleRead {getValue()} case10] [FAILED]--- \n");
             break;
        }

        Boolean b1 = value->getBoolean("ret");
        Boolean b2 = value->getBoolean("ret2");
        if(b1 == nullptr || b2 == nullptr
          || b1->toValue() != true || b2->toValue() != false) {
            printf("---[JsonReader SimpleRead {getValue()} case10] [FAILED]--- \n");
            break;
        }

        printf("---[JsonReader SimpleRead {getString()} case9] [OK]--- \n");
        break;
    }

    //bool isInt();
    while(1) {
      JsonValue v1 = value->getValue("a");
      if(!v1->isInt()) {
        printf("---[JsonReader SimpleRead {isInt()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getValue("arr");
      if(v2->isInt()) {
        printf("---[JsonReader SimpleRead {isInt()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isInt()} case3] [OK]--- \n");
      break;
    }

    //bool isBool();
    while(1) {
      JsonValue v1 = value->getValue("ret");
      if(!v1->isBool()) {
        printf("---[JsonReader SimpleRead {isBool()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getValue("arr");
      if(v2->isBool()) {
        printf("---[JsonReader SimpleRead {isBool()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isBool()} case3] [OK]--- \n");
      break;
    }

    //bool isString();
    while(1) {
      JsonValue v1 = value->getValue("c");
      if(!v1->isString()) {
        printf("---[JsonReader SimpleRead {isString()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getValue("arr");
      if(v2->isString()) {
        printf("---[JsonReader SimpleRead {isString()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isString()} case3] [OK]--- \n");
      break;
    }

    //bool isDouble();
    while(1) {
      JsonValue v1 = value->getValue("b");
      if(!v1->isDouble()) {
        printf("---[JsonReader SimpleRead {isDouble()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getValue("arr");
      if(v2->isDouble()) {
        printf("---[JsonReader SimpleRead {isDouble()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isDouble()} case3] [OK]--- \n");
      break;
    }

    //bool isArray();
    while(1) {
      JsonValue v1 = value->getValue("arr2");
      if(!v1->isArray()) {
        printf("---[JsonReader SimpleRead {isArray()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getValue("a");
      if(v2->isArray()) {
        printf("---[JsonReader SimpleRead {isArray()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isArray()} case3] [OK]--- \n");
      break;
    }

    //void put(String tag,String value);
    while(1) {
      value->put("test1",createString("test1"));

      String test1 = value->getString("test1");
      if(test1 == nullptr || !test1->equals("test1")) {
        printf("---[JsonReader SimpleRead {put()} case1] [FAILED]--- \n");
        break;
      }

      value->put("test2",nullptr);
      String test2 = value->getString("test2");
      if(test2 != nullptr) {
        printf("---[JsonReader SimpleRead {put()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case3] [OK]--- \n");
      break;
    }

    //void put(String tag,char *value);
    while(1) {
      value->put("test3",(char *)"test3");

      String test1 = value->getString("test3");
      if(test1 == nullptr || !test1->equals("test3")) {
        printf("---[JsonReader SimpleRead {put()} case4] [FAILED]--- \n");
        break;
      }

      value->put("test4",(char *)nullptr);
      String test2 = value->getString("test4");
      if(test2 != nullptr) {
        printf("---[JsonReader SimpleRead {put()} case5] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case6] [OK]--- \n");
      break;
    }

    //void put(String tag,std::string value);
    while(1) {
      std::string t = "test5";
      value->put("test5",t);

      String test1 = value->getString("test5");
      if(test1 == nullptr || !test1->equals("test5")) {
        printf("---[JsonReader SimpleRead {put()} case7] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case8] [OK]--- \n");
      break;
    }

    //void put(String tag,Integer value);
    while(1) {
      value->put("int1",createInteger(1));
      Integer test1 = value->getInteger("int1");

      if(test1 == nullptr || test1->toValue() != 1) {
        printf("---[JsonReader SimpleRead {put()} case9] [FAILED]--- \n");
        break;
      }

      Integer int2;
      value->put("int2",int2);
      Integer test2 = value->getInteger("int2");
      if(test2 != nullptr) {
        printf("---[JsonReader SimpleRead {put()} case10] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case11] [OK]--- \n");
      break;
    }

    //void put(String tag,int value);
    while(1) {
      value->put("int2",2);
      Integer test1 = value->getInteger("int2");

      if(test1 == nullptr || test1->toValue() != 2) {
        printf("---[JsonReader SimpleRead {put()} case12] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case13] [OK]--- \n");
      break;
    }

    //void put(String tag,Boolean value);
    while(1) {
      value->put("bool1",createBoolean(true));
      Boolean test1 = value->getBoolean("bool1");

      if(test1 == nullptr || test1->toValue() != true) {
        printf("---[JsonReader SimpleRead {put()} case14] [FAILED]--- \n");
        break;
      }

      Boolean int2;
      value->put("bool2",int2);
      Boolean test2 = value->getBoolean("bool2");
      if(test2 != nullptr) {
        printf("---[JsonReader SimpleRead {put()} case15] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case16] [OK]--- \n");
      break;
    }

    //void put(String tag,bool value);
    while(1) {
      value->put("bool3",true);
      Boolean test1 = value->getBoolean("bool3");

      if(test1 == nullptr || test1->toValue() != true) {
        printf("---[JsonReader SimpleRead {put()} case17] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {put()} case18] [OK]--- \n");
      break;
    }

    //void put(String tag,Double value);
    while(1) {
      value->put("double1",createDouble(1.1));
      Double test1 = value->getDouble("double1");

      if(test1 == nullptr || test1->toValue() != 1.1) {
        printf("---[JsonReader SimpleRead {put()} case19] [FAILED]--- \n");
        break;
      }

      Double int2;
      value->put("double2",int2);
      Double test2 = value->getDouble("double2");
      if(test2 != nullptr) {
        printf("---[JsonReader SimpleRead {put()} case20] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case21] [OK]--- \n");
      break;
    }

    //void put(String tag,double value);
    while(1) {
      value->put("double3",1.1);
      Double test1 = value->getDouble("double3");

      if(test1 == nullptr || test1->toValue() != 1.1) {
        printf("---[JsonReader SimpleRead {put()} case22] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case23] [OK]--- \n");
      break;
    }

    //put(sp<_JsonValue> value);
    while(1) {
      //create a array attr
      JsonValue array = createJsonValue();
      array->append((char *)"abc1");
      array->append(100);
      JsonValue jvalue = createJsonValue();
      jvalue->put("jv1",(char *)"jv1");
      jvalue->put("jv2",2);
      //printf("jvalue size is %d \n",jvalue->size());
      array->append(jvalue);
      value->put("testarr1",array);

      //start check
      JsonValue testArray = value->getValue("testarr1");
      String t1 = testArray->getStringAt(0);
      if(!t1->equals("abc1")) {
        printf("---[JsonReader SimpleRead {put()} case24] [FAILED]--- \n");
        break;
      }

      Integer t2 = testArray->getIntegerAt(1);
      //printf("t2 is %d \n",t2->toValue());
      if(t2->toValue() != 100) {
        printf("---[JsonReader SimpleRead {put()} case25] [FAILED]--- \n");
        break;
      }

      JsonValue v3 = testArray->getValueAt(2);
      //printf("v3 is %d \n",v3->size());
      if(!v3->getString("jv1")->equals("jv1")) {
        printf("---[JsonReader SimpleRead {put()} case26] [FAILED]--- \n");
        break;
      }

      //Integer t4 = testArray->getValue(3)->getInteger();
      if(v3->getInteger("jv2")->toValue()!= 2) {
        printf("---[JsonReader SimpleRead {put()} case27] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {put()} case27] [OK]--- \n");
      break;
    }

    //void remove(String tag);
    while(1) {
      JsonValue array = createJsonValue();
      array->append((char *)"abc1");
      array->append(100);
      value->put("testarr2",array);

      bool formexist = false;
      if(value->contains("testarr2")) {
        //printf("remove testArr2 exists \n");
        formexist = true;
      }

      value->remove("testarr2");
      if(value->contains("testarr2") && formexist) {
        printf("---[JsonReader SimpleRead {remove()} case１] [FAILED]--- \n");
        break;
      }

      value->remove("tt");

      printf("---[JsonReader SimpleRead {remove()} case2] [OK]--- \n");
      break;
    }

    //String getString(String tag);
    while(1) {
      String v1 = value->getString("c");
      if(v1 == nullptr || !v1->equals("nihao")) {
        printf("---[JsonReader SimpleRead {getString()} case１] [FAILED]--- \n");
        break;
      }

      String v2 = value->getString("what");
      if(v2 != nullptr) {
        printf("---[JsonReader SimpleRead {getString()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getString()} case3] [OK]--- \n");
      break;
    }

    //String getString();
    while(1) {
      JsonValue v1 = value->getValue(createString("c"));
      String str1 = v1->getString();
      if(str1 == nullptr || !str1->equals("nihao")) {
        printf("---[JsonReader SimpleRead {getString()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getString()} case5] [OK]--- \n");
      break;
    }

    //Integer getInteger(String tag);
    while(1) {
      Integer v1 = value->getInteger("a");
      if(v1 == nullptr || v1->toValue() != 1) {
        printf("---[JsonReader SimpleRead {getInteger()} case１] [FAILED]--- \n");
        break;
      }

      Integer v2 = value->getInteger("what");
      if(v2 != nullptr) {
        printf("---[JsonReader SimpleRead {getInteger()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getInteger()} case3] [OK]--- \n");
      break;
    }

    //Integer getInteger();
    while(1) {
      JsonValue v1 = value->getValue("a");
      Integer str1 = v1->getInteger();
      if(str1 == nullptr || str1->toValue() != 1) {
        printf("---[JsonReader SimpleRead {getInteger()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getInteger()} case5] [OK]--- \n");
      break;
    }

    //getBoolean(String tag)
    while(1) {
      Boolean v1 = value->getBoolean("ret");
      if(v1 == nullptr || v1->toValue() != true) {
        printf("---[JsonReader SimpleRead {getBoolean()} case１] [FAILED]--- \n");
        break;
      }

      Boolean v2 = value->getBoolean("what");
      if(v2 != nullptr) {
        printf("---[JsonReader SimpleRead {getBoolean()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getBoolean()} case3] [OK]--- \n");
      break;
    }

    //Boolean getBoolean();
    while(1) {
      JsonValue v1 = value->getValue("ret");
      Boolean str1 = v1->getBoolean();
      if(str1 == nullptr || str1->toValue() != true) {
        printf("---[JsonReader SimpleRead {getBoolean()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getBoolean()} case5] [OK]--- \n");
      break;
    }

    //getDouble(String tag)
    while(1) {
      Double v1 = value->getDouble("b");
      if(v1 == nullptr || v1->toValue() != 2) {
        printf("---[JsonReader SimpleRead {getDouble()} case１] [FAILED]--- \n");
        break;
      }

      Double v2 = value->getDouble("what");
      if(v2 != nullptr) {
        printf("---[JsonReader SimpleRead {getDouble()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getDouble()} case3] [OK]--- \n");
      break;
    }

    //getDouble();
    while(1) {
      JsonValue v1 = value->getValue("b");
      Double str1 = v1->getDouble();
      if(str1 == nullptr || str1->toValue() != 2) {
        printf("---[JsonReader SimpleRead {getDouble()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getDouble()} case5] [OK]--- \n");
      break;
    }

    //sp<_JsonValue> getValue(String tag);
    while(1) {
      JsonValue arr1 = value->getValue(createString("arr"));
      if(arr1 == nullptr) {
        printf("---[JsonReader SimpleRead {getValue()} case１] [FAILED]--- \n");
        break;
      }

      //printf("arr1->size is %d \n",arr1->size());
      if(arr1->size() != 3) {
        printf("---[JsonReader SimpleRead {getValue()} case2] [FAILED]--- \n");
        break;
      }

      String str1 = arr1->getStringAt(0);
      //printf("str1 is %s \n",str1->toChars());
      if(!str1->equals("abc1")) {
        printf("---[JsonReader SimpleRead {getValue()} case3] [FAILED]--- \n");
        break;
      }

      str1 = arr1->getStringAt(1);
      //printf("str1 is %s \n",str1->toChars());
      if(!str1->equals("abc2")) {
        printf("---[JsonReader SimpleRead {getValue()} case4] [FAILED]--- \n");
        break;
      }

      str1 = arr1->getStringAt(2);
      //printf("str1 is %s \n",str1->toChars());
      if(!str1->equals("abc3")) {
        printf("---[JsonReader SimpleRead {getValue()} case5] [FAILED]--- \n");
        break;
      }

      printf("---[JsonReader SimpleRead {getValue()} case6] [OK]--- \n");
      break;
    }


}
