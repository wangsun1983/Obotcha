#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"

using namespace obotcha;

extern void fileoutput_trunc_test();
extern void fileoutput_append_test();
extern void fileoutput_base_test();
extern void fileoutput_close_test();

int main() {
    //create a base test
#if 0
    int fd = open("./tmp/abc.txt",O_CREAT | O_RDWR | O_APPEND,
                    S_IRUSR | S_IWUSR);

    for(int i = 0;i < 1024;i++) {
      for(int j = 0;j<255;j++) {
        write(fd,&j,sizeof(j));
      }
    }
    close(fd);
#endif

    fileoutput_base_test();
    fileoutput_trunc_test();
    fileoutput_append_test();
    fileoutput_close_test();
}
