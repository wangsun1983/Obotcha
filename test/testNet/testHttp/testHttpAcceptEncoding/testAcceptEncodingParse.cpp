#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAcceptEncoding.hpp"

using namespace obotcha;

void testEncodingParse() {
  while(1) {
    HttpAcceptEncoding encoding1 = createHttpAcceptEncoding();
    encoding1->import("gzip, compress, br");
    auto encodings = encoding1->getEncodings();
    if(encodings->size() != 3) {
      printf("---[HttpAcceptEncoding test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!encodings->get(0)->type->equals("gzip")
      || !encodings->get(1)->type->equals("compress")
      || !encodings->get(2)->type->equals("br")) {
        printf("---[HttpAcceptEncoding test Parse case2] [FAILED]--- \n");
        break;
    }
    break;
  }

  while(1) {
    HttpAcceptEncoding encoding1 = createHttpAcceptEncoding();
    encoding1->import("deflate, gzip;q=1.0, *;q=0.5");
    auto encodings = encoding1->getEncodings();
    if(encodings->size() != 3) {
      printf("---[HttpAcceptEncoding test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!encodings->get(0)->type->equals("deflate")
      || !encodings->get(1)->type->equals("gzip")
      || !encodings->get(2)->type->equals("*")) {
        printf("---[HttpAcceptEncoding test Parse case4] [FAILED]--- \n");
        break;
    }

    if(encodings->get(1)->weight != 1.0) {
      printf("---[HttpAcceptEncoding test Parse case5] [FAILED]--- ,weight is %f\n",encodings->get(1)->weight);
      break;
    }

    if(encodings->get(2)->weight != 0.5) {
      printf("---[HttpAcceptEncoding test Parse case6] [FAILED]--- ,weight is %f\n",encodings->get(2)->weight);
      break;
    }
    break;
  }

  printf("---[HttpAcceptEncoding test Parse case100] [OK]--- \n");

}
