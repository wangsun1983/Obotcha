#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InetAddress.hpp"
#include "Log.hpp"
#include "String.hpp"
#include "StringBuffer.hpp"
#include "Inet6Address.hpp"
#include "Inet4Address.hpp"
#include "InetLocalAddress.hpp"


namespace obotcha {

#define INET6_ADDRSTRLEN 46

int _InetAddress::DefaultPort = 8080;

//---------------SockAddress-------------
_SockAddress::_SockAddress(int family) {
    this->mFamily = family;
    switch(family) {
        case st(InetAddress)::IPV4: {
            memset(&mSockAddr, 0, sizeof(struct sockaddr_in));
        }
        break;

        case st(InetAddress)::IPV6: {
            memset(&mSockAddrV6, 0, sizeof(struct sockaddr_in6));
        }
        break;

        case st(InetAddress)::LOCAL: {
            memset(&mLocalSockAddr, 0, sizeof(struct sockaddr_un));
        }
        break;
    }
}

_SockAddress::_SockAddress(int family,String address,int port) {
    this->mFamily = family;
    switch(mFamily) {
        case st(InetAddress)::IPV4: {
                mSockAddr.sin_family = AF_INET;
                mSockAddr.sin_port = htons(port);
                if (address != nullptr) {
                    mSockAddr.sin_addr.s_addr = inet_addr(address->toChars());
                } else {
                    mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
                }
            }
            break;

        case st(InetAddress)::IPV6: {
            mSockAddrV6.sin6_family = AF_INET6;
            mSockAddrV6.sin6_port = htons(port);
            if (address != nullptr) {
                inet_pton(AF_INET6, address->toChars(), &mSockAddrV6.sin6_addr);
            } else {
                mSockAddrV6.sin6_addr = in6addr_any;
            }

            
        }
        break;

        case st(InetAddress)::LOCAL: {
            mLocalSockAddr.sun_family = AF_UNIX;
            strcpy(mLocalSockAddr.sun_path, address->toChars());
        }
        break;
    }
}

DefRet(int,sockaddr *) _SockAddress::get() {
    switch(mFamily) {
        case st(InetAddress)::IPV4: {
            return MakeRet(sizeof(mSockAddr),(sockaddr *)&mSockAddr);
        }
        
        case st(InetAddress)::IPV6: {
            return MakeRet(sizeof(mSockAddrV6),(sockaddr *)&mSockAddrV6);
        }

        case st(InetAddress)::LOCAL: {
            return MakeRet(sizeof(mLocalSockAddr),(sockaddr *)&mLocalSockAddr);
        }
    }

    return MakeRet(-1,nullptr);
}

int _SockAddress::port() {
    switch(mFamily) {
        case st(InetAddress)::IPV4: {
            return mSockAddr.sin_port;
        }
        
        case st(InetAddress)::IPV6: {
            return mSockAddrV6.sin6_port;
        }
    }

    return -1;
}

int _SockAddress::family() {
    switch(mFamily) {
        case st(InetAddress)::IPV4: {
            return AF_INET;
        }
        
        case st(InetAddress)::IPV6: {
            return AF_INET6;
        }

        case st(InetAddress)::LOCAL: {
            return AF_UNIX;
        }
    }
    return -1;
}

sp<_InetAddress> _SockAddress::toInetAddress() {
    switch(mFamily) {
        case st(InetAddress)::IPV4: {
            return createInet4Address(createString(inet_ntoa(mSockAddr.sin_addr)),
                                ntohs(mSockAddr.sin_port));

        }
        break;

        case st(InetAddress)::IPV6: {
            char buf[256];
            memset(buf,0,256);
            inet_ntop(AF_INET6, &mSockAddrV6.sin6_addr, buf, sizeof(buf));

            String ip = createString(buf);
            return createInet6Address(ip,mSockAddrV6.sin6_port);
        }
        break;

        case st(InetAddress)::LOCAL: {
            return createInetLocalAddress(createString(mLocalSockAddr.sun_path));
        }
        break;
    }
    return nullptr;
}

String _SockAddress::toString() {
    StringBuffer result = createStringBuffer();
    switch(mFamily) {
        case st(InetAddress)::IPV4: {
            result->append("ip is ")
                  ->append(inet_ntoa(mSockAddr.sin_addr))
                  ->append(",port is ")
                  ->append(createString(ntohs(mSockAddr.sin_port)));
            return result->toString();
        }
        break;

        case st(InetAddress)::IPV6: {
            char buf[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &mSockAddrV6.sin6_addr, buf, sizeof(buf));
            result->append("ip is ")
                  ->append(createString((const char *)buf))
                  ->append(",port is ")
                  ->append(createString(ntohs(mSockAddrV6.sin6_port)));
            return result->toString();
        }
        break;

        case st(InetAddress)::LOCAL: {
            result->append("local path is ")
                  ->append(createString(mLocalSockAddr.sun_path));
            return result->toString();
        }
        break;
    }

    return nullptr;
}

//---------------InetAddress-------------
_InetAddress::_InetAddress(int port) {
    mPort = port;
    mAddress = nullptr;
    mFamily = -1;
}

_InetAddress::_InetAddress(String addr, int port) {
    mAddress = addr;
    mPort = port;
    mFamily = -1;
}

_InetAddress::_InetAddress() { 
    mPort = DefaultPort;
    mFamily = -1; 
}

void _InetAddress::setPort(int p) { 
    mPort = p; 
}

int _InetAddress::getPort() { 
    return mPort; 
}

void _InetAddress::setAddress(String addr) {
    if (addr != nullptr) {
        mAddress = addr;
    }
}

String _InetAddress::getAddress() { 
    return mAddress; 
}

SockAddress _InetAddress::getSockAddress() {
    if(mSockAddress == nullptr) {
        mSockAddress = createSockAddress(mFamily,mAddress,mPort);
    }
    
    return mSockAddress;
}

int _InetAddress::getFamily() {
    return mFamily;
}

uint64_t _InetAddress::hashcode() {
    return mAddress->append(createString(mPort))->hashcode();
}

bool _InetAddress::equals(InetAddress addr) {
    return mPort == addr->mPort
           && mFamily == addr->mFamily
           && (mAddress != nullptr)?mAddress->equals(addr->mAddress):addr->mAddress == nullptr;
}

String _InetAddress::toString() {
    return getSockAddress()->toString();
}

} // namespace obotcha