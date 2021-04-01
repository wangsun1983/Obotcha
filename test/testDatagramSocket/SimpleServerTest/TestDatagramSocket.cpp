#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener) {

public:
  void onSocketMessage(int event,Socket,ByteArray data) {
    printf("event is %d, data is %s\n",event,data->toString()->toChars());
  }

};

int main() {
  InetAddress addr = createInetAddress("192.168.1.9",1222);
  Socket sock = createSocketBuilder()->setAddress(addr)->newDatagramSocket();
  int result = sock->bind();
  printf("bind result is %d \n",result);

  SocketMonitor monitor = createSocketMonitor();
  MyListener l = createMyListener();
  monitor->bind(sock,l);
  while(1) {
    sleep(1);
  }

}