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

using namespace obotcha;


CountDownLatch latch = createCountDownLatch(128);
long array[128] = {0};

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
public:
  _MyListener(int i) {
    index = i;
  }

  void onSocketMessage(int event,Socket s,ByteArray data) {
    switch(event) {
      case Message: {
        array[index] += data->toString()->toBasicInt();
      }
      break;

      case Disconnect: {
        latch->countDown();
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
    for(int i = 0;i<1024;i++) {
      sum+=i;
    }

    for(int i = 0;i<128;i++) {
      InetAddress addr = createInet4Address(1234);
      Socket client = createSocketBuilder()->setAddress(addr)->newSocket();
      if(client->connect() != 0) {
        printf("---TestTcpSocket case3_simple_multi_test test1 [FAILED]--- ,i is %d\n",i);
        return 1;
      }
      array[i] = 0;
      monitor->bind(client,createMyListener(i));
    }
    
    latch->await();
    for(int i = 0;i <128;i++) {
      if(array[i] != sum) {
        printf("---TestTcpSocket case3_simple_multi_test test2 [FAILED]--- ,array is %d,sum is %d\n",array[i],sum);
      }
    }
    
    printf("---TestTcpSocket case3_simple_multi_test test100 [OK]--- \n");
    return 0;
}