#include <stdio.h>

//#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

extern int normaltest();
extern int testSubClassRelease();

int main()
{
    //normaltest();
    testSubClassRelease();
}
