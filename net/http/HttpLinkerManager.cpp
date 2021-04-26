#include "HttpLinkerManager.hpp"

namespace obotcha {

//HttpLinkerManager
HttpLinkerManager _HttpLinkerManager::mInstance = nullptr;
Mutex _HttpLinkerManager::mInitMutex = createMutex("HttpServer Mutex");;

_HttpLinkerManager::_HttpLinkerManager() {
    mClients = createHashMap<Socket,HttpLinker>();
    mMutex = createMutex("http client manager");
}

sp<_HttpLinkerManager> _HttpLinkerManager::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mInitMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _HttpLinkerManager *p = new _HttpLinkerManager();
    mInstance.set_pointer(p);
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