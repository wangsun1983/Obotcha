#include "Socket.hpp"
#include "SocketBuilder.hpp"
#include "InetAddress.hpp"
#include "SocketMonitor.hpp"
#include "InetLocalAddress.hpp"

using namespace obotcha;

int messageCount = 0;
int disconnectCount = 0;

Mutex disconnectMutex = createMutex();
Condition disconnectCond = createCondition();

String message = createString("");

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener){
public:
  void onSocketMessage(int event,Socket s,ByteArray data) {
    switch(event) {
      case Message:
      message = message->append(data->toString());
      messageCount++;
      break;

      case Disconnect:
      disconnectCount++;
      AutoLock l(disconnectMutex);
      disconnectCond->notify();
      break;
    }
  }
};



int main() {
    SocketOption option = createSocketOption();
    //option->setReUseAddr(st(SocketOption)::On);
    Socket client = createSocketBuilder()->setAddress(createInetLocalAddress("mysock"))
                                         ->setOption(option)
                                         ->newLocalSocket();
    int ret = client->connect();
    SocketMonitor monitor = createSocketMonitor();
    monitor->bind(client,createMyListener());
    
    AutoLock l(disconnectMutex);
    disconnectCond->wait(disconnectMutex);

    if(disconnectCount != 1) {
      printf("---LocalSocketClient test1 [FAILED]---,messageCount is %d, disconnectCount is %d\n",messageCount,disconnectCount);
    }

    int count = message->counts("hello client");

    if(message->counts("hello client") != 50) {
      printf("---LocalSocketClient test2 [FAILED]--- count is %d,message is %s \n",message->toChars());
    }

    printf("---LocalSocketClient test3 [OK]--- \n");
    return 0;
}