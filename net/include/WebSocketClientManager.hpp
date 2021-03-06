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
    
    WebSocketClientInfo addClient(Socket,int version);

    WebSocketClientInfo getClient(Socket);
  
    void removeClient(WebSocketClientInfo);

private:
   static WebSocketClientManager mInstance;
   
   static Mutex mMutex;
   
   HashMap<Socket,WebSocketClientInfo> mClients;

   _WebSocketClientManager();
};


}
#endif
