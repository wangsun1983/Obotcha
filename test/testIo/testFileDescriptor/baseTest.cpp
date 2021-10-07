#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "FileDescriptor.hpp"

using namespace obotcha;

void baseTest() {
    //isClosed
    while(1) {
      int fd = open("./tmp/base_data",O_RDONLY);
      FileDescriptor descripor = createFileDescriptor(fd);

      if(descripor->isClosed()) {
        printf("---[FileDescriptor isClosed Test case1] [FAILED]--- \n");
      }
      close(fd);

      if(!descripor->isClosed()) {
        printf("---[FileDescriptor isClosed Test case2] [FAILED]--- \n");
      }
      break;
    }

    //isAsync
    while(1) {
      int fd = open("./tmp/base_data",O_RDONLY);
      FileDescriptor descripor = createFileDescriptor(fd);

      if(descripor->isAsync()) {
        printf("---[FileDescriptor isClosed Test case3] [FAILED]--- \n");
      }

      descripor->setAsync(false);

      if(descripor->isAsync()) {
        printf("---[FileDescriptor isClosed Test case4] [FAILED]--- \n");
      }

      descripor->setAsync(true);
      if(!descripor->isAsync()) {
        printf("---[FileDescriptor isClosed Test case5] [FAILED]--- \n");
      }

      close(fd);
      break;
    }

    //hashcode
    while(1) {
      int fd = open("./tmp/base_data",O_RDONLY);
      FileDescriptor descripor = createFileDescriptor(fd);
      if(descripor->hashcode() != fd) {
        printf("---[FileDescriptor isClosed Test case6] [FAILED]--- \n");
      }
      close(fd);
      break;
    }

    printf("---[FileDescriptor isClosed Test case100] [OK]--- \n");
}
