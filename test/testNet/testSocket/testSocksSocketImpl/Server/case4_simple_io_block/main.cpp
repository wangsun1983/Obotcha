#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Inet4Address.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

bool isFirst = true;

int main() {
  InetAddress addr = createInet4Address(1222);
  ServerSocket sock = createSocketBuilder()->setAddress(addr)->newServerSocket();
  int result = sock->bind();
  printf("result is %d \n",result);
  auto client = sock->accept();
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    auto stream = client->getInputStream();
    ByteArray data = createByteArray(32);
    watch->start();
    int len = stream->read(data);
    long result = watch->stop();
    //printf("result is %ld \n",result);
    if(len == 0) {
      break;
    }

    if(result < 100 || result > 105) {
      printf("---Test Tcp Server case4_block_io test1 [FAILED]--- \n");
    }
  }

  printf("---Test Tcp Server case4_block_io test100 [OK]--- \n");

}