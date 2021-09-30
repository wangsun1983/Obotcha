#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"

using namespace obotcha;

void fileoutput_close_test() {

    while(1) {
        File file = createFile("./tmp/output_close_test.txt");
        file->createNewFile();

        int fd = open("./tmp/output_close_test.txt",O_WRONLY);
        {
          FileOutputStream stream = createFileOutputStream(fd);
        }

        byte buf[2] = {0x1,0x2};
        int len = write(fd,buf,2);
        if(len != 2) {
          printf("---[TestFileOutputStream Test close case1] [FAILED]--- ,len is %d\n",len);
          break;
        }

        close(fd);
        break;
    }

    while(1) {
        File file = createFile("./tmp/output_close_test.txt");
        file->createNewFile();

        int fd = open("./tmp/output_close_test.txt",O_RDONLY);
        FileOutputStream stream = createFileOutputStream(fd);
        stream->close();

        byte buf[2] = {0x1,0x2};
        int len = write(fd,buf,2);
        if(len != -1) {
          printf("---[TestFileOutputStream Test close case2] [FAILED]--- \n");
          break;
        }

        close(fd);
        break;
    }

    printf("---[TestFileOutputStream Test close case3] [OK]--- \n");
}
