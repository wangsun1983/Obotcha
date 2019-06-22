#include <stdio.h>
#include "Crc32.hpp"

using namespace obotcha;

int main() {

    printf("---[TestCrc32 Test Start]--- \n");
    //testfile.data crc32 result is 82269724

    //long decode(File);
    while(1) {
    	File f = createFile("testData.file");
        Crc32 cc = createCrc32();
        long v = cc->decode(f);
        printf("v is %ld \n",v);
        if(v != 82269724) {
        	printf("---[TestCrc32 Test {decode(File)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestCrc32 Test {decode(File)} case2] [Success]--- \n");
        break;
    }
    
    

}
