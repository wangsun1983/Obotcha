#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ConfReader.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int testcreate() {

    try {
        ConfReader reader = createConfReader("abcd.conf");
        printf("---[ConfReader create test} case1] [FAILED]--- \n");
    } catch(InitializeException e) {}

}
