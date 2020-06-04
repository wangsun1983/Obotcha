#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "EPollFileObserver.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "TcpServer.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

AtomicInteger baseTestValue1 = createAtomicInteger(0);
AtomicInteger baseTestValue2 = createAtomicInteger(0);
int baseTestClientfd = 0;

DECLARE_SIMPLE_CLASS(BaseTestListener2) EXTENDS(EPollFileObserverListener) {
public:
    _BaseTestListener2() {

    }

    int onEvent(int fd,int events,ByteArray data) {
        //printf("receive fd,data is %s \n",data->toString()->toChars());
        baseTestValue2->incrementAndGet();
        return 0;
    }
};

DECLARE_SIMPLE_CLASS(BaseTestListener1) EXTENDS(EPollFileObserverListener) {
public:
    _BaseTestListener1(int fd,EPollFileObserver ob) {
        //printf("mSocket is %d \n",mSocket);
        mSocket = fd;
        mObserver = ob;
    }

    int onEvent(int fd,int events,ByteArray data) {
        if(fd == mSocket) {
            struct sockaddr_in client_address;
            socklen_t client_addrLength = sizeof(struct sockaddr_in);
            if(baseTestClientfd == 0) {
                baseTestClientfd = accept( mSocket, ( struct sockaddr* )&client_address, &client_addrLength );
            }

            baseTestValue1->incrementAndGet();
            
            mObserver->addObserver(baseTestClientfd,EPOLLIN|EPOLLRDHUP,createBaseTestListener2());
        }

        return 0;
    }

private:
    int mSocket;
    EPollFileObserver mObserver;
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
        {
            printf("start create epoll \n");
            EPollFileObserver observer = createEPollFileObserver();
            printf("trace create epoll \n");
            for(int i = 0;i<1024*32;i++) {
                observer->addObserver(sock,EPOLLIN|EPOLLRDHUP,createBaseTestListener1(sock,observer));
            }
            printf("trace create end \n");
        }
        while(1) {}
    }
};

int basetest() {
    //test1
    BaseTestServer1 server1 = createBaseTestServer1();
    server1->start();
    sleep(30);
    printf("baseTestValue1 is %d \n",baseTestValue1->get());
    printf("baseTestValue2 is %d \n",baseTestValue2->get());
    //while(1){usleep(100000);}
}
