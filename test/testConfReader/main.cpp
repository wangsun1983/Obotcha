#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ConfReader.hpp"
#include "ConfValue.hpp"
#include "Log.hpp"

using namespace obotcha;

extern int testcreate();
extern int basetest();

int main() {
    testcreate();
    basetest();
}
