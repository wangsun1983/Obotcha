#include <stdio.h>

extern void testReflectArrayListFieldWrite();
extern void testReflectFieldRead();
extern void testReflectFieldWrite();
extern void testReflectComplexFieldRead();
extern void testReflectComplexFieldWrite();
extern void testReflectToJson();
extern void testReflectArrayListFieldRead();
extern void testReflectToSimpleJson();
extern void testReflectToArrayJson();
extern void testReflectToSimpleArrayJson();
extern void testReflectNumber();
extern void testReflectHashMapFieldWrite();
extern void testReflectArrayList2();
extern void testReflectMap2();
extern void testReflectArrayHashmap();
extern void testReflectToXml();
extern void testReflectArrayListToXml();
extern void testReflectHashMapXml2();

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
  testReflectHashMapFieldWrite();
  testReflectArrayList2();
  testReflectMap2();
  testReflectArrayHashmap();
  testReflectArrayListFieldWrite();
  testReflectToXml();
  testReflectArrayListToXml();
  testReflectHashMapXml2();
  return 0;
}
