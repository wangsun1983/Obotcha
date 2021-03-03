#include <netdb.h>
#include <arpa/inet.h>

#include "URL.hpp"
#include "Inet4Address.hpp"
#include "Inet6Address.hpp"

namespace obotcha {

_URL::_URL(String uri) {
    this->uri = uri;
}

ArrayList<InetAddress> _URL::getInetAddress() {
    ArrayList<InetAddress> hosts = createArrayList<InetAddress>();
    struct hostent *hptr = gethostbyname(uri->toChars());
    if(hptr == nullptr) {
        return nullptr;
    }

    char **pptr = hptr->h_addr_list;
    char  str[64];
    for(; *pptr!=NULL; pptr++) {
        inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
        InetAddress address = nullptr;
        if(hptr->h_addrtype == AF_INET) {
            address = createInet4Address(createString(str),-1);
        } else if(hptr->h_addrtype == AF_INET6) {
            address = createInet6Address(createString(str),-1);
        }
        
        hosts->add(address);
    }
    
    return hosts;
}

}
