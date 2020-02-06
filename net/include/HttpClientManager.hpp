#ifndef __HTTP_CLIENT_MANAGER_HPP__
#define __HTTP_CLIENT_MANAGER_HPP__

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
#include "HttpV1Parser.hpp"
#include "HttpPacket.hpp"
#include "HttpV1ClientInfo.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpV1ClientManager) {
public:
    static sp<_HttpV1ClientManager> getInstance();

    void addClientInfo(int fd,sp<_HttpV1ClientInfo>);

    HttpV1ClientInfo getClientInfo(int fd);

    HttpV1ClientInfo removeClientInfo(int fd);

    void clear();
    
private:
    static Mutex mMutex;

    HashMap<int,HttpV1ClientInfo> mClients;

    static sp<_HttpV1ClientManager> mInstance;

    _HttpV1ClientManager();
};


}
#endif
