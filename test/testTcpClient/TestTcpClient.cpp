
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"

using namespace obotcha;

int main() {
  TcpClient client = createTcpClient("192.168.43.90",1111,3000);
  //CloseThread t = createCloseThread(client);
  //t->start();
  //testTcpClient();
  if(client->doConnect() == -1) {
    printf("connect failed \n");
  };

  ByteArray arr = createByteArray(createString("nihao from client"));
  client->doSend(arr);

  long t = st(System)::currentTimeMillis();
  printf("start wait \n");
  //client->wait();
  ByteArray recvData = client->doReceive();
  printf("TcpClient arr is %s \n",recvData->toValue());

  sleep(1);
  client->doSend(arr);

  sleep(2);
  recvData = client->doReceive();
  printf("TcpClient2 arr is %s \n",recvData->toValue());
  //client->release();
  //printf("main end!!!! \n");
  //while(1) {
  //
  //}
}
