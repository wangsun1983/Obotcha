#ifndef __OBOTCHA_WEBSOCKET_LINKER_MANGER_HPP__
#define __OBOTCHA_WEBSOCKET_LINKER_MANGER_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "Socket.hpp"

namespace obotcha {

class _WebSocketLinker;

DECLARE_CLASS(WebSocketLinkerManager) {
public:
    _WebSocketLinkerManager();

    sp<_WebSocketLinker> addLinker(Socket,int version);

    sp<_WebSocketLinker> getLinker(Socket);
  
    void removeLinker(sp<_WebSocketLinker>);

private:
    Mutex mMutex;
    HashMap<Socket,sp<_WebSocketLinker>> mClients;
};


}
#endif
