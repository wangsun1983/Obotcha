#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>

#include <fstream>
#include <sys/un.h>

#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

static AtomicInteger connectCount = createAtomicInteger(0);
static AtomicInteger disconnectCount = createAtomicInteger(0);
static AtomicInteger messageCount = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(Listener1) IMPLEMENTS(SocketListener) {
public:
  _Listener1(SocketMonitor m) {
    mSocketMonitor = m;
  }

  void onSocketMessage(int event ,Socket socket ,ByteArray data) {
    switch(event) {
      case st(Socket)::Connect:
      connectCount->incrementAndGet();
      mSocketMonitor->bind(socket,AutoClone(this));
      break;

      case st(Socket)::Message:
      //printf("get message is %s \n",data->toString()->toChars());
      messageCount->incrementAndGet();
      socket->getOutputStream()->write(data);
      //printf("send message \n");
      break;

      case st(Socket)::Disconnect:
      disconnectCount->incrementAndGet();
      mSocketMonitor->remove(socket);
      break;
    }
  }

private:
  SocketMonitor mSocketMonitor;
};

int main() {
  InetAddress inet = createInetAddress("192.168.1.8",1234);
  ServerSocket server = createSocketBuilder()->setAddress(inet)->newServerSocket();
  server->bind();
  SocketMonitor monitor = createSocketMonitor(4);
  monitor->bind(server,createListener1(monitor));
  sleep(100);

  if(connectCount->get() != 1024*32 || disconnectCount->get() != 1024*32 || messageCount->get() != 1024*32) {
    printf("---[testServerSocket ConnectCountTest case1,connectCount is %d,disconnectCount is %d,messageCount is %d] [FAILED]--- \n"
            ,connectCount->get(),disconnectCount->get(),messageCount->get());
  } else {

    printf("---[testServerSocket ConnectCountTest case1] [OK]---] \n");
  }
}
