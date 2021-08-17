#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"

using namespace obotcha;

extern void testEnqueueDequeue();
extern void testMultiThreadQueue();
extern void testBlockingLinkedListInt();
extern void testBlockingLinkedListDestroy();
extern void testBlockingLinkedListPeekFirst();
extern void testBlockingLinkedListPeekLast();
extern void testBlockingLinkedListToArray();
extern void testBlockingLinkedListPutLast();
extern void testBlockingLinkedListPutFirst();
extern void testBlockingLinkedListTakeFirst();
extern void testBlockingLinkedListTakeLast();
extern void testBlockingLinkedListTryPutFirst();
extern void testBlockingLinkedListTryPutLast();
extern void testBlockingLinkedListTryTakeFirst();
extern void testBlockingLinkedListTryTakeLast();
extern void testBlockingLinkedListUnlimited();
extern void testBlockingLinkedListClear();
extern void testBlockingLinkedListRemove();
extern void testBlockingLinkedListRemoveAt();
extern void testBlockingLinkedListInt();
extern void testBlockingLinkedListForeach();

int main() {
    testBlockingLinkedListForeach();
    testBlockingLinkedListInt();
    testEnqueueDequeue();
    testMultiThreadQueue();
    testBlockingLinkedListInt();
    testBlockingLinkedListDestroy();
    testBlockingLinkedListPeekFirst();
    testBlockingLinkedListPeekLast();
    testBlockingLinkedListToArray();
    testBlockingLinkedListPutLast();
    testBlockingLinkedListPutFirst();
    testBlockingLinkedListTakeFirst();
    testBlockingLinkedListTakeLast();
    testBlockingLinkedListTryPutFirst();
    testBlockingLinkedListTryPutLast();
    testBlockingLinkedListTryTakeFirst();
    testBlockingLinkedListTryTakeLast();
    testBlockingLinkedListUnlimited();
    testBlockingLinkedListClear();
    testBlockingLinkedListRemove();
    testBlockingLinkedListRemoveAt();
    return 0;
}
