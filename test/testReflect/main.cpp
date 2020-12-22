#include <stdio.h>

extern int testReflectFieldRead();
extern int testReflectFieldWrite();
int main() {
  testReflectFieldRead();
  testReflectFieldWrite();
}
