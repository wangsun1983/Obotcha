#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyHandler) EXTENDS(Handler) {
public:
  void handleMessage(Message msg) {
    printf("receive time is %ld \n",st(System)::currentTimeMillis());
    printf("msg.what is %d \n",msg->what);
  }
};

int main() {
  MyHandler m = createMyHandler();
  printf("start time is %ld \n",st(System)::currentTimeMillis());
  m->sendEmptyMessageDelayed(2,2000);

  m->sendEmptyMessage(4);
  while(1) {}
  printf("end main!!!! \n");
}
