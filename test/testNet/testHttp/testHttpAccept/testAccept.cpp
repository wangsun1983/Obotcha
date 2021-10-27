#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"

using namespace obotcha;

void testEncodingParse() {
  while(1) {
    HttpAccept encoding1 = createHttpAccept();
    encoding1->import("text/html");
    auto encodings = encoding1->getAccepts();
    if(encodings->size() != 1) {
      printf("---[HttpAccept test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!encodings->get(0)->type->equals("text/html")) {
        printf("---[HttpAccept test Parse case2] [FAILED]--- \n");
        break;
    }
    break;
  }

  while(1) {
    HttpAccept encoding1 = createHttpAccept();
    encoding1->import("image/*");
    auto encodings = encoding1->getAccepts();
    if(encodings->size() != 1) {
      printf("---[HttpAccept test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!encodings->get(0)->type->equals("image/*")) {
        printf("---[HttpAccept test Parse case4] [FAILED]--- \n");
        break;
    }

    break;
  }

  while(1) {
    HttpAccept encoding1 = createHttpAccept();
    encoding1->import("text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8");
    auto encodings = encoding1->getAccepts();
    if(encodings->size() != 4) {
      printf("---[HttpAccept test Parse case5] [FAILED]--- \n");
      break;
    }

    if(!encodings->get(0)->type->equals("text/html")
      ||!encodings->get(1)->type->equals("application/xhtml+xml")
      ||!encodings->get(2)->type->equals("application/xml")
      ||!encodings->get(3)->type->equals("*/*")) {
        printf("---[HttpAccept test Parse case6] [FAILED]--- \n");
        break;
    }

    if(st(Math)::compareFloat(encodings->get(2)->weight,0.9) != st(Math)::AlmostEqual) {
      printf("---[HttpAccept test Parse case5] [FAILED]--- ,weight is %f\n",encodings->get(2)->weight);
      break;
    }

    if(st(Math)::compareFloat(encodings->get(3)->weight,0.8) != st(Math)::AlmostEqual) {
      printf("---[HttpAccept test Parse case5] [FAILED]--- ,weight is %f\n",encodings->get(3)->weight);
      break;
    }
    break;
  }

  printf("---[HttpAccept test Parse case100] [OK]--- \n");

}
