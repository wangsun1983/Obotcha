#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "UUID.hpp"
#include "Log.hpp"
#include "ZipStream.hpp"

using namespace obotcha;

int main() {
    //ZipStream zipstream = createZipStream();
    //zipstream->compressWithPassword("abc","/home/dji/mysource/Obotcha/test/testZipInputStream/newzip.zip","abcde");

    ZipStream unzip = createZipStream();
    unzip->uncompressWithPassword("abc.zip","/home/dji/mysource/Obotcha/test/testZipInputStream/tt1","abcde");
}
