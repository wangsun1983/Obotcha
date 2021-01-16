#include "HttpClientManager.hpp"

namespace obotcha {

//HttpClientManager
HttpClientManager _HttpClientManager::mInstance = nullptr;
Mutex _HttpClientManager::mInitMutex = createMutex("HttpServer Mutex");;

_HttpClientManager::_HttpClientManager() {
    mClients = createHashMap<int,HttpClientInfo>();
    mMutex = createMutex("http client manager");
    mRand = createRandom();
}

uint32_t _HttpClientManager::genRandomUint32() {
    return mRand->nextUint32();
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

HttpClientInfo _HttpClientManager::getClientInfo(int fd) {
    AutoLock l(mMutex);
    return mClients->get(fd);
}

void _HttpClientManager::addClientInfo(int fd,sp<_HttpClientInfo> info) {
    AutoLock l(mMutex);
    mClients->put(fd,info);
}
    

HttpClientInfo _HttpClientManager::removeClientInfo(int fd) {
    AutoLock l(mMutex);
    HttpClientInfo ret = mClients->get(fd);
    mClients->remove(fd);

    return ret;
}

void _HttpClientManager::clear() {
    AutoLock l(mMutex);
    mClients->clear();
}

}