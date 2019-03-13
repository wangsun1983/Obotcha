#include <stdio.h>
#include <unistd.h>

#include "InetAddress.hpp"
#include "ArrayList.hpp"
#include "Log.hpp"

int main() {
    //InetAddress inet = createInetAddress();
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

}
