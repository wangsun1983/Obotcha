#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"

using namespace obotcha;

extern int normaltest();
extern int notifytest();

int main() {
    normaltest();
    notifytest();
}
