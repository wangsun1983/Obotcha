#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "String.hpp"

using namespace obotcha;

void testToString() {
    Double d1 = createDouble(1.1);
    if(!d1->toString()->equals("1.1")) {
        printf("Double toString test1-------[Fail] \n");
    }

    printf("Double toString test2-------[OK] \n");
}
