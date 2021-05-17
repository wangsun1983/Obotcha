#include <stdio.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>

#include "Host.hpp"

namespace obotcha {

_Host::_Host() {

}
    
String _Host::getHostName() {
    //get hostname;
    char hostname[128];
    int ret = gethostname(hostname, sizeof(hostname));
    if (ret != -1){
        return createString(hostname);
    }
    
    return nullptr;
}

ArrayList<InetHostAddress> _Host::getHostAddress() {
    struct ifaddrs * ifAddrStruct = NULL;
    void * tmpAddrPtr = NULL;
 
    ArrayList<InetHostAddress> addressList = createArrayList<InetHostAddress>();

    if (getifaddrs(&ifAddrStruct) != 0){
        //if wrong, go out!
        return nullptr;
    }
 
    struct ifaddrs * iter = ifAddrStruct;
 
    while (iter != NULL) {
        if (iter->ifa_addr->sa_family == AF_INET) { //if ip4
            // is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *)iter->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            InetHostAddress address = createInetHostAddress();
            address->interface = createString(iter->ifa_name);
            address->ip = createString(addressBuffer);
            addressList->add(address);
        }else if (iter->ifa_addr->sa_family==AF_INET6) { // check it is IP6
            tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            InetHostAddress address = createInetHostAddress();
            address->interface = createString(iter->ifa_name);
            address->ip = createString(addressBuffer);
            addressList->add(address);
        } 
        iter = iter->ifa_next;
    }

    //release the struct
    freeifaddrs(ifAddrStruct);
    return addressList;
}

ArrayList<InetHostMac> getMacAddress() {
    int fd = 0;
    int interface = 0;
    struct ifreq buf[128];
    struct ifconf ifc;
    
 
    ArrayList<InetHostMac> list = createArrayList<InetHostMac>();

    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        int i = 0;
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            interface = ifc.ifc_len / sizeof(struct ifreq);
            char mac[32] = {0};
            while (i < interface) {
                if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[i]))) {
                    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                        (unsigned char)buf[i].ifr_hwaddr.sa_data[0],
                        (unsigned char)buf[i].ifr_hwaddr.sa_data[1],
                        (unsigned char)buf[i].ifr_hwaddr.sa_data[2],
                        (unsigned char)buf[i].ifr_hwaddr.sa_data[3],
                        (unsigned char)buf[i].ifr_hwaddr.sa_data[4],
                        (unsigned char)buf[i].ifr_hwaddr.sa_data[5]);
                    InetHostMac inetMac = createInetHostMac();
                    inetMac->interface = createString(buf[i].ifr_ifrn.ifrn_name);
                    inetMac->mac = createString(mac);
                    list->add(inetMac);
                }
                i++;
            }
        }
    }
    
    if(fd != 0) {
        close(fd);
    }
    return list;
}

}
