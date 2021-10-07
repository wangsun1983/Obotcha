#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_CLASS(HasMessageHandler) IMPLEMENTS(Handler) {
public:

  void handleMessage(Message msg) {
  }

};

void testHasMessage() {
   HasMessageHandler h = createHasMessageHandler();
   for(int i = 0; i<1024;i++) {
    h->sendEmptyMessageDelayed(1,10000);
   }

   if(!h->hasMessage(1)) {
    printf("---[Handler Test {hasMessage} case1] [FAILED]--- \n");
   }

   h->removeMessages(1);
   if(h->hasMessage(1)) {
    printf("---[Handler Test {hasMessage} case2] [FAILED]--- \n");
   }

  printf("---[Handler Test {hasMessage} case3] [OK]--- \n");

}
