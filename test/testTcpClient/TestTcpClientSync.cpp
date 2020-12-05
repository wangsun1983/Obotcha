
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TcpServer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;


int testTcpClientSync() {
    TcpClient client = createTcpClient("192.168.1.7",9999,-1,nullptr);
    client->doConnect();
    ByteArray data = client->doReceive();
    printf("data is %s \n",data->toString()->toChars());
    String hello = createString("hello server");
    client->doSend(createByteArray(hello));
    sleep(10);
    return 0;
}
