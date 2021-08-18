#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_CLASS(HasMessageHandler) EXTENDS(Handler) {
public:
  
  void handleMessage(Message msg) { 
  }

};

int testHasMessage() {
   HasMessageHandler h = createHasMessageHandler();
   for(int i = 0; i<1024;i++) {
    h->sendEmptyMessageDelayed(1,10000);
   }

   if(!h->hasMessage(1)) {
    printf("---[Handler Test {hasMessage} case1] [FAILED]--- \n");
    return 0;
   }

   h->removeMessages(1);
   if(h->hasMessage(1)) {
    printf("---[Handler Test {hasMessage} case2] [FAILED]--- \n");
    return 0;
   }

  printf("---[Handler Test {hasMessage} case3] [OK]--- \n");
    
}
