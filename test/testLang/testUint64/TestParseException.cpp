#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint64.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void TestParseException() {
  Uint64 data = st(Uint64)::parseDecUint64("0x12");
  if(data != nullptr) {
    printf("Uint64 Parse Exception test1-------[FAIL] \n");
  }

  printf("Uint64 Parse Exception test100-------[OK] \n");
  return;
}
