#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint32.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int TestParseException() {
  Uint32 data = st(Uint32)::parseDecUint32("0x12");
  if(data != nullptr) {
    printf("Uint32 Parse Exception test1-------[FAIL] \n");
  }

  printf("Uint32 Parse Exception test100-------[OK] \n");
  return 0;
}
