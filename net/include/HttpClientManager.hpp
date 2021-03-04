#ifndef __OBOTCHA_HTTP_CLIENT_MANAGER_HPP__
#define __OBOTCHA_HTTP_CLIENT_MANAGER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "HttpHeader.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpPacket.hpp"
#include "HttpClientInfo.hpp"
#include "Random.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpClientManager) {
public:
    static sp<_HttpClientManager> getInstance();

    void addClientInfo(sp<_HttpClientInfo>);

    HttpClientInfo getClientInfo(Socket);

    HttpClientInfo removeClientInfo(Socket);
    
    void clear();
    
private:
    static sp<_HttpClientManager> mInstance;
    static Mutex mInitMutex;

    Mutex mMutex;

    HashMap<Socket,HttpClientInfo> mClients;

    _HttpClientManager();

    Random mRand;
};


}
#endif
