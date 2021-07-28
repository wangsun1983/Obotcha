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
#include "Exception.hpp"
#include "MethodNotSupportException.hpp"

using namespace obotcha;

int main() {
    //ZipStream zipstream = createZipStream();
    //zipstream->compressWithPassword("abc","/home/dsd/mysource/Obotcha/test/testZipInputStream/newzip.zip","abcde");
    printf("---[ZipStream Test Start]--- \n");

    //_ZipStream();
    while(1) {
        ZipStream zip = createZipStream();
        if(zip == nullptr) {
            printf("---[ZipStream Test {construct()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ZipStream Test {construct()} case2] [Success]--- \n");
        break;
    }

    //int read();
    while(1) {
        ZipStream zip = createZipStream();
        try {
            zip->read();
            printf("---[ZipStream Test {read()} case1] [FAIL]--- \n");
            break;
        } catch(MethodNotSupportException e) {}

        printf("---[ZipStream Test {read()} case2] [Success]--- \n");
        break;
    }

    //long read(ByteArray buffer);
    while(1) {
        ZipStream zip = createZipStream();
        try {
            ByteArray buff = createByteArray(2);
            zip->read(2);
            printf("---[ZipStream Test {read(ByteArray)} case1] [FAIL]--- \n");
            break;
        } catch(MethodNotSupportException e) {}

        printf("---[ZipStream Test {read(ByteArray)} case2] [Success]--- \n");
        break;
    }

    //bool open();
    while(1) {
        ZipStream zip = createZipStream();
        if(!zip->open()) {
            printf("---[ZipStream Test {open()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ZipStream Test {open()} case2] [Success]--- \n");
        break;
    }

    //void close();
    while(1) {
        ZipStream zip = createZipStream();
        zip->close();
        printf("---[ZipStream Test {close()} case1] [Success]--- \n");
        break;
    }

    //int compress(String src,String dest);
    while(1) {

    }

    /*

    int compress(String src,String dest);

    int compressWithPassword(String src,String dest,String password);

    int uncompress(String src);

    int uncompress(String src,String dest);

    int uncompressWithPassword(String src,String dest,String password);
    */

#if 0
    ZipStream unzip = createZipStream();
    unzip->uncompressWithPassword("abc.zip","/home/dsd/mysource/Obotcha/test/testZipInputStream/tt1","abcde");
#endif
}
