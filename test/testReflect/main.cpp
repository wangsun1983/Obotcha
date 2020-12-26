#include <stdio.h>

extern int testReflectFieldRead();
extern int testReflectFieldWrite();
extern int testReflectComplexFieldRead();
extern int testReflectComplexFieldWrite();
extern int testReflectToJson();
extern int testReflectArrayListFieldRead();

int main() {
  //testReflectFieldRead();
  //testReflectFieldWrite();
  //testReflectComplexFieldRead();
  //testReflectComplexFieldWrite();
  //testReflectToJson();
  testReflectArrayListFieldRead();
}
