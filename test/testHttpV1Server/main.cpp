#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpV1Server.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {
public:
    void onMessage(int fd,HttpPacket msg) {
        printf("msg is %s \n",msg->getBody()->toValue());
    }
};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpV1Server server = createHttpV1Server(8012,listener);
  while(1) {sleep(1000);}
}
