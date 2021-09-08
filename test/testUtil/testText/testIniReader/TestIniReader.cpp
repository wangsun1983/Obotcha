#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "IniReader.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int basetest() {

    while(1) {
        IniReader reader = createIniReader(createFile("./testData.ini"));
        auto maps = reader->getAll();
        if(maps->size() != 5) {
          printf("IniReader test1-------[FAILED] \n");
          break;
        }

        //L0
        auto map1 = maps->get(createString(""));
        if(map1->size() != 1) {
          printf("IniReader test2-------[FAILED] \n");
          break;
        }

        auto str1 = map1->get(S("abc1"));
        if(str1 == nullptr || !str1->equals("1")) {
          printf("IniReader test3-------[FAILED] \n");
          break;
        }

        //L1
        auto map2 = maps->get(createString("l1"));
        if(map2->size() != 6) {
          printf("IniReader test4-------[FAILED] \n");
          break;
        }

        if(map2->get(S("a")) == nullptr || !map2->get(S("a"))->equals("1")) {
          printf("IniReader test4-------[FAILED] \n");
          break;
        }

        printf("IniReader test100-------[OK] \n");
        break;
    }
}
