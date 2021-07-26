#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int TestParseException() {
  Uint16 data = st(Uint16)::parseDecUint16("0x12");
  if(data != nullptr) {
    printf("Uint16 Parse Exception test1-------[FAIL] \n");
  }

  printf("Uint16 Parse Exception test100-------[OK] \n");
  return 0;
}
