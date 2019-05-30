#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonArray.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int main() {
    printf("---[JsonReader Test Start]--- \n");
    JsonReader reader = createJsonReader(createString("abc.json"));
    JsonValue value = reader->parse();

    //String getString(String tag);
    while(1) {
        Integer v1 = value->getInteger("a");
        if(v1->toValue() != 1) {
          printf("---[JsonReader SimpleRead {getString()} case1] [FAILED]--- \n");
          break;
        }

        JsonArray arr1 = value->getArray("arr");
        if(arr1 == nullptr) {
          printf("---[JsonReader SimpleRead {getString()} case2] [FAILED]--- \n");
          break;
        }

        //printf("arr1->size is %d \n",arr1->size());
        if(arr1->size() != 3) {
          printf("---[JsonReader SimpleRead {getString()} case3] [FAILED]--- \n");
          break;
        }

        String str1 = arr1->getValue(0)->getString();
        //printf("str1 is %s \n",str1->toChars());
        if(!str1->equals("abc1")) {
          printf("---[JsonReader SimpleRead {getString()} case4] [FAILED]--- \n");
          break;
        }

        str1 = arr1->getValue(1)->getString();
        //printf("str1 is %s \n",str1->toChars());
        if(!str1->equals("abc2")) {
          printf("---[JsonReader SimpleRead {getString()} case5] [FAILED]--- \n");
          break;
        }

        str1 = arr1->getValue(2)->getString();
        //printf("str1 is %s \n",str1->toChars());
        if(!str1->equals("abc3")) {
          printf("---[JsonReader SimpleRead {getString()} case6] [FAILED]--- \n");
          break;
        }

        Integer v2 = value->getInteger("b");
        if(v2 ==nullptr || v2->toValue() != 2) {
          printf("---[JsonReader SimpleRead {getInteger()} case7] [FAILED]--- \n");
          break;
        }

        str1 = value->getString("c");
        if(str1 == nullptr || !str1->equals("nihao")) {
          printf("---[JsonReader SimpleRead {getString()} case8] [FAILED]--- \n");
          break;
        }

        JsonArray arr3 = value->getArray("arr2");
        JsonValue vv1 = arr3->getValue(0);
        String strvv1 = vv1->getString("vv");
        Integer intvv1 = vv1->getInteger("v1");
        if(strvv1 == nullptr || !strvv1->equals("v1")
           ||intvv1 == nullptr || intvv1->toValue() != 1) {
             printf("---[JsonReader SimpleRead {getArray()} case9] [FAILED]--- \n");
             break;
        }

        JsonValue vv2 = arr3->getValue(1);
        String strvv2 = vv2->getString("vv");
        Integer intvv2 = vv2->getInteger("v1");
        if(strvv2 == nullptr || !strvv2->equals("v2")
           ||intvv2 == nullptr || intvv2->toValue() != 2) {
             printf("---[JsonReader SimpleRead {getArray()} case10] [FAILED]--- \n");
             break;
        }

        Boolean b1 = value->getBoolean("ret");
        Boolean b2 = value->getBoolean("ret2");
        if(b1 == nullptr || b2 == nullptr
          || b1->toValue() != true || b2->toValue() != false) {
            printf("---[JsonReader SimpleRead {getArray()} case10] [FAILED]--- \n");
            break;
        }

        printf("---[JsonReader SimpleRead {getString()} case9] [Success]--- \n");
        break;
    }

    //bool isInt();
    while(1) {
      JsonValue v1 = value->getObject("a");
      if(!v1->isInt()) {
        printf("---[JsonReader SimpleRead {isInt()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getObject("arr");
      if(v2->isInt()) {
        printf("---[JsonReader SimpleRead {isInt()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isInt()} case3] [Success]--- \n");
      break;
    }

    //bool isBool();
    while(1) {
      JsonValue v1 = value->getObject("ret");
      if(!v1->isBool()) {
        printf("---[JsonReader SimpleRead {isBool()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getObject("arr");
      if(v2->isBool()) {
        printf("---[JsonReader SimpleRead {isBool()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isBool()} case3] [Success]--- \n");
      break;
    }

    //bool isString();
    while(1) {
      JsonValue v1 = value->getObject("c");
      if(!v1->isString()) {
        printf("---[JsonReader SimpleRead {isString()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getObject("arr");
      if(v2->isString()) {
        printf("---[JsonReader SimpleRead {isString()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isString()} case3] [Success]--- \n");
      break;
    }

    //bool isDouble();
    while(1) {
      JsonValue v1 = value->getObject("b");
      if(!v1->isDouble()) {
        printf("---[JsonReader SimpleRead {isDouble()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getObject("arr");
      if(v2->isDouble()) {
        printf("---[JsonReader SimpleRead {isDouble()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isDouble()} case3] [Success]--- \n");
      break;
    }

    //bool isArray();
    while(1) {
      JsonValue v1 = value->getObject("arr2");
      if(!v1->isArray()) {
        printf("---[JsonReader SimpleRead {isArray()} case1] [FAILED]--- \n");
        break;
      }

      JsonValue v2 = value->getObject("a");
      if(v2->isArray()) {
        printf("---[JsonReader SimpleRead {isArray()} case2] [FAILED]--- \n");
        break;
      }
      printf("---[JsonReader SimpleRead {isArray()} case3] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case3] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case6] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case8] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case11] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case13] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case16] [Success]--- \n");
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
      printf("---[JsonReader SimpleRead {put()} case18] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case21] [Success]--- \n");
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

      printf("---[JsonReader SimpleRead {put()} case23] [Success]--- \n");
      break;
    }

    //put(sp<_JsonArray> value);
    while(1) {
      //create a array attr
      JsonArray array = createJsonArray("testarr1");
      array->append((char *)"abc1");
      array->append(100);
      JsonValue jvalue = createJsonValue();
      jvalue->put("jv1",(char *)"jv1");
      jvalue->put("jv2",2);
      //printf("jvalue size is %d \n",jvalue->size());
      array->append(jvalue);
      value->put(array);

      //start check
      JsonArray testArray = value->getArray("testarr1");
      String t1 = testArray->getValue(0)->getString();
      if(!t1->equals("abc1")) {
        printf("---[JsonReader SimpleRead {put()} case24] [FAILED]--- \n");
        break;
      }

      Integer t2 = testArray->getValue(1)->getInteger();
      //printf("t2 is %d \n",t2->toValue());
      if(t2->toValue() != 100) {
        printf("---[JsonReader SimpleRead {put()} case25] [FAILED]--- \n");
        break;
      }

      JsonValue v3 = testArray->getValue(2);
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

      printf("---[JsonReader SimpleRead {put()} case27] [Success]--- \n");
      break;
    }

    //void remove(String tag);
    while(1) {
      JsonArray array = createJsonArray("testarr2");
      array->append((char *)"abc1");
      array->append(100);
      value->put(array);

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

      printf("---[JsonReader SimpleRead {remove()} case2] [Success]--- \n");
      break;
    }

    
#if 0
    String v1 = value->getString("c");
    LOGD("v1 is ",v1);

    JsonValueIterator iterator = value->getIterator();
    while(iterator->hasValue()) {
      LOGD("has value");
      String tag = iterator->getTag();
      if(iterator->isInt()) {
          Integer val = value->getInteger(tag);
          LOGD("tag is ",tag, " val is ",val);
      }

      iterator->next();

    }
#endif
}
