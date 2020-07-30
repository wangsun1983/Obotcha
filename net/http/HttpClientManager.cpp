#include "HttpClientManager.hpp"

namespace obotcha {

//HttpV1ClientManager
HttpV1ClientManager _HttpV1ClientManager::mInstance = nullptr;
Mutex _HttpV1ClientManager::mInitMutex = createMutex("HttpV1Server Mutex");;

_HttpV1ClientManager::_HttpV1ClientManager() {
    mClients = createHashMap<int,HttpV1ClientInfo>();
    mMutex = createMutex("http client manager");
}

sp<_HttpV1ClientManager> _HttpV1ClientManager::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mInitMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _HttpV1ClientManager *p = new _HttpV1ClientManager();
    mInstance.set_pointer(p);
    return mInstance;
}

HttpV1ClientInfo _HttpV1ClientManager::getClientInfo(int fd) {
    AutoLock l(mMutex);
    return mClients->get(fd);
}

void _HttpV1ClientManager::addClientInfo(int fd,sp<_HttpV1ClientInfo> info) {
    AutoLock l(mMutex);
    mClients->put(fd,info);
}
    

HttpV1ClientInfo _HttpV1ClientManager::removeClientInfo(int fd) {
    AutoLock l(mMutex);
    HttpV1ClientInfo ret = mClients->get(fd);
    mClients->remove(fd);

    return ret;
}

void _HttpV1ClientManager::clear() {
    AutoLock l(mMutex);
    mClients->clear();
}

}