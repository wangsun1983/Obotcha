#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

using namespace obotcha;


void testByteArrayStringConvert() {
  while(1) {
    String str = createString("abc test");
    ByteArray array = str->toByteArray();

    String v = array->toString();
    //printf("v is %s \n",v->toChars());
    if(!v->equals(str)) {
      printf("ByteArray  ByteArray String Convert test 1-------[FAILED] \n");
    }
    break;
  }

  printf("ByteArray  ByteArray String Convert test 100-------[OK] \n");
}
