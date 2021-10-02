#include "HttpLinkerManager.hpp"

namespace obotcha {

_HttpLinkerManager::_HttpLinkerManager() {
    mClients = createHashMap<Socket, HttpLinker>();
    mMutex = createMutex("http client manager");
}

HttpLinker _HttpLinkerManager::getLinker(Socket s) {
    AutoLock l(mMutex);
    return mClients->get(s);
}

void _HttpLinkerManager::addLinker(sp<_HttpLinker> info) {
    AutoLock l(mMutex);
    mClients->put(info->getSocket(), info);
}

HttpLinker _HttpLinkerManager::removeLinker(Socket s) {
    AutoLock l(mMutex);
    HttpLinker ret = mClients->get(s);
    mClients->remove(s);
    return ret;
}

void _HttpLinkerManager::clear() {
    AutoLock l(mMutex);
    //mClients->clear();
    mClients->foreach([](Socket s,HttpLinker l){
        l->close();
        return Global::Continue;
    });
    mClients->clear();
}

 _HttpLinkerManager::~_HttpLinkerManager() {
    clear();
}

} // namespace obotcha