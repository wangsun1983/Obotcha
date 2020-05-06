#include "HttpClientManager.hpp"

namespace obotcha {

//HttpV1ClientManager
//HttpV1ClientManager _HttpV1ClientManager::mInstance = nullptr;
//Mutex _HttpV1ClientManager::mMutex = createMutex("HttpV1Server Mutex");;

_HttpV1ClientManager::_HttpV1ClientManager() {
    mClients = createHashMap<int,HttpV1ClientInfo>();
}

sp<_HttpV1ClientManager> _HttpV1ClientManager::getInstance() {
    static _HttpV1ClientManager *instance = new _HttpV1ClientManager();
    HttpV1ClientManager s;
    s.set_pointer(instance);
    return s;
}

HttpV1ClientInfo _HttpV1ClientManager::getClientInfo(int fd) {
    AutoMutex l(mMutex);
    return mClients->get(fd);
}

void _HttpV1ClientManager::addClientInfo(int fd,sp<_HttpV1ClientInfo> info) {
    AutoMutex l(mMutex);
    mClients->put(fd,info);
}
    

HttpV1ClientInfo _HttpV1ClientManager::removeClientInfo(int fd) {
    AutoMutex l(mMutex);
    HttpV1ClientInfo ret = mClients->get(fd);
    mClients->remove(fd);

    return ret;
}

void _HttpV1ClientManager::clear() {
    AutoMutex l(mMutex);
    mClients->clear();
}

}