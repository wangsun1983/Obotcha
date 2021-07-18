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

    String resp = createString("hello server");
    int ret = s->getOutputStream()->write(createByteArray(resp));
    printf("ret is %d \n",ret);
  }

};

int main() {
  InetAddress addr = createInetAddress("192.168.1.8",1222);
  Socket sock = createSocketBuilder()->setAddress(addr)->newDatagramSocket();
  int result = sock->connect();
  printf("bind result is %d,fd is %d \n",result,sock->getFileDescriptor()->getFd());
  
  String resp = createString("hello server");
  sock->getOutputStream()->write(createByteArray(resp));

  SocketMonitor monitor = createSocketMonitor();
  MyListener l = createMyListener();
  monitor->bind(sock,l);
  while(1) {
    sleep(1);
  }

}