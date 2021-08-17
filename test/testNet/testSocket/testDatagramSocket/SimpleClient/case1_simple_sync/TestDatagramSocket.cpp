#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Handler.hpp"
#include "Inet4Address.hpp"

using namespace obotcha;

int messageCount = 0;
int disconnectCount = 0;

Mutex disconnectMutex = createMutex();
Condition disconnectCond = createCondition();

String message = createString("");

DECLARE_SIMPLE_CLASS(MyHandler) IMPLEMENTS(Handler) {
public:
  void handleMessage(sp<_Message> msg) {
    AutoLock l(disconnectMutex);
    disconnectCond->notify();
  }
};

MyHandler h = createMyHandler();

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener){
public:
  void onSocketMessage(int event,Socket s,ByteArray data) {
    switch(event) {
      case Message:
      h->removeMessages(1);
      message = message->append(data->toString());
      messageCount++;
      printf("trace6 \n");
      h->sendEmptyMessageDelayed(1,100);
      break;

      case Disconnect:
      //disconnectCount++;
      //AutoLock l(disconnectMutex);
      //disconnectCond->notify();
      printf("trace7 \n");
      break;
    }
  }
};


int main() {
    printf("trace1 \n");
    InetAddress addr = createInet4Address(1213);
    Socket client = createSocketBuilder()->setAddress(addr)->newDatagramSocket();

    int ret = client->connect();
    printf("trace2 ret is %d\n",ret);
    String resp = createString("hello server");
    printf("trace2_1 \n");
    client->getOutputStream()->write(resp->toByteArray());
    printf("trace2_2 \n");

    SocketMonitor monitor = createSocketMonitor();
    int bindret = monitor->bind(client,createMyListener());
    printf("trace3 bindret is %d\n",bindret);
    AutoLock l(disconnectMutex);
    disconnectCond->wait(disconnectMutex);
    printf("trace4 \n");

    int count = message->counts("hello server");
    printf("trace5 \n");
    if(message->counts("hello server") != 50) {
      printf("---TestDataGramSocket case1_simple_sync test2 [FAILED]--- count is %d,message is %s \n",count,message->toChars());
    }

    printf("---TestDataGramSocket case1_simple_sync test3 [OK]--- \n");
    return 0;
}