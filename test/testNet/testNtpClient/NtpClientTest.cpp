#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "NtpClient.hpp"
#include "System.hpp"

using namespace obotcha;

int main() {
    printf("wangsl trace1 \n");
    NtpClient c = createNtpClient();
    c->bind("ntp.aliyun.com",123);
    long int t = c->get();
    printf("t is %ld \n",t);
    printf("current is %ld \n",st(System)::currentTimeMillis());
    while(1){}

}
