#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonArray.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int main() {
    printf("---[JsonValueIterator Test Start]--- \n");
    JsonReader reader = createJsonReader(createString("abc.json"));
    JsonValue value = reader->parse();
    //String getTag();
    JsonValueIterator iterator = value->getIterator();
    while(1) {
      if(!iterator->getTag()->equals("a")) {
        printf("---[JsonValueIterator Test {getTag()} case1] [FAILED]--- \n");
        break;
      }
      printf("---[JsonValueIterator Test {getTag()} case2] [Success]--- \n");
      break;
    }

    //bool hasValue();
    while(1) {
      if(!iterator->hasValue()) {
        printf("---[JsonValueIterator Test {hasValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {hasValue()} case2] [Success]--- \n");
      break;
    }

    //bool isInt();
    while(1) {
      if(!iterator->isInt()) {
        printf("---[JsonValueIterator Test {isInt()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {isInt()} case2] [Success]--- \n");
      break;
    }

    //Integer getInteger();
    while(1) {
      Integer v1 = iterator->getInteger();
      if(v1 == nullptr || v1->toValue() != 1) {
        printf("---[JsonValueIterator Test {getInteger()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {getInteger()} case2] [Success]--- \n");
      break;
    }

    //bool isArray();
    while(1) {
      iterator->next();
      if(!iterator->isArray()) {
        printf("---[JsonValueIterator Test {isArray()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {isArray()} case2] [Success]--- \n");
      break;
    }

    //sp<_JsonArray> getArray();
    while(1) {
      JsonArray v1 = iterator->getArray();
      if(v1 == nullptr || v1->size() != 3) {
        printf("---[JsonValueIterator Test {getArray()} case1] [FAILED]--- \n");
        break;
      }

      String a1 = v1->getValue(0)->getString();
      if(a1 == nullptr ||!a1->equals("abc1")) {
        printf("---[JsonValueIterator Test {getArray()} case2] [FAILED]--- \n");
        break;
      }

      String a2 = v1->getValue(1)->getString();
      if(a2 == nullptr ||!a2->equals("abc2")) {
        printf("---[JsonValueIterator Test {getArray()} case3] [FAILED]--- \n");
        break;
      }

      String a3 = v1->getValue(2)->getString();
      if(a3 == nullptr ||!a3->equals("abc3")) {
        printf("---[JsonValueIterator Test {getArray()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {getArray()} case5] [Success]--- \n");
      break;
    }

    //bool isObject();
    while(1) {
        iterator->next();
        if(!iterator->isObject()) {
          printf("---[JsonValueIterator Test {isObject()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[JsonValueIterator Test {isObject()} case2] [Success]--- \n");
        break;
    }

    //sp<_JsonValue> getObject();
    while(1) {
      JsonValue v1 = iterator->getObject();
      if(v1 == nullptr) {
        printf("---[JsonValueIterator Test {getObject()} case1] [FAILED]--- \n");
        break;
      }

      Integer t1 = v1->getInteger("v1");
      if(t1 == nullptr || t1->toValue() != 1) {
        printf("---[JsonValueIterator Test {getObject()} case2] [FAILED]--- \n");
        break;
      }

      String t2 = v1->getString("vv");
      if(t2 == nullptr || !t2->equals("v1")) {
        printf("---[JsonValueIterator Test {getObject()} case3] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {getObject()} case4] [Success]--- \n");
      break;
    }

    //bool isString();
    while(1) {
      iterator->next();
      //String tag = iterator->getTag();
      //printf("tag2 is %s \n",tag->toChars());

      if(!iterator->isString()) {
        printf("---[JsonValueIterator Test {isString()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {isString()} case2] [Success]--- \n");
      break;
    }

    //String getString();
    while(1) {
      String v1 = iterator->getString();
      if(v1 == nullptr ||!v1->equals("nihao")) {
        printf("---[JsonValueIterator Test {getString()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {getString()} case2] [Success]--- \n");
      break;
    }

    //bool isBool();
    while(1) {
      iterator->next();
      //String tag = iterator->getTag();
      //printf("tag2 is %s \n",tag->toChars());

      if(!iterator->isBool()) {
        printf("---[JsonValueIterator Test {isBool()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {isBool()} case2] [Success]--- \n");
      break;
    }

    //Boolean getBoolean();
    while(1) {
      Boolean v1 = iterator->getBoolean();
      if(v1 == nullptr ||v1->toValue() != true) {
        printf("---[JsonValueIterator Test {getBoolean()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[JsonValueIterator Test {getBoolean()} case2] [Success]--- \n");
      break;
    }

}
