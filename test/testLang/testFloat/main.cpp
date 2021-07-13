#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Float.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

extern int basetest();
extern int equaltest();
extern int updatetest();
extern int hashcodetest();

int main() {
    basetest();
    equaltest();
    updatetest();
    hashcodetest();
}
