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
            IniReader reader = createIniReader(createFile("abc"));
            printf("IniReader create test1-------[FAIL] \n");
        } catch(InitializeException e) {

        }

        try {
            File f;
            IniReader reader = createIniReader(f);
            printf("IniReader create test2-------[FAIL] \n");
        } catch(InitializeException e) {

        }

        //
        IniReader reader = createIniReader(createFile("testData.ini"));
        if(reader == nullptr || reader->get() == nullptr) {
            printf("IniReader create test3-------[FAIL] \n");
        }

        printf("IniReader create test4-------[OK] \n");
        break;
    }
}
