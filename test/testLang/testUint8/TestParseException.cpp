#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int TestParseException() {
  Uint8 data = st(Uint8)::parseDecUint8("0x12");
  if(data != nullptr) {
    printf("Uint8 Parse Exception test1-------[FAIL] \n");
  }

  printf("Uint8 Parse Exception test100-------[OK] \n");
  return 0;
}
