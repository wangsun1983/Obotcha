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

extern int listobjecttest();
extern int basetest();
extern int testConstruct();
extern int testExceptoin();
extern int testListValueUpdate();

int main() {
  listobjecttest();
  basetest();
  testConstruct();
  testExceptoin();
  testListValueUpdate();
}