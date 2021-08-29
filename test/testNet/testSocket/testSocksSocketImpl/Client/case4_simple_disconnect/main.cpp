#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Handler.hpp"
#include "Inet4Address.hpp"
#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "System.hpp"
#include "Md.hpp"
#include "CountDownLatch.hpp"
#include "Message.hpp"

using namespace obotcha;

Condition mwaitcond = createCondition();
Mutex mMutex = createMutex();

DECLARE_CLASS(MyHandler) IMPLEMENTS(Handler) {
public:
  void handleMessage(Message msg) {
    mwaitcond->notify();
  }
};

CountDownLatch latch = createCountDownLatch(32*1024);
MyHandler h = createMyHandler();

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
public:
  _MyListener(int i) {
    index = i;
  }

  void onSocketMessage(int event,Socket s,ByteArray data) {
    switch(event) {
      case Message: {
        
      }
      break;

      case Disconnect: {
        //printf("count is %d \n",latch->getCount());
        latch->countDown();
        h->removeMessages(0);
        h->sendEmptyMessageDelayed(0,2000);
      }
      break;
    }
  }

private:
  int index;
};


int main() {
    SocketMonitor monitor = createSocketMonitor();
    long sum = 0;

    for(int i = 0;i<32*1024;i++) {
      InetAddress addr = createInet4Address(1234);
      Socket client = createSocketBuilder()->setAddress(addr)->newSocket();
      if(client->connect() != 0) {
        printf("---TestTcpSocket case4_simple_multi_test test1 [FAILED]--- ,i is %d\n",i);
        continue;
      }

      monitor->bind(client,createMyListener(i));
    }
    
    {
      AutoLock l(mMutex);
      mwaitcond->wait(mMutex);
    }

    if(latch->getCount() != 0) {
      printf("---TestTcpSocket case4_simple_multi_test test2 [FAILED]--- cout is %d\n",latch->getCount());
    }

    printf("---TestTcpSocket case4_simple_multi_test test100 [OK]--- \n");
    return 0;
}