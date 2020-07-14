
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "SystemProperties.hpp"

using namespace obotcha;


int main(int argc, char *argv[]) {
  String command = createString(argv[1]);
  if(command->equals("server")) {
    unlink("sysprops");
    SystemProperties instance = st(SystemProperties)::getInstance();
    while(1) {
      sleep(1);
    }
  }

  if(command->equals("set")) {
      String key = createString(argv[2]);
      String value = createString(argv[3]);
      SystemProperties instance = st(SystemProperties)::getInstance();
      instance->set(key,value);
  }

  if(command->equals("get")) {
     String key = createString(argv[2]);
     SystemProperties instance = st(SystemProperties)::getInstance();
     String value = instance->get(key);
     printf("value is %s \n",value->toChars());
  }
}

