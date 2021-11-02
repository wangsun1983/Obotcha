#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderRetryAfter.hpp"
#include "Math.hpp"
#include "Calendar.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderRetryAfter retryAfter = createHttpHeaderRetryAfter();
    retryAfter->import(" Thu, 21 Oct 2021 07:28:00 GMT ");
    auto date = retryAfter->getDate()->toDateTime();
    if(date->year() != 2021) {
      printf("---[HttpHeaderRetryAfter test Parse case1] [FAILED]--- \n");
    }

    if(date->month() != st(Calendar)::October) {
      printf("---[HttpHeaderRetryAfter test Parse case2] [FAILED]--- \n");
    }

    if(date->dayOfMonth() != 21) {
      printf("---[HttpHeaderRetryAfter test Parse case3] [FAILED]--- \n");
    }

    if(date->hour() != 7) {
      printf("---[HttpHeaderRetryAfter test Parse case4] [FAILED]--- \n");
    }

    if(date->minute() != 28) {
      printf("---[HttpHeaderRetryAfter test Parse case5] [FAILED]--- \n");
    }

    if(date->dayOfWeek() != st(Calendar)::Thursday) {
      printf("---[HttpHeaderRetryAfter test Parse case6] [FAILED]---,date->dayOfWeek() is %d \n",date->dayOfWeek());
    }
    break;
  }

  while(1) {
    HttpHeaderRetryAfter retryAfter = createHttpHeaderRetryAfter();
    retryAfter->import(" 120 ");
    if(retryAfter->getDelayInterval() != 120) {
      printf("---[HttpHeaderRetryAfter test Parse case7] [FAILED]--- \n");
    }
    break;
  }

  printf("---[HttpHeaderRetryAfter test Parse case100] [OK]--- \n");
}
