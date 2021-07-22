#include <stdio.h>

extern int testReflectFieldRead();
extern int testReflectFieldWrite();
extern int testReflectComplexFieldRead();
extern int testReflectComplexFieldWrite();
extern int testReflectToJson();
extern int testReflectArrayListFieldRead();
extern int testReflectArrayListFieldWrite();
extern int testReflectToSimpleJson();
extern int testReflectToArrayJson();
extern int testReflectToSimpleArrayJson();
extern int testReflectNumber();
extern int testReflectHashMapFieldWrite();
extern int testReflectToXml();

int main() {
/*  
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
*/ 
  testReflectHashMapFieldWrite();
}
