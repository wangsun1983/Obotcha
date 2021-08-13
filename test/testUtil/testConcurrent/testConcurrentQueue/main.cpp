#include <stdio.h>
#include <unistd.h>

#include "ConcurrentQueue.hpp"

extern void testConcurrentQueue_Size();
extern void testConcurrentQueue_Add();
extern void testConcurrentQueue_Get();
extern void testConcurrentQueue_ToArray();
extern void testConcurrentQueue_PutFirst();
extern void testConcurrentQueue_PutLast();
extern void testConcurrentQueue_Remove();
extern void testConcurrentQueue_TakeFirst();
extern void testConcurrentQueue_TakeLast();
extern void testConcurrentQueue_Clear();
extern void testConcurrentQueue_MultiThread_Case1();
extern void testConcurrentQueue_MultiThread_Case2();

using namespace obotcha;

int main() {
  testConcurrentQueue_Size();
  testConcurrentQueue_Add();
  testConcurrentQueue_Get();
  testConcurrentQueue_ToArray();
  testConcurrentQueue_PutFirst();
  testConcurrentQueue_PutLast();
  testConcurrentQueue_Remove();
  testConcurrentQueue_TakeFirst();
  testConcurrentQueue_TakeLast();
  testConcurrentQueue_Clear();
  testConcurrentQueue_MultiThread_Case1();
  testConcurrentQueue_MultiThread_Case2();
  return 0;
}
