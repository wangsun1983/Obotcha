#include <ifaddrs.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/ioctl.h>

#include "Host.hpp"
#include "InetAddress.hpp"
#include "Inspect.hpp"

namespace obotcha {

String _Host::getName() const {
    char hostname[HOST_NAME_MAX + 1] = {0};
    return (gethostname(hostname, sizeof(hostname)) != -1)?
        String::New(hostname):nullptr;
}

ArrayList<HostAddress> _Host::getAddresses() const {
    struct ifaddrs *addrs = nullptr;
    struct ifaddrs *iter = nullptr;
    Inspect(getifaddrs(&addrs) != 0,nullptr)

    ArrayList<HostAddress> addressList = ArrayList<HostAddress>::New();
    for (iter = addrs; iter != nullptr; iter = iter->ifa_next) {
        HostAddress address = HostAddress::New();
        String ip = nullptr;

        if (iter->ifa_addr->sa_family == AF_INET) {
            auto sin = (struct sockaddr_in *)iter->ifa_addr;
            char addressBuffer[INET_ADDRSTRLEN + 1] = {0};
            inet_ntop(AF_INET,  &sin->sin_addr, addressBuffer, INET_ADDRSTRLEN);
            address->type = st(Net)::Family::Ipv4;
            ip = String::New(addressBuffer);
        } else if (iter->ifa_addr->sa_family == AF_INET6) {
            auto sin6 = (struct sockaddr_in6 *)iter->ifa_addr;
            char addressBuffer[INET6_ADDRSTRLEN + 1] = {0};
            inet_ntop(AF_INET6, &sin6->sin6_addr, addressBuffer, INET6_ADDRSTRLEN);
            address->type = st(Net)::Family::Ipv6;
            ip = String::New(addressBuffer);
        }

        if(ip != nullptr) {
            address->interface = String::New(iter->ifa_name);
            address->ip = ip;
            addressList->add(address);
        }
    }

    freeifaddrs(addrs);
    return addressList;
}

ArrayList<HostMac> _Host::getMacAddresses() const {
    int fd = 0;
    struct ifreq buf[128];
    struct ifconf ifc;

    ArrayList<HostMac> list = ArrayList<HostMac>::New();
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            int i = 0;
            int interface = ifc.ifc_len / sizeof(struct ifreq);
            char mac[128] = {0};
            while (i < interface) {
                if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[i]))) {
                    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[0],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[1],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[2],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[3],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[4],
                            (unsigned char)buf[i].ifr_hwaddr.sa_data[5]);
                    HostMac inetMac = HostMac::New();
                    inetMac->interface = String::New(buf[i].ifr_ifrn.ifrn_name);
                    inetMac->mac = String::New(mac);
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
