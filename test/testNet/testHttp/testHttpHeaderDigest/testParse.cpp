#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderDigest.hpp"
#include "Math.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderDigest digest = createHttpHeaderDigest();
    digest->import(" sha-256=X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=");
    ArrayList<HttpHeaderDigestItem> list = digest->getDigests();
    if(list->size() != 1) {
      printf("---[HttpHeaderDigest test Parse case1] [FAILED]--- \n");
      break;
    }

    auto item = list->get(0);
    if(!item->algorithm->equals("sha-256") || !item->value->equals("X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=")) {
      printf("---[HttpHeaderDigest test Parse case2] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    HttpHeaderDigest digest = createHttpHeaderDigest();
    digest->import(" sha-256=X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=,unixsum=30637 ");
    ArrayList<HttpHeaderDigestItem> list = digest->getDigests();
    if(list->size() != 2) {
      printf("---[HttpHeaderDigest test Parse case1] [FAILED]--- \n");
      break;
    }

    auto item = list->get(0);
    if(!item->algorithm->equals("sha-256") || !item->value->equals("X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=")) {
      printf("---[HttpHeaderDigest test Parse case2] [FAILED]--- \n");
      break;
    }

    item = list->get(1);
    if(!item->algorithm->equals("unixsum") || !item->value->equals("30637")) {
      printf("---[HttpHeaderDigest test Parse case2] [FAILED]--- \n");
      break;
    }

    break;
  }
  
  printf("---[HttpHeaderDigest test Parse case100] [OK]--- \n");
}
