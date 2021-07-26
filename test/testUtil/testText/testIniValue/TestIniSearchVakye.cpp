#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "IniReader.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int searchvaluetest_char() {

    //
    IniReader reader = createIniReader(createFile("testData.ini"));
    IniValue v = reader->get();
    int v1 = v->getInteger("spl1",-1);
    //printf("v1 is %d \n",v1);
    if(v1 != 100) {
      printf("---[IniValue Test {searchValue(char *)} case1] [FAIL]--- \n");
    }

    String v2 = v->getString("spl2","");
    if(!v2->equals("aaa")) {
      printf("---[IniValue Test {searchValue(char *)} case2] [FAIL]--- \n");
    }

    double v3 = v->getDouble("spl3",0.0);
    if(v3 != 4.1) {
      printf("---[IniValue Test {searchValue(char *)} case3] [FAIL]--- \n");
    }

    bool v4 = v->getBoolean("spl5",true);
    if(v4 != false) {
      printf("---[IniValue Test {searchValue(char *)} case4] [FAIL]--- \n");
    }

    printf("---[IniValue Test {searchValue(char *)} case5] [OK]--- \n");

    return 0;
}

int searchvaluetest_string() {

    //
    IniReader reader = createIniReader(createFile("testData.ini"));
    IniValue v = reader->get();
    int v1 = v->getInteger(createString("spl1"),-1);
    //printf("v1 is %d \n",v1);
    if(v1 != 100) {
      printf("---[IniValue Test {searchValue(String)} case] [FAIL]--- \n");
    }

    String v2 = v->getString(createString("spl2"),createString(""));
    if(!v2->equals("aaa")) {
      printf("---[IniValue Test {searchValue(String)} case2] [FAIL]--- \n");
    }

    double v3 = v->getDouble(createString("spl3"),0.0);
    if(v3 != 4.1) {
      printf("---[IniValue Test {searchValue(String)} case3] [FAIL]--- \n");
    }

    bool v4 = v->getBoolean(createString("spl5"),true);
    if(v4 != false) {
      printf("---[IniValue Test {searchValue(String)} case4] [FAIL]--- \n");
    }

    printf("---[IniValue Test {searchValue(String)} case5] [OK]--- \n");

    return 0;
}

int searchvaluetest() {
    searchvaluetest_string();
    searchvaluetest_char();
    return 0;
}
