#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Integer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "System.hpp"

using namespace obotcha;

extern void testReadLock_Lock();
extern void testWriteLock_Lock();
extern void testReadWriteLock_Lock();

int main() {
  testReadLock_Lock();
  testWriteLock_Lock();
  testReadWriteLock_Lock();
  return 1;
}
