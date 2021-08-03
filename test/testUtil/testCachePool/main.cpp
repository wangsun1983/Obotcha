#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "FifoPipe.hpp"
#include "CachePool.hpp"

using namespace obotcha;
extern int TestConstruct();
extern int TestEnqueue();
extern int TestDequeue();

int main() {
  TestConstruct();
  TestEnqueue();
  TestDequeue();
}
