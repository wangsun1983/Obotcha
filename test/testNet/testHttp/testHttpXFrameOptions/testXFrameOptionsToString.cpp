#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpXFrameOptions.hpp"

using namespace obotcha;

void testXFrameOptionsToString() {
  while(1) {
    HttpXFrameOptions options = createHttpXFrameOptions();
    options->import("deny");
    if(!options->toString()->equals("deny")) {
      printf("---[HttpXFrameOptions test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpXFrameOptions options = createHttpXFrameOptions();
    options->import("sameorigin");
    if(!options->toString()->equals("sameorigin")) {
      printf("---[HttpXFrameOptions test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpXFrameOptions options = createHttpXFrameOptions();
    options->import("allow-from https://example.com/");
    if(!options->toString()->equals("allow-from https://example.com/")) {
      printf("---[HttpXFrameOptions test toString case3] [FAILED]--- \n");
      break;
    }

    break;
  }

  printf("---[HttpXFrameOptions test toString case100] [OK]--- \n");

}
