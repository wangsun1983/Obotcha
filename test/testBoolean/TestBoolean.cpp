#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"


int main() {

    printf("---[Boolean Test Start]--- \n");
    //Test Construct
    Boolean t0 = createBoolean(100);
    Boolean t0_1 = createBoolean(t0);
    if(t0 == t0_1){
        printf("Boolean construct test1-------[OK] \n");
    } else {
        printf("Boolean construct test1-------[FAIL] \n");
    }

    //Test bool equals(Boolean p);
    Boolean t1 = createBoolean(10);
    Boolean t2 = createBoolean(10);

    if(t1->equals(t2)) {
        printf("Boolean equal test1-------[OK] \n");
    } else {
        printf("Boolean equal test1-------[FAIL] \n");
    }

    if(t1 == t2) {
        printf("Boolean operator == test1-------[OK] \n");
    } else {
        printf("Boolean operator == test1-------[FAIL] \n");
    }

    //Test bool equals(int p);
    Boolean t3 = createBoolean(1);
    if(t3->equals(1)) {
        printf("Boolean equal test2-------[OK] \n");
    } else {
        printf("Boolean equal test2-------[FAIL] \n");
    }
}
