#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

int main() {
  InetAddress addr = createInetAddress("192.168.1.6",1222);
  Socket sock = createSocketBuilder()->setAddress(addr)->newDatagramSocket();
  OutputStream stream = sock->getOutputStream();

  int result = stream->write(createByteArray(createString("hello world")));
  printf("result is %d \n",result);

}