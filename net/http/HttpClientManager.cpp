#include "HttpClientManager.hpp"

namespace obotcha {

//HttpClientManager
HttpClientManager _HttpClientManager::mInstance = nullptr;
Mutex _HttpClientManager::mInitMutex = createMutex("HttpServer Mutex");;

_HttpClientManager::_HttpClientManager() {
    mClients = createHashMap<Socket,HttpClientInfo>();
    mMutex = createMutex("http client manager");
}

sp<_HttpClientManager> _HttpClientManager::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mInitMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _HttpClientManager *p = new _HttpClientManager();
    mInstance.set_pointer(p);
    return mInstance;
}

HttpClientInfo _HttpClientManager::getClientInfo(Socket s) {
    AutoLock l(mMutex);
    return mClients->get(s);
}

void _HttpClientManager::addClientInfo(sp<_HttpClientInfo> info) {
    AutoLock l(mMutex);
    mClients->put(info->getSocket(),info);
}
    

HttpClientInfo _HttpClientManager::removeClientInfo(Socket s) {
    AutoLock l(mMutex);
    HttpClientInfo ret = mClients->get(s);
    mClients->remove(s);

    return ret;
}

void _HttpClientManager::clear() {
    AutoLock l(mMutex);
    mClients->clear();
}

}