#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Des.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {
    Des des = createDes(DesTypeCBC);
    //des->genKey("abc_key");
    des->loadKey("abc_key");
    String abc = createString("hello world \n");
    String abc2 = createString("myabc is efg");
    ByteArray arrAbc2 = createByteArray(abc2);
    char *q = arrAbc2->toValue();
    printf("q is %s \n",q);

    ByteArray ret = des->encrypt(createByteArray(abc));
    ByteArray ret2 = des->decrypt(ret);
    char *p = ret2->toValue();
    printf("value is %s \n",p);
    des->encrypt("test_data.file","encrypt.file");
    printf("file trace1 \n");
    des->decrypt("encrypt.file","dencrypt.file");
    printf("file trace2 \n");

}
