#include "WebSocketLinkerManager.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketLinker.hpp"
#include "WebSocketListener.hpp"
#include "AutoLock.hpp"
#include "Log.hpp"

namespace obotcha {

//--------------------WebSocketLinkerManager-----------------
_WebSocketLinkerManager::_WebSocketLinkerManager() {
    mClients = createHashMap<Socket, WebSocketLinker>();
    mMutex = createMutex();
}

WebSocketLinker _WebSocketLinkerManager::add(Socket sock, int version) {
    WebSocketLinker client = createWebSocketLinker(sock);
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
    mClients->put(sock, client);
    return client;
}

WebSocketLinker _WebSocketLinkerManager::get(Socket s) {
    AutoLock ll(mMutex);
    return mClients->get(s);
}

void _WebSocketLinkerManager::remove(WebSocketLinker client) {
    AutoLock ll(mMutex);
    mClients->remove(client->getSocket());
}


}

