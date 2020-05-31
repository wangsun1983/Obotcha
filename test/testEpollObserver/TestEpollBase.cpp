#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "EPollFileObserver.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "TcpServer.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(BaseTestListener1) EXTENDS(EPollFileObserverListener) {
public:
    int onEvent(int fd,int events,ByteArray) {
        printf("receive fd \n");
    }
};

DECLARE_SIMPLE_CLASS(BaseTestServer1) IMPLEMENTS(Thread) {
public:
    void run() {
        struct sockaddr_in serverAddr;
        int sock = -1;
        int opt = 1;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_port = htons(1234);
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
            printf("BaseTestServer1 error1");
            return;
        }

        if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            printf("BaseTestServer1 error2");
            return;
        }

        int ret = listen(sock, 1024*64);
        EPollFileObserver observer = createEPollFileObserver();
        observer->addObserver(sock,EPOLLIN,createBaseTestListener1());
        while(1) {}
    }
};

int basetest() {
    //test1
    BaseTestServer1 server1 = createBaseTestServer1();
    server1->start();

    while(1){usleep(100000);}
}
