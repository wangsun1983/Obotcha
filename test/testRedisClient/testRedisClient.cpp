#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "AtomicInteger.hpp"
#include "StrongPointer.hpp"
#include "RedisClient.hpp"

using namespace obotcha;

int main() {
    RedisClient client = createRedisClient();
    client->connect(createString("127.0.0.1"),6379,100);
    int value1 = client->set(createString("tag1"),createString("haha"));
    String value2 = client->getValue(createString("tag1"));
    printf("value2 is %s \n",value2->toChars());
}
