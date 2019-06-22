#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "System.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 100 //s

static int disposeVal = -1;

using namespace obotcha;

extern int testThreadInterruptCase();
extern int testThreadCommonCase();

int main() {
    //testThreadInterruptCase();
    testThreadCommonCase();
}
