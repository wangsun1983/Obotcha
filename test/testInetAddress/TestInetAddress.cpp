#include <stdio.h>
#include <unistd.h>

#include "InetAddress.hpp"
#include "ArrayList.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
    //InetAddress inet = createInetAddress();
#if 0  
    ArrayList<InetHostAddress> list = st(InetAddress)::getHostAddress();
    int index = 0;
    for(;index < list->size();index++) {
      InetHostAddress addr = list->get(index);
      LOGD("addr interface is ",addr->interface);
      LOGD("ip is ",addr->ip);
    }

    String hostname = st(InetAddress)::getHostName();
    LOGD("hostname is ",hostname);

    LOGD("-==============");
    ArrayList<InetHostMac> macs = st(InetAddress)::getMacAddress();
    index = 0;
    for(;index < macs->size();index++) {
      InetHostMac addr = macs->get(index);
      LOGD("mac interface is ",addr->interface);
      LOGD("mac is ",addr->mac);
    }
#endif
    ArrayList<String> hosts = st(InetAddress)::getHostByName("www.blog.csdn.net");
    if(hosts == nullptr) {
      printf("analyse fail \n");
      return 0;
    }

    for(int index = 0;index < hosts->size();index++) {
      String addr = hosts->get(index);
      printf("addr is %s",addr->toChars());
    }

}
