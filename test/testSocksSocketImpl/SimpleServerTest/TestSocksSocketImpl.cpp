#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener) {

public:
  void onSocketMessage(int event,Socket s,ByteArray data) {
    printf("onSocketMessage fd is %d \n",s->getFileDescriptor()->getFd());

    if(data != nullptr) {
      printf("event is %d, data is %s\n",event,data->toString()->toChars());
    }

    String resp = createString("response from server");
    int ret = s->getOutputStream()->write(createByteArray(resp));
    printf("ret is %d \n",ret);
  }

};

int main() {
  InetAddress addr = createInetAddress("192.168.1.9",1222);
  ServerSocket sock = createSocketBuilder()->setAddress(addr)->newServerSocket();
  int result = sock->bind();
  printf("bind result is %d,fd is %d \n",result,sock->getFileDescriptor()->getFd());

  SocketMonitor monitor = createSocketMonitor();
  MyListener l = createMyListener();
  monitor->bind(sock,l);
  while(1) {
    sleep(1);
  }

}