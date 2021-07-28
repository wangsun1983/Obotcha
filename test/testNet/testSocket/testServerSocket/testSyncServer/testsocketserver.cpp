#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>

#include <fstream>
#include <sys/un.h>

#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

int main() {
  InetAddress inet = createInetAddress("192.168.1.9",1234);
  ServerSocket server = createSocketBuilder()->setAddress(inet)->newServerSocket();
  server->bind();
  while(1) {
    Socket s = server->accept();
    OutputStream out = s->getOutputStream();
    InputStream in = s->getInputStream();

    ByteArray data = createByteArray(1024);
    int length = in->read(data);
    printf("accept message is %s \n",data->toString()->toChars());

    out->write(createByteArray(createString("nihao")));
  }
}
