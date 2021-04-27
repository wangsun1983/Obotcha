#ifndef __OBOTCHA_WEBSOCKET_LINKER_MANGER_HPP__
#define __OBOTCHA_WEBSOCKET_LINKER_MANGER_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpMultiPart.hpp"
#include "HashMap.hpp"
#include "WebSocketLinker.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketLinkerManager) {
public:
    static WebSocketLinkerManager getInstance();
    
    WebSocketLinker addLinker(Socket,int version);

    WebSocketLinker getLinker(Socket);
  
    void removeLinker(WebSocketLinker);

private:
    static std::once_flag s_flag;
    static WebSocketLinkerManager mInstance;
   
    Mutex mMutex;
    HashMap<Socket,WebSocketLinker> mClients;

   _WebSocketLinkerManager();
};


}
#endif
