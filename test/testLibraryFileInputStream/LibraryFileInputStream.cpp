#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <dlfcn.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LocalSocketClient.hpp"
#include "LibraryFileInputStream.hpp"

using namespace obotcha;

typedef void (*myfunc)(int, int);

int main() {
    LibraryFileInputStream stream = createLibraryFileInputStream(createString("./library/testLibrary.so"));
    stream->open();
    myfunc t = (myfunc)stream->getMethod(createString("start"));
    if(t != nullptr) {
      t(1,2);
    } else {
      printf("tt is nullptr \n");
    }
    
}
