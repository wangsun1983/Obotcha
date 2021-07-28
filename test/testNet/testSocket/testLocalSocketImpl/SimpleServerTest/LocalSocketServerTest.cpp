#include "Socket.hpp"
#include "SocketBuilder.hpp"
#include "InetAddress.hpp"
#include "SocketMonitor.hpp"
#include "InetLocalAddress.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener){
public:
  void onSocketMessage(int event,Socket s,ByteArray data) {
    printf("on event is %d \n",event);
    if(data != nullptr) {
      printf("event is %s \n",data->toString()->toChars());
    }
  }
};

int main() {
    SocketOption option = createSocketOption();
    option->setReUseAddr(st(SocketOption)::On);

    ServerSocket server = createSocketBuilder()->setAddress(createInetLocalAddress("mysock"))
                                               ->setOption(option)
                                               ->newServerLocalSocket();
    server->bind();
    SocketMonitor monitor = createSocketMonitor();
    monitor->bind(server,createMyListener());
    while(1) {
      sleep(100);
    }

    return 0;
}