#ifndef __OBOTCHA_WEBSOCKET_LINKER_MANGER_HPP__
#define __OBOTCHA_WEBSOCKET_LINKER_MANGER_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "Socket.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

class _WebSocketLinker;

DECLARE_CLASS(WebSocketLinkerManager) {
public:
    _WebSocketLinkerManager();

    sp<_WebSocketLinker> add(Socket,int version);

    sp<_WebSocketLinker> get(Socket);
  
    void remove(sp<_WebSocketLinker>);

private:
    //Mutex mMutex;
    ReadWriteLock mReadWriteLock;
    ReadLock mReadLock;
    WriteLock mWriteLock;
    HashMap<Socket,sp<_WebSocketLinker>> mClients;
};


}
#endif
