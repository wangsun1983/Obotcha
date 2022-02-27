#include "HttpLinkerManager.hpp"

namespace obotcha {

_HttpLinkerManager::_HttpLinkerManager() {
    mClients = createHashMap<Socket, HttpLinker>();
    mMutex = createMutex("http client manager");
}

HttpLinker _HttpLinkerManager::get(Socket s) {
    AutoLock l(mMutex);
    return mClients->get(s);
}

void _HttpLinkerManager::add(sp<_HttpLinker> info) {
    AutoLock l(mMutex);
    mClients->put(info->mSocket, info);
}

void _HttpLinkerManager::remove(sp<_HttpLinker> linker) {
    AutoLock l(mMutex);
    //HttpLinker ret = mClients->get(s);
    //mClients->remove(s);
    mClients->remove(linker->mSocket);
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