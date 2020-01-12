#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

#define FILL_VALUE 1

bool checkRingBuff(ByteRingArray array) {
  for(int i = 0; i < 12;i++) {
    if(array->at(i) != i) {
      printf("error!!!! \n");
      return false;
    }
  }

  return true;
}

int main() {
  //test pop and push
  ByteRingArray mRingBuff = createByteRingArray(12);
  for(int i = 0;i<12;i++) {
    ByteArray b = createByteArray(1);
    b->toValue()[0] = i;
    mRingBuff->push(b);
  }

  checkRingBuff(mRingBuff);
}
