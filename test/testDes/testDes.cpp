#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Des.hpp"

using namespace obotcha;

int main() {
    Des des = createDes();
    //des->genKey("abc_key");
    des->loadKey("abc_key");

    //des->encrypt("test_data.file","encrypt.file");
    des->decrypt("encrypt.file","dencrypt.file");

}
