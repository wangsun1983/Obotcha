#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

extern int basetest();
extern int testpass1();
extern int testremove();
extern int testreflect();
extern int arrayDataTest();
extern int basicDataTest();
extern int integerDataTest();
extern int objectDataTest();
extern int commentTest();
extern int realDataTest();
extern int stringDataTest();
extern int stringUnicodeDataTest();
extern int dataFailTest();

int main(){
    basetest();
    testpass1();
    testremove();
    testreflect();
    arrayDataTest();
    basicDataTest();
    integerDataTest();
    objectDataTest();
    commentTest();
    realDataTest();
    stringDataTest();
    stringUnicodeDataTest();
    dataFailTest();
}
