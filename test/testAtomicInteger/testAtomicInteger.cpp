#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "AtomicInteger.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "UUID.hpp"
#include "Log.hpp"
#include "ZipStream.hpp"

using namespace obotcha;

int main() {
    AtomicInteger atomic = createAtomicInteger(100);
    int v = atomic->incrementAndGet();
    printf("v is %d \n",v);

    int v1 = atomic->incrementAndGet();
    printf("v1 is %d \n",v1);

    int v2 = atomic->getAndIncrement();
    printf("v2 is %d \n",v2);    
}
