#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAcceptCharSet.hpp"
#include "Math.hpp"

using namespace obotcha;

void testCharSetParse() {
  while(1) {
    HttpAcceptCharSet charset = createHttpAcceptCharSet();
    charset->import("iso-8859-1");
    ArrayList<HttpAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 1) {
      printf("---[HttpAcceptCharSet test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!charsets->get(0)->type->equals("iso-8859-1")) {
        printf("---[HttpAcceptCharSet test Parse case2] [FAILED]--- \n");
        break;
    }
    break;
  }

  while(1) {
    HttpAcceptCharSet charset = createHttpAcceptCharSet();
    charset->import("utf-8, iso-8859-1;q=0.5");
    ArrayList<HttpAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 2) {
      printf("---[HttpAcceptCharSet test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!charsets->get(0)->type->equals("utf-8")) {
        printf("---[HttpAcceptCharSet test Parse case4] [FAILED]--- \n");
        break;
    }

    if(!charsets->get(1)->type->equals("iso-8859-1")) {
        printf("---[HttpAcceptCharSet test Parse case5] [FAILED]--- \n");
        break;
    }

    if(charsets->get(1)->weight != 0.5) {
        printf("---[HttpAcceptCharSet test Parse case6] [FAILED]--- \n");
        break;
    }
    break;
  }

  while(1) {
    HttpAcceptCharSet charset = createHttpAcceptCharSet();
    charset->import("utf-8, iso-8859-1;q=0.5, *;q=0.1");
    ArrayList<HttpAcceptCharSetItem> charsets = charset->get();
    if(charsets->size() != 3) {
      printf("---[HttpAcceptCharSet test Parse case7] [FAILED]--- \n");
      break;
    }

    if(!charsets->get(0)->type->equals("utf-8")) {
        printf("---[HttpAcceptCharSet test Parse case8] [FAILED]--- \n");
        break;
    }

    if(!charsets->get(1)->type->equals("iso-8859-1")) {
        printf("---[HttpAcceptCharSet test Parse case9] [FAILED]--- \n");
        break;
    }

    if(charsets->get(1)->weight != 0.5) {
        printf("---[HttpAcceptCharSet test Parse case10] [FAILED]--- \n");
        break;
    }

    if(!charsets->get(2)->type->equals("*")) {
        printf("---[HttpAcceptCharSet test Parse case11] [FAILED]--- \n");
        break;
    }

    if(st(Math)::compareFloat(charsets->get(2)->weight,0.1) != st(Math)::AlmostEqual) {
        printf("---[HttpAcceptCharSet test Parse case12] [FAILED]---,weight is %f \n",charsets->get(2)->weight);
        break;
    }
    break;
  }

  printf("---[HttpAcceptCharSet test Parse case100] [OK]--- \n");

}
