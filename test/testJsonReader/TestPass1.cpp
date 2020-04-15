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
    String v1 = root->getStringAt(0);
    printf("v1 value is %s \n",v1->toChars());
}
