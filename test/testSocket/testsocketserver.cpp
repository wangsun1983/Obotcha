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
  void onSocketMessage(int event ,Socket socket ,ByteArray data) {
    switch(event) {
      case st(Socket)::Connect:
      connectCount->incrementAndGet();
      break;

      case st(Socket)::Message:
      messageCount->incrementAndGet();
      socket->getOutputStream()->write(data);
      break;

      case st(Socket)::Disconnect:
      disconnectCount->incrementAndGet();
      break;
    }
  }
};

int testSocketServer() {
  ServerSocket server = createSocketBuilder()->setPort(1234)->newServerSocket();
  server->bind();
  SocketMonitor monitor = createSocketMonitor(4);
  monitor->bind(server,createListener1());
  while(1) {sleep(100);}
}
