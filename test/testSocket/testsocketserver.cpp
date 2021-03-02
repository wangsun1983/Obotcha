#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>

#include <fstream>
#include <sys/un.h>

#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Listener1) IMPLEMENTS(SocketListener) {
public:
  void onDataReceived(SocketResponser r,ByteArray pack) {
    printf("on data \n");
  }

  void onDisconnect(SocketResponser r) {
    printf("on disconnect \n");
  }

  void onConnect(SocketResponser r) {
    
    printf("wahah on connect fd is %d\n",r->getFd());
  }
};

int testSocketServer() {
  printf("trace1 \n");
  ServerSocket server = createSocketBuilder()->setPort(1234)->newServerSocket();
  server->bind();
  printf("trace2 \n");
  SocketMonitor monitor = createSocketMonitor();
  printf("trace3 \n");
  monitor->bind(server,createListener1());
  printf("trace4 \n");
  while(1) {sleep(100);}
}
