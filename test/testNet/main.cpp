#include <stdio.h>
#include <unistd.h>

#include "WsServerListener.hpp"

using namespace obotcha;

int main() {
    String abc = createString("h");
    abc->append("e");
    abc->append("e")->append("l");
    printf("abc is %s \n",abc->toChars());

    std::string abc2;
    abc2.append("c");
    abc2.append("d");
    printf("abc2 is %s \n",abc2.c_str());

    //start Ws Server
    printf("start \n");
    WsServerListener listener = createWsServerListener();
    printf("start1 \n");
    WebSocketServer server = createWebSocketServer();
    printf("start2 \n");
    int ret = server->bind(1212,"/wstest",listener);
    printf("ret is %d \n",ret);
    ret = server->start();
    printf("ret2 is %d \n",ret);
    while(1) {
        sleep(1000);
    }
}
