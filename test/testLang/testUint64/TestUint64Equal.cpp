#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint64.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "Uint64.hpp"

using namespace obotcha;

int equaltest() {

  while(1) {
      Uint64 v1 = createUint64(10);
      Uint64 v2 = createUint64(10);
      if(v1 != v2){
          printf("Uint64 equal test1-------[FAIL] \n");
          break;
      }

      Uint64 v3 = createUint64(10);
      Uint64 v4 = createUint64(11);
      if(v3 == v4){
          printf("Uint64 equal test2-------[FAIL] \n");
          break;
      }

      printf("Uint64 equal test3-------[OK] \n");
      break;
  }



}
