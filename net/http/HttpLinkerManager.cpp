#include "HttpLinkerManager.hpp"

namespace obotcha {

std::once_flag _HttpLinkerManager::s_flag;
sp<_HttpLinkerManager> _HttpLinkerManager::mInstance;

_HttpLinkerManager::_HttpLinkerManager() {
    mClients = createHashMap<Socket,HttpLinker>();
    mMutex = createMutex("http client manager");
}

sp<_HttpLinkerManager> _HttpLinkerManager::getInstance() {
    std::call_once(s_flag, [&]() {
        _HttpLinkerManager *p = new _HttpLinkerManager();
        p->mInstance.set_pointer(p);
    });

    return mInstance;
}

HttpLinker _HttpLinkerManager::getLinker(Socket s) {
    AutoLock l(mMutex);
    return mClients->get(s);
}

void _HttpLinkerManager::addLinker(sp<_HttpLinker> info) {
    AutoLock l(mMutex);
    mClients->put(info->getSocket(),info);
}

HttpLinker _HttpLinkerManager::removeLinker(Socket s) {
    AutoLock l(mMutex);
    HttpLinker ret = mClients->get(s);
    mClients->remove(s);

    return ret;
}

void _HttpLinkerManager::clear() {
    AutoLock l(mMutex);
    mClients->clear();
}

}