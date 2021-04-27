#include "SSLManager.hpp"

namespace obotcha {

std::once_flag _SSLManager::s_flag;
SSLManager _SSLManager::mInstance;

SSLManager _SSLManager::getInstance() {
    std::call_once(s_flag, [&]() {
        _SSLManager *p = new _SSLManager();
        p->mInstance.set_pointer(p);
    });

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
