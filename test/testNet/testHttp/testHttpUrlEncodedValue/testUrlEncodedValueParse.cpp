#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpUrlEncodedValue.hpp"

using namespace obotcha;

void testUrlEncodedValueParse() {
  while(1) {
    HttpUrlEncodedValue v = createHttpUrlEncodedValue("abc=1&bbb=qq&ccc=ffds");
    auto list = v->getValues();
    KeyValuePair<String,String> l0 = list->get(0);
    if(!l0->getKey()->equals("abc")) {
      printf("---[HttpUrlEncodedValue test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!l0->getValue()->equals("1")) {
      printf("---[HttpUrlEncodedValue test Parse case2] [FAILED]--- \n");
      break;
    }

    KeyValuePair<String,String> l1 = list->get(1);
    if(!l1->getKey()->equals("bbb")) {
      printf("---[HttpUrlEncodedValue test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!l1->getValue()->equals("qq")) {
      printf("---[HttpUrlEncodedValue test Parse case4] [FAILED]--- \n");
      break;
    }

    KeyValuePair<String,String> l2 = list->get(2);
    if(!l2->getKey()->equals("ccc")) {
      printf("---[HttpUrlEncodedValue test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!l2->getValue()->equals("ffds")) {
      printf("---[HttpUrlEncodedValue test Parse case5] [FAILED]--- \n");
      break;
    }

    break;
  }

  printf("---[HttpUrlEncodedValue test Parse case100] [OK]--- \n");

}
