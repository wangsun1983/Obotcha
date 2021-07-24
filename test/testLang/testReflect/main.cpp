#include <stdio.h>

extern int testReflectArrayListFieldWrite();
extern int testReflectFieldRead();
extern int testReflectFieldWrite();
extern int testReflectComplexFieldRead();
extern int testReflectComplexFieldWrite();
extern int testReflectToJson();
extern int testReflectArrayListFieldRead();
extern int testReflectToSimpleJson();
extern int testReflectToArrayJson();
extern int testReflectToSimpleArrayJson();
extern int testReflectNumber();
extern int testReflectHashMapFieldWrite();
extern int testReflectToXml();
extern int testReflectArrayList2();
extern int testReflectMap2();
extern int testReflectArrayHashmap();


int main() {

  testReflectFieldRead();
  testReflectFieldWrite();
  testReflectComplexFieldRead();
  testReflectComplexFieldWrite();
  testReflectToJson();
  testReflectArrayListFieldRead();
  testReflectArrayListFieldWrite();
  testReflectToSimpleJson();
  testReflectToArrayJson();
  testReflectToSimpleArrayJson();
  testReflectNumber();
  testReflectHashMapFieldWrite();
  testReflectToXml();
  testReflectHashMapFieldWrite();
  testReflectArrayList2();
  testReflectMap2();
  testReflectArrayHashmap();

  testReflectArrayListFieldWrite();
  return 0;
}
