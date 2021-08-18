#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "AtomicInteger.hpp"

using namespace obotcha;


DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener) {

public:
  _MyListener(AtomicInteger connect,AtomicInteger disconnect,AtomicInteger message) {
      connectNum = connect;
      disconnectNum = disconnect;
      messageNum = message;
  }

  void onSocketMessage(int event,Socket s,ByteArray data) {
      switch(event) {
        case Connect:
        connectNum->incrementAndGet();
        break;

        case Disconnect:
        disconnectNum->incrementAndGet();
        break;

        case Message:
        messageNum->incrementAndGet();
        break;
      }
  }

private:
  AtomicInteger connectNum;
  AtomicInteger disconnectNum;
  AtomicInteger messageNum;
};

int main() {
    AtomicInteger connectNum = createAtomicInteger(0);
    AtomicInteger disconnectNum = createAtomicInteger(0);
    AtomicInteger messageNum = createAtomicInteger(0);
    SocketMonitor monitor = createSocketMonitor();

    InetAddress addr = createInetAddress("192.168.1.9",1222);
    ServerSocket sock = createSocketBuilder()->setAddress(addr)->newServerSocket();
    int result = sock->bind();
    monitor->bind(sock,createMyListener(connectNum,disconnectNum,messageNum));


    sleep(60);
    printf("connectNum is %d,disconnectNum is %d,messageNum is %d \n",connectNum->get(),disconnectNum->get(),messageNum->get());

}