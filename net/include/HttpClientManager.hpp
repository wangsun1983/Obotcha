#ifndef __OBOTCHA_HTTP_CLIENT_MANAGER_HPP__
#define __OBOTCHA_HTTP_CLIENT_MANAGER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "TcpServer.hpp"
#include "HttpHeader.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpPacket.hpp"
#include "HttpV1ClientInfo.hpp"
#include "Random.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV1ClientManager) {
public:
    static sp<_HttpV1ClientManager> getInstance();

    void addClientInfo(int fd,sp<_HttpV1ClientInfo>);

    HttpV1ClientInfo getClientInfo(int fd);

    HttpV1ClientInfo removeClientInfo(int fd);
    
    uint32_t genRandomUint32();

    void clear();
    
private:
    static sp<_HttpV1ClientManager> mInstance;
    static Mutex mInitMutex;

    Mutex mMutex;

    HashMap<int,HttpV1ClientInfo> mClients;

    _HttpV1ClientManager();

    Random mRand;
};


}
#endif
