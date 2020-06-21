#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "EPollFileObserver.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "TcpServer.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"
#include "AutoLock.hpp"
#include "AtomicLong.hpp"

using namespace obotcha;

AtomicInteger baseTestValue1 = createAtomicInteger(0);
AtomicInteger baseTestValue2 = createAtomicInteger(0);
AtomicLong baseTestValue3 = createAtomicLong(0);
int baseTestClientfd = 0;

class _BaseTestListener1;
class _BaseTestListener2;

ArrayList<sp<_BaseTestListener1>> listener1s = createArrayList<sp<_BaseTestListener1>>();
Mutex listenersMutex1 = createMutex("listeners1");

ArrayList<sp<_BaseTestListener2>> listener2s = createArrayList<sp<_BaseTestListener2>>();
Mutex listenersMutex2 = createMutex("listeners2");

DECLARE_SIMPLE_CLASS(BaseTestListener2) EXTENDS(EPollFileObserverListener) {
public:
    _BaseTestListener2() {

    }

    int onEvent(int fd,uint32_t events,ByteArray data) {
        //printf("fd is %d,event is %p \n",fd,events);
        if(data != nullptr) {
            baseTestValue2->addAndGet(data->size());
        }

        if((events &EPOLLRDHUP) != 0) {
            baseTestValue3->incrementAndGet();
            return 0;
        }

        //printf("fd is %d,data is %s \n",fd,data->toString()->toChars());
        
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

    int onEvent(int fd,uint32_t events,ByteArray data) {
        //printf("listener1 fd is %d,mSocket is %d,events is %p \n",fd,mSocket,events);
        if(fd == mSocket) {
            struct sockaddr_in client_address;
            socklen_t client_addrLength = sizeof(struct sockaddr_in);
            int clientfd = accept( mSocket, ( struct sockaddr* )&client_address, &client_addrLength );
            if(clientfd == -1) {
                printf("accept fail,error is %s \n",strerror(errno));
            }
            baseTestValue1->incrementAndGet();
            AutoLock l(listenersMutex2);
            BaseTestListener2 l2 = createBaseTestListener2();
            listener2s->add(l2);
            //printf("baseTestClientfd is %d \n",clientfd);
            mObserver->addObserver(clientfd,EPOLLIN|EPOLLRDHUP,l2);
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
        int opt = 1;
        printf("BaseTest trace1 \n");
        sock = socket(AF_INET, SOCK_STREAM, 0);
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_port = htons(1222);
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0) {
            printf("BaseTestServer1 error1");
            return;
        }

        printf("BaseTest trace2 sock is %d \n",sock);

        if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            printf("BaseTestServer1 error2");
            return;
        }

        printf("BaseTest trace3 sock is %d \n",sock);
        
        int ret = listen(sock, 1024*64);
        {
            printf("start create epoll \n");
            observer = createEPollFileObserver();
            printf("trace create epoll,add epoll hup is %d \n",sock);
            AutoLock l(listenersMutex1);
            BaseTestListener1 l1 = createBaseTestListener1(sock,observer);
            listener1s->add(l1);
            observer->addObserver(sock,EPOLLIN|EPOLLRDHUP,l1);
            printf("trace create end \n");
        }

        while(1) {sleep(100);}
    }

    EPollFileObserver getObserver() {
        return observer;
    }

    int getSock() {
        return sock;
    }


    void dump() {
        observer->dump();
    }

private:
    EPollFileObserver observer;
    int sock;
};

int basetest() {
    //test1
    BaseTestServer1 server1 = createBaseTestServer1();
    server1->start();
    sleep(100);
    printf("baseTestValue1 is %d,baseTestValue2 is %ld,baseTestValue3 is %d \n",baseTestValue1->get(),baseTestValue2->get(),baseTestValue3->get());
    server1->dump();
}
