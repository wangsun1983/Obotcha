#include "HttpLinkerManager.hpp"

namespace obotcha {

_HttpLinkerManager::_HttpLinkerManager() {
    mClients = createHashMap<Socket, HttpLinker>();
    //mMutex = createMutex("http client manager");
    mReadWriteLock = createReadWriteLock();
    mReadLock = mReadWriteLock->getReadLock();
    mWriteLock = mReadWriteLock->getWriteLock();
}

HttpLinker _HttpLinkerManager::get(Socket s) {
    AutoLock l(mReadLock);
    return mClients->get(s);
}

void _HttpLinkerManager::add(sp<_HttpLinker> info) {
    AutoLock l(mWriteLock);
    mClients->put(info->mSocket, info);
}

void _HttpLinkerManager::remove(sp<_HttpLinker> linker) {
    AutoLock l(mWriteLock);
    mClients->remove(linker->mSocket);
}

void _HttpLinkerManager::clear() {
    AutoLock l(mWriteLock);
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