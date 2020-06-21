#include "SSLManager.hpp"

namespace obotcha {

SSLManager _SSLManager::mInstance = nullptr;
    
Mutex _SSLManager::mInitMutex = createMutex();

SSLManager _SSLManager::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mInitMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _SSLManager *p = new _SSLManager();
    mInstance.set_pointer(p);
    return mInstance;
}

void _SSLManager::add(int fd ,SSLInfo info) {
    AutoLock ll(mMutex);
    mSSLMap->put(fd,info);
}

SSLInfo _SSLManager::get(int fd) {
    AutoLock ll(mMutex);
    return mSSLMap->get(fd);
}

void _SSLManager::remove(int fd) {
    AutoLock ll(mMutex);
    mSSLMap->remove(fd);
}

_SSLManager::_SSLManager() {
    mSSLMap = createHashMap<int,SSLInfo>();
    mMutex = createMutex("SSLManagerMutex");
}

}
