#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoLock.hpp"
#include "Integer.hpp"

using namespace obotcha;

extern void testConditionWait();
extern void testConditionNotify();
extern void testConditionNotifyAll();
extern void testConditionDoubleLock();

int main() {
  testConditionDoubleLock();
  testConditionWait();
  testConditionNotify();
  testConditionNotifyAll();
  return 0;
}
