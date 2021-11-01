#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderMatch.hpp"
#include "Math.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderMatch match = createHttpHeaderMatch();
    match->import("\"bfc13a64729c4290ef5b2c2730249c88ca92d82d\"");
    ArrayList<HttpHeaderMatchItem> list = match->get();
    if(list->size() != 1){
      printf("---[HttpHeaderMatch test parse case1] [FAILED]--- \n");
      break;
    }

    auto item = list->get(0);
    if(item == nullptr || !item->tag->equals("bfc13a64729c4290ef5b2c2730249c88ca92d82d")) {
      printf("---[HttpHeaderMatch test parse case2] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpHeaderMatch match = createHttpHeaderMatch();
    match->import("W/\"67ab43\", \"54ed21\", \"7892dd\"");
    ArrayList<HttpHeaderMatchItem> list = match->get();
    if(list->size() != 3){
      printf("---[HttpHeaderMatch test parse case3] [FAILED]--- \n");
      break;
    }

    auto item = list->get(0);
    if(item == nullptr || !item->tag->equals("67ab43") || !item->isWeakAlg) {
      printf("---[HttpHeaderMatch test parse case4] [FAILED]--- \n");
    }

    item = list->get(1);
    if(item == nullptr || !item->tag->equals("54ed21") || item->isWeakAlg) {
      printf("---[HttpHeaderMatch test parse case5] [FAILED]--- \n");
    }

    item = list->get(2);
    if(item == nullptr || !item->tag->equals("7892dd") || item->isWeakAlg) {
      printf("---[HttpHeaderMatch test parse case6] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpHeaderMatch match = createHttpHeaderMatch();
    match->import("*");
    ArrayList<HttpHeaderMatchItem> list = match->get();
    if(list->size() != 1){
      printf("---[HttpHeaderMatch test parse case7] [FAILED]--- \n");
      break;
    }

    auto item = list->get(0);
    if(item == nullptr || !item->tag->equals("*") || item->isWeakAlg) {
      printf("---[HttpHeaderMatch test parse case8] [FAILED]--- \n");
    }

    break;
  }

  printf("---[HttpHeaderMatch test Parse case100] [OK]--- \n");
}
