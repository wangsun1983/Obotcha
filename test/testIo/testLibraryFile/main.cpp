#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <dlfcn.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LibraryFile.hpp"

using namespace obotcha;

using myfunc = int (*)(int , int );

int main() {
    LibraryFile file = createLibraryFile(createString("./library/libtest.so"));
    myfunc t = (myfunc)file->getMethod(createString("start"));

    int v1 = 100;
    int v2 = 101;
    int ret = t(v1,v2);

    if(ret != 201) {
      printf("---[LibraryFile Test case1] [FAILED]---,v1 is %d,v2 is %d \n",v1,v2);
    }
    printf("---[LibraryFile Test case2] [OK]--- \n");
}
