#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "LruCache.hpp"

using namespace obotcha;

extern int testLruAdd();
extern int testLruRemove();
extern int testLruUpdate();

int main() {
  testLruAdd();
  testLruRemove();
  testLruUpdate();
}
