#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAllow.hpp"
#include "HttpCacheControl.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpCacheControl c = createHttpCacheControl();
    c->import("no-transform,only-if-cached,must-revalidate,public,no-cache, no-store, must-revalidate");
    if(!c->noCache()) {
      printf("---[HttpCacheControl test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!c->noStore()) {
      printf("---[HttpCacheControl test Parse case2] [FAILED]--- \n");
      break;
    }

    if(c->isPrivate()) {
      printf("---[HttpCacheControl test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!c->isPublic()) {
      printf("---[HttpCacheControl test Parse case4] [FAILED]--- \n");
      break;
    }

    if(!c->mustRevalidate()) {
      printf("---[HttpCacheControl test Parse case5] [FAILED]--- \n");
      break;
    }

    if(!c->onlyIfCached()) {
      printf("---[HttpCacheControl test Parse case6] [FAILED]--- \n");
      break;
    }

    if(!c->noTransform()) {
      printf("---[HttpCacheControl test Parse case7] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpCacheControl c = createHttpCacheControl();
    c->import("no-transform,only-if-cached,must-revalidate,private,no-cache, no-store, must-revalidate");
    if(!c->noCache()) {
      printf("---[HttpCacheControl test Parse case8] [FAILED]--- \n");
      break;
    }

    if(!c->noStore()) {
      printf("---[HttpCacheControl test Parse case9] [FAILED]--- \n");
      break;
    }

    if(!c->isPrivate()) {
      printf("---[HttpCacheControl test Parse case10] [FAILED]--- \n");
      break;
    }

    if(c->isPublic()) {
      printf("---[HttpCacheControl test Parse case11] [FAILED]--- \n");
      break;
    }

    if(!c->mustRevalidate()) {
      printf("---[HttpCacheControl test Parse case12] [FAILED]--- \n");
      break;
    }

    if(!c->onlyIfCached()) {
      printf("---[HttpCacheControl test Parse case13] [FAILED]--- \n");
      break;
    }

    if(!c->noTransform()) {
      printf("---[HttpCacheControl test Parse case14] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpCacheControl c = createHttpCacheControl();
    c->import("max-age=31536000,max-stale=123,min-fresh=333,s-maxage=90");
    if(c->maxAgeSeconds() != 31536000) {
      printf("---[HttpCacheControl test Parse case15] [FAILED]--- \n");
      break;
    }

    if(c->sMaxAgeSeconds() != 90) {
      printf("---[HttpCacheControl test Parse case16] [FAILED]--- \n");
      break;
    }

    if(c->minFreshSeconds() != 333) {
      printf("---[HttpCacheControl test Parse case17] [FAILED]--- \n");
      break;
    }

    if(c->maxStaleSeconds() != 123) {
      printf("---[HttpCacheControl test Parse case18] [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---[HttpCacheControl test Parse case100] [OK]--- \n");

}
