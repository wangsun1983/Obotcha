#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

using namespace obotcha;

int testHttpCookieParser() {
  //aa=bb;expires= Sun, 29 Apr 2018 07:00:00 GMT ;path=/
  //while(1) {
	  HttpCookie cookie = createHttpCookie();
	  cookie->import(createString("aa=bb;expires= Sun, 29 Apr 2018 07:00:00 GMT ;path=/"));
	  printf("cookie->date is %s \n",cookie->getPropertyExpires()->toString()->toChars());
  //}
}
