#include "SSLManager.hpp"

namespace obotcha {

SSLManager _SSLManager::getInstance() {
    static _SSLManager *mInstance = new _SSLManager();
    SSLManager s;
    s.set_pointer(mInstance);
    return s;
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
