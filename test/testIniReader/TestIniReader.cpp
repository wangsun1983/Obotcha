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
        //test Construct
        try {
            IniReader reader = createIniReader("abc");
            printf("IniReader create test1-------[FAIL] \n");
        } catch(InitializeException e) {

        }

        try {
            IniReader reader = createIniReader(nullptr);
            printf("IniReader create test2-------[FAIL] \n");
        } catch(InitializeException e) {

        }

        //
        IniReader reader = createIniReader("testData.ini");
        if(reader == nullptr || reader->get() == nullptr) {
            printf("IniReader create test3-------[FAIL] \n");
        }

        printf("IniReader create test4-------[OK] \n");
        break;
    }
}
