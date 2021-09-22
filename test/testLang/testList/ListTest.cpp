#include <stdio.h>
#include <unistd.h>
#include <vector>
//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "Uint8.hpp"
#include "List.hpp"

using namespace std;
using namespace obotcha;

extern void listobjecttest();
extern void basetest();
extern void testConstruct();
extern void testExceptoin();
extern void testListValueUpdate();

int main() {
  listobjecttest();
  basetest();
  testConstruct();
  testExceptoin();
  testListValueUpdate();
  return 0;
}
