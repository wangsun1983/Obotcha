#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InetAddress.hpp"
#include "Log.hpp"
#include "String.hpp"
#include "StringBuffer.hpp"
#include "Inet6Address.hpp"
#include "Inet4Address.hpp"
#include "InetLocalAddress.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

in_port_t _InetAddress::kDefaultPort = 8080;

//---------------SockAddress-------------
_SockAddress::_SockAddress(st(Net)::Family family):mFamily(family) {
    switch(family) {
        case st(Net)::Family::Ipv4: {
            memset(&mSockAddr, 0, sizeof(struct sockaddr_in));
        } break;

        case st(Net)::Family::Ipv6: {
            memset(&mSockAddrV6, 0, sizeof(struct sockaddr_in6));
        } break;

        case st(Net)::Family::Local: {
            memset(&mLocalSockAddr, 0, sizeof(struct sockaddr_un));
        } break;

        case st(Net)::Family::Unknow:
            Trigger(IllegalArgumentException,"unknow family")
    }
}

_SockAddress::_SockAddress(st(Net)::Family family,String address,in_port_t port):mFamily(family) {
    switch(mFamily) {
        case st(Net)::Family::Ipv4: {
                mSockAddr.sin_family = AF_INET;
                mSockAddr.sin_port = htons(port);
                if (address != nullptr) {
                    mSockAddr.sin_addr.s_addr = inet_addr(address->toChars());
                } else {
                    mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
                }
        } break;

        case st(Net)::Family::Ipv6: {
            mSockAddrV6.sin6_family = AF_INET6;
            mSockAddrV6.sin6_port = htons(port);
            if (address != nullptr) {
                inet_pton(AF_INET6, address->toChars(), &mSockAddrV6.sin6_addr);
            } else {
                mSockAddrV6.sin6_addr = in6addr_any;
            }
        } break;

        case st(Net)::Family::Local: {
            mLocalSockAddr.sun_family = AF_UNIX;
            strcpy(mLocalSockAddr.sun_path, address->toChars());
        } break;

        case st(Net)::Family::Unknow: {
            LOG(ERROR)<<"InetAddress create SocketAdd unknow family";
        } break;
    }
}

DefRet(int,sockaddr *) _SockAddress::get() {
    switch(mFamily) {
        case st(Net)::Family::Ipv4: {
            return MakeRet(sizeof(mSockAddr),(sockaddr *)&mSockAddr);
        }

        case st(Net)::Family::Ipv6: {
            return MakeRet(sizeof(mSockAddrV6),(sockaddr *)&mSockAddrV6);
        }

        case st(Net)::Family::Local: {
            return MakeRet(sizeof(mLocalSockAddr),(sockaddr *)&mLocalSockAddr);
        }

        case st(Net)::Family::Unknow: {
            LOG(ERROR)<<"InetAddress get unknow family";
        } break;
    }

    return MakeRet(-1,nullptr);
}

in_port_t _SockAddress::port() const {
    switch(mFamily) {
        case st(Net)::Family::Ipv4: {
            return ntohs(mSockAddr.sin_port);
        }

        case st(Net)::Family::Ipv6: {
            return ntohs(mSockAddrV6.sin6_port);
        }

        case st(Net)::Family::Local:
        case st(Net)::Family::Unknow:
        //do nothing
        break;
    }
    return 0;
}

int _SockAddress::family() const {
    return static_cast<int>(mFamily);
}

sp<_InetAddress> _SockAddress::toInetAddress() {
    switch(mFamily) {
        case st(Net)::Family::Ipv4: {
            return Inet4Address::New(String::New(inet_ntoa(mSockAddr.sin_addr)),
                                ntohs(mSockAddr.sin_port));

        }

        case st(Net)::Family::Ipv6: {
            char buf[INET6_ADDRSTRLEN] = {0};
            inet_ntop(AF_INET6, &mSockAddrV6.sin6_addr, buf, sizeof(buf));
            String ip = String::New(buf);
            return Inet6Address::New(ip,ntohs(mSockAddrV6.sin6_port));
        }

        case st(Net)::Family::Local: {
            return InetLocalAddress::New(String::New(mLocalSockAddr.sun_path));
        }

        case st(Net)::Family::Unknow: {
            LOG(ERROR)<<"InetAddress toInetAddress unknow";
        } break;
    }
    return nullptr;
}

String _SockAddress::toString() {
    StringBuffer result = StringBuffer::New();
    switch(mFamily) {
        case st(Net)::Family::Ipv4: {
            result->append("ip is ")
                  ->append(inet_ntoa(mSockAddr.sin_addr))
                  ->append(",port is ")
                  ->append(String::New(ntohs(mSockAddr.sin_port)));
            return result->toString();
        }

        case st(Net)::Family::Ipv6: {
            char buf[INET6_ADDRSTRLEN] = {0};
            inet_ntop(AF_INET6, &mSockAddrV6.sin6_addr, buf, sizeof(buf));
            result->append("ip is ")
                  ->append(String::New((const char *)buf))
                  ->append(",port is ")
                  ->append(String::New(ntohs(mSockAddrV6.sin6_port)));
            return result->toString();
        }

        case st(Net)::Family::Local: {
            result->append("local path is ")
                  ->append(String::New(mLocalSockAddr.sun_path));
            return result->toString();
        }

        case st(Net)::Family::Unknow: {
            LOG(ERROR)<<"InetAddress toString unknow";
        } break;
    }
    return nullptr;
}

//---------------InetAddress-------------
_InetAddress::_InetAddress(in_port_t port):mPort(port) {
}

_InetAddress::_InetAddress(String addr, in_port_t port):mAddress(addr),mPort(port) {
}

void _InetAddress::setPort(in_port_t p) {
    mPort = p;
}

in_port_t _InetAddress::getPort() const {
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
        mSockAddress = SockAddress::New(mFamily,mAddress,mPort);
    }

    return mSockAddress;
}

st(Net)::Family _InetAddress::getFamily() const {
    return mFamily;
}

uint64_t _InetAddress::hashcode() const {
    return mAddress->append(String::New(mPort))->hashcode();
}

bool _InetAddress::equals(Object obj) {
    auto addr = dynamic_cast<_InetAddress *>(obj.get_pointer());
    return this == addr || (mPort == addr->mPort
           && mFamily == addr->mFamily
           && (mAddress != nullptr)?mAddress->equals(addr->mAddress):addr->mAddress == nullptr);
}

String _InetAddress::toString() {
    return getSockAddress()->toString();
}

} // namespace obotcha
