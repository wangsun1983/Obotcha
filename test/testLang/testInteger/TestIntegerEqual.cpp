#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int equaltest() {

  while(1) {
      Integer v1 = createInteger(10);
      Integer v2 = createInteger(10);
      if(v1 != v2){
          printf("Integer equal test1-------[FAIL] \n");
          break;
      }

      Integer v3 = createInteger(10);
      Integer v4 = createInteger(11);
      if(v3 == v4){
          printf("Integer equal test2-------[FAIL] \n");
          break;
      }

      printf("Integer equal test3-------[OK] \n");
      break;
  }



}
