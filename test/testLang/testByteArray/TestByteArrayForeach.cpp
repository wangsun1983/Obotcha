#include "ByteArray.hpp"

using namespace obotcha;

int testForeach() {
  ByteArray array = createByteArray(10);
  for(int i = 0;i <10;i++) {
    array[i] = i;
  }

  int index = 0;
  array->foreach([&index](byte d) {
    if(d != index) {
      printf("ByteArray Lambda test 1-------[FAIL] \n");
      return -1;
    }
    index++;
    return 1;
  });

  printf("ByteArray Lambda test 1-------[OK] \n");

}
