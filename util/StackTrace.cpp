#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <sys/types.h>  
#include <sys/stat.h>
#include <fcntl.h>

#include "StackTrace.hpp"

namespace obotcha {

/*
Example:
../../out/lib/libobotcha.so(_ZN7obotcha10_Exception10printStackEv+0xf4) [0x7f8509e031f8]
./mytest(main+0x2c4) [0x559c87affb7e]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7) [0x7f850908ab97]
./mytest(_start+0x2a) [0x559c87aff7da]

Method 1:
-------------------------------------------------------------
Step 1:
    readelf -a libobotcha.so,[readelf -a ../../out/lib/libobotcha.so |grep -i _ZN7obotcha10_Exception10]
    5932: 00000000004080f2    17 FUNC    GLOBAL DEFAULT   12 _ZN7obotcha10_Exception10
    6129: 00000000004080c4    45 FUNC    GLOBAL DEFAULT   12 _ZN7obotcha10_Exception10
    14073: 0000000000408104   400 FUNC    GLOBAL DEFAULT   12 _ZN7obotcha10_Exception10
    14859: 0000000000408104   400 FUNC    GLOBAL DEFAULT   12 _ZN7obotcha10_Exception10
    20559: 00000000004080f2    17 FUNC    GLOBAL DEFAULT   12 _ZN7obotcha10_Exception10
    23095: 00000000004080c4    45 FUNC    GLOBAL DEFAULT   12 _ZN7obotcha10_Exception10

Step2:
    use c++filt to transalte _ZN7obotcha10_Exception10printStackEv->obotcha::_Exception::printStack()

Step4:
    use addr2line to find printStack()'s address
    addr2line -e ../../out/lib/libobotcha.so 00000000004080f2
    .....
    
    the right address is :0000000000408104
    error address is 0000000000408104 + f4 = 4081F8

Step5:
    addr2line -e ../../out/lib/libobotcha.so 4081F8
    /home/dji/mysource/Obotcha/lang/Exception.cpp:57 -> source file !!

Method 2:    
-------------------------------------------------------------
Step 1:
    find libobotcha.so's address:
    7f04cdc7b000-7f04ce41d000 r-xp 00000000 103:02 4086477   /home/dji/mysource/Obotcha/out/lib/libobotcha.so
    7f04ce41d000-7f04ce61d000 ---p 007a2000 103:02 4086477   /home/dji/mysource/Obotcha/out/lib/libobotcha.so
    7f04ce61d000-7f04ce658000 r--p 007a2000 103:02 4086477   /home/dji/mysource/Obotcha/out/lib/libobotcha.so

    so libobotacha.so's start address is 7f04cdc7b000

Step 2:
    calculate error address :
    -----------------[stack dump start]-------------- 
    ../../out/lib/libobotcha.so(_ZN7obotcha10_Exception10printStackEv+0xf4) [0x7f04ce0831f8]
    ./mytest(main+0x2c4) [0x556cefda5b7e]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7) [0x7f04cd30ab97]
    ./mytest(_start+0x2a) [0x556cefda57da]
    -----------------[stack dump end]--------------- 


    ../../out/lib/libobotcha.so(_ZN7obotcha10_Exception10printStackEv+0xf4) [0x7f8509e031f8]
    0x7f8509e031f8 - 7f04cdc7b000 = 4081F8

Step2:
    addr2line -e ../../out/lib/libobotcha.so 4081F8
    /home/dji/mysource/Obotcha/lang/Exception.cpp:57 -> source file !!     
*/

void _StackTrace::dumpStack(String tag) {

    printf("PROCESS MAPS: \n");
    const char *path = "/proc/self/maps";
    int fd = open(path,O_RDONLY);
    if(fd >=0) {
        char buff[1024*256];
        read(fd,buff,1024*256);
        close(fd);
        printf("%s \n",&buff[0]);
    }

    printf("PROCESS TRACE: \n");
    printf("Dump %s trace: \n",tag->toChars());
    int size = 16;
    void * array[16];
    int stack_num = backtrace(array, size);
    char ** stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i) {
        printf("%s\n", stacktrace[i]);
    }
    free(stacktrace);
}

}


