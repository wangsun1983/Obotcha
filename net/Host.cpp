#include <arpa/inet.h>
#include <cstring>
#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Host.hpp"
#include "InetAddress.hpp"
#include "Inspect.hpp"

namespace obotcha {

_Host::_Host() {}

String _Host::getName() {
    // get hostname;
    char hostname[128] = {0};
    return (gethostname(hostname, sizeof(hostname)) != -1)?
        createString(hostname):nullptr;
}

ArrayList<HostAddress> _Host::getAddresses() {
    struct ifaddrs *iter = nullptr;
    Inspect(getifaddrs(&iter) != 0,nullptr);

    ArrayList<HostAddress> addressList = createArrayList<HostAddress>();
    char addressBuffer[256] = {0};
    struct ifaddrs *ifaddr = iter;

    while (iter != nullptr) {
        HostAddress address = createHostAddress();
        void * tmpAddrPtr = &((struct sockaddr_in *)iter->ifa_addr)->sin_addr;
        bool found = false;

        if (iter->ifa_addr->sa_family == AF_INET) { // if ip4
            // is a valid IP4 Address
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            address->type = st(InetAddress)::IPV4;
            found = true;
        } else if (iter->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            address->type = st(InetAddress)::IPV6;
            found = true;
        }

        if(found) {
            address->interface = createString(iter->ifa_name);
            address->ip = createString(addressBuffer);
            addressList->add(address);
        }

        iter = iter->ifa_next;
    }

    // release the struct
    freeifaddrs(ifaddr);
    return addressList;
}

ArrayList<HostMac> _Host::getMacAddresses() {
    int fd = 0;
    struct ifreq buf[128];
    struct ifconf ifc;

    ArrayList<HostMac> list = createArrayList<HostMac>();

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            int i = 0;
            int interface = ifc.ifc_len / sizeof(struct ifreq);
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
                    HostMac inetMac = createHostMac();
                    inetMac->interface =
                        createString(buf[i].ifr_ifrn.ifrn_name);
                    inetMac->mac = createString(mac);
                    list->add(inetMac);
                }
                i++;
            }
        }
    }

    if (fd != 0) {
        close(fd);
    }

    return list;
}

} // namespace obotcha
