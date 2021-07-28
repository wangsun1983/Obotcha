#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "FileNodeReader.hpp"

using namespace obotcha;

int main() {
    printf("msg_max is %d \n",st(FileNodeReader)::readInt("/proc/sys/fs/mqueue/msg_max"));
    printf("msgsize_max is %d \n",st(FileNodeReader)::readInt("/proc/sys/fs/mqueue/msgsize_max"));
}
