#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"
#include "File.hpp"

#include "Log.hpp"

using namespace obotcha;

int testremove() {
    JsonReader mReader = createJsonReader(createFile("abc.json"));
    JsonValue root = mReader->get();

    JsonValue arr = root->getValue("arr");
    arr->removeAt(1);
    if(arr->size() != 2) {
      printf("---[JsonReader testRemove case1...,size is %d ] [FAIL]--- \n",arr->size());
    }

    String attr1 = arr->getStringAt(0);
    if(!attr1->equals("abc1")) {
      printf("---[JsonReader testRemove case2...] [FAIL]--- \n");
    }

    String attr2 = arr->getStringAt(1);
    if(!attr2->equals("abc3")) {
      printf("---[JsonReader testRemove case3...] [FAIL]--- \n");
    }

    printf("---[JsonReader testRemove case...] [OK]--- \n");
    return 0;
}
