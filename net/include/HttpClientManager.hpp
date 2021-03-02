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

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpClientManager) {
public:
    static sp<_HttpClientManager> getInstance();

    void addClientInfo(int fd,sp<_HttpClientInfo>);

    HttpClientInfo getClientInfo(int fd);

    HttpClientInfo removeClientInfo(int fd);
    
    uint32_t genRandomUint32();

    void clear();
    
private:
    static sp<_HttpClientManager> mInstance;
    static Mutex mInitMutex;

    Mutex mMutex;

    HashMap<int,HttpClientInfo> mClients;

    _HttpClientManager();

    Random mRand;
};


}
#endif
