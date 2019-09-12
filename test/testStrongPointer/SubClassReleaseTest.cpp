#include <stdio.h>

//#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ABC) {
public:
    virtual ~_ABC() {
        printf("_ABC \n");
    }
};

DECLARE_SIMPLE_CLASS(ABC2) EXTENDS(ABC) {
public:
    ~_ABC2() {
        printf("_ABC2 \n");
    }
};

int testSubClassRelease() {
    {
        ABC a = createABC2();
    }
}