#include "SSLManager.hpp"

namespace obotcha {

SSLManager _SSLManager::mInstance = nullptr;

Mutex _SSLManager::mMutex = createMutex("SSLManagerMutex");

SSLManager _SSLManager::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoMutex ll(mMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _SSLManager *v = new _SSLManager();
    mInstance.set_pointer(v);
    return mInstance;
}

void _SSLManager::add(int fd ,SSLInfo info) {
    AutoMutex ll(mMutex);
    mSSLMap->put(fd,info);
}

SSLInfo _SSLManager::get(int fd) {
    AutoMutex ll(mMutex);
    return mSSLMap->get(fd);
}

void _SSLManager::remove(int fd) {
    AutoMutex ll(mMutex);
    mSSLMap->remove(fd);
}

_SSLManager::_SSLManager() {
    mSSLMap = createHashMap<int,SSLInfo>();
}

}
