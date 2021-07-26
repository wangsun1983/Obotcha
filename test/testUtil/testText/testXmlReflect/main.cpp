#include <stdio.h>

extern int testReflectToSimpleXml();
extern int testReflectToArrayXml();
extern int testReflectToSimpleArrayXml();
extern int testReflectNumber();

int main() {
  testReflectNumber();
  testReflectToArrayXml();
  testReflectToSimpleArrayXml();
  testReflectToSimpleXml();
}
