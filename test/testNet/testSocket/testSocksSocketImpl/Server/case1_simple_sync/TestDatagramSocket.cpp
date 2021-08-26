#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Inet4Address.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"

using namespace obotcha;

String message = createString("");
bool isFirst = true;

Mutex mMutex = createMutex();
Condition mCond = createCondition();

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener) {

public:
  void onSocketMessage(int event,Socket s,ByteArray data) {
    if(isFirst) {
      int len = s->getOutputStream()->write(createString("hello client")->toByteArray());
      isFirst = false;
      mCond->notify();
      return;
    }

    message = message->append(data->toString());
  }

};

int main() {
  InetAddress addr = createInet4Address(1222);
  Socket sock = createSocketBuilder()->setAddress(addr)->newDatagramSocket();
  int result = sock->bind();
  SocketMonitor monitor = createSocketMonitor();
  MyListener l = createMyListener();
  monitor->bind(sock,l);
  AutoLock ll(mMutex);
  mCond->wait(mMutex);

  sleep(1);
  int count = message->counts("hello client");
    
  if(message->counts("hello client") != 50) {
    printf("---TestDataGramSocket Server case1_simple_sync test2 [FAILED]--- count is %d,message is %s \n",count,message->toChars());
  }

  printf("---TestDataGramSocket Server case1_simple_sync test3 [OK]--- \n");

}