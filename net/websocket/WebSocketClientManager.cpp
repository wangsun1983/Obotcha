#include "WebSocketClientManager.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "AutoLock.hpp"
#include "Log.hpp"

namespace obotcha {

//--------------------WebSocketClientManager-----------------
WebSocketClientManager _WebSocketClientManager::mInstance = nullptr;
Mutex _WebSocketClientManager::mMutex = createMutex("WebSocketClientManagerMutex");

_WebSocketClientManager::_WebSocketClientManager() {
    mClients = createHashMap<int, WebSocketClientInfo>();

    mRand = createRandom();
}

uint32_t _WebSocketClientManager::genRandomUint32() {
    return mRand->nextUint32();
}

WebSocketClientManager _WebSocketClientManager::getInstance() {
    if (mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);

    if (mInstance != nullptr) {
        return mInstance;
    }

    mInstance = AutoClone(new _WebSocketClientManager());
    return mInstance;
}

WebSocketClientInfo _WebSocketClientManager::addClient(int fd, int version) {
    WebSocketClientInfo client = createWebSocketClientInfo();
    client->setClientFd(fd);
    client->setVersion(version);

    switch (version) {
        case 0: {
            client->setParser(createWebSocketHybi00Parser());
            client->setComposer(createWebSocketHybi00Composer(WsServerComposer));
            break;
        }

        case 7: {
            client->setParser(createWebSocketHybi07Parser());
            client->setComposer(createWebSocketHybi07Composer(WsServerComposer));
            break;
        }

        case 8: {
            client->setParser(createWebSocketHybi08Parser());
            client->setComposer(createWebSocketHybi08Composer(WsServerComposer));
            break;
        }

        case 13: {
            client->setParser(createWebSocketHybi13Parser());
            client->setComposer(createWebSocketHybi13Composer(WsServerComposer));
            break;
        }

        default:
            LOG(ERROR)<<"WebSocket Protocol Not Support,Version is "<<version;
            return nullptr;
    }

    AutoLock ll(mMutex);
    mClients->put(fd, client);
    return client;
}

WebSocketClientInfo _WebSocketClientManager::getClient(int fd) {
    AutoLock ll(mMutex);
    return mClients->get(fd);
}

void _WebSocketClientManager::removeClient(WebSocketClientInfo client) {
    AutoLock ll(mMutex);
    mClients->remove(client->getClientFd());
}


}

