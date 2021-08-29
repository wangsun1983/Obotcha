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
#include "InetLocalAddress.hpp"

#include <signal.h>

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
        //printf("i get a message ,data is %s,fd is %d\n",data->toString()->toChars(),s->getFileDescriptor()->getFd());
        array[index] += data->toString()->toBasicLong();
        s->getOutputStream()->write(createString("abc")->toByteArray());
      }
      break;

      case Disconnect: {
        //printf("disconnect index is %d\n",index);
        latch->countDown();
      }
      break;
    }
  }

private:
  int index;
};


int main() {
    signal(SIGPIPE, SIG_IGN);
    SocketMonitor monitor = createSocketMonitor();
    long sum = 0;
    for(int i = 0;i<1024*32;i++) {
      sum+=i;
    }

    for(int i = 0;i<128;i++) {
      auto addr = createInetLocalAddress("case3_socket");
      Socket client = createSocketBuilder()->setAddress(addr)->newLocalSocket();
      if(client->connect() != 0) {
        printf("---TestLocalSocket Client case3_simple_multi_test test1 [FAILED]--- ,i is %d\n",i);
        return 1;
      }
      array[i] = 0;
      monitor->bind(client,createMyListener(i));
    }

    latch->await();
    for(int i = 0;i <128;i++) {
      if(array[i] != sum) {
        printf("---TestLocalSocket Client case3_simple_multi_test test2 [FAILED]--- ,index is %d,array is %ld,sum is %ld\n",i,array[i],sum);
      }
    }
    printf("trace3 \n");
    printf("---TestLocalSocket Client case3_simple_multi_test test100 [OK]--- \n");
    return 0;
}