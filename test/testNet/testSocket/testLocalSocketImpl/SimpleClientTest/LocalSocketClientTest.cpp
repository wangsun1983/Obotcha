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
    Socket client = createSocketBuilder()->setAddress(createInetLocalAddress("mysock"))
                                               ->newLocalSocket();
    client->connect();
    SocketMonitor monitor = createSocketMonitor();
    monitor->bind(client,createMyListener());
    while(1) {
      sleep(100);
    }

    return 0;
}