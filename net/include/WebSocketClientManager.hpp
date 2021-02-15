#ifndef __OBOTCHA_WEBSOCKET_CLIENT_MANGER_HPP__
#define __OBOTCHA_WEBSOCKET_CLIENT_MANGER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpMultiPart.hpp"
#include "HashMap.hpp"
#include "WebSocketClientInfo.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketClientManager) {
public:
    static WebSocketClientManager getInstance();
    
    WebSocketClientInfo addClient(int fd,int version);

    WebSocketClientInfo getClient(int fd);
  
    void removeClient(WebSocketClientInfo);

    uint32_t genRandomUint32();

private:
   static WebSocketClientManager mInstance;
   
   static Mutex mMutex;
   
   HashMap<int,WebSocketClientInfo> mClients;

   _WebSocketClientManager();

   Random mRand;

};


}
#endif
