#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpUrlEncodedValue.hpp"

using namespace obotcha;

void testUrlEncodedValueToString() {
  while(1) {
    //abc=1&bbb=qq&ccc=ffds
    HttpUrlEncodedValue v = createHttpUrlEncodedValue();
    v->set("abc","1");
    v->set("bbb","qq");
    v->set("ccc","ffds");
    if(!v->toString()->equals("abc=1&bbb=qq&ccc=ffds")) {
      printf("---[HttpUrlEncodedValue test toString case1] [FAILED]--- v is %s\n",v->toString()->toChars());
    }
    break;
  }

  printf("---[HttpUrlEncodedValue test toString case100] [OK]--- \n");

}
