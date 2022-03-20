#ifndef __OBOTCHA_HTTP_LINKER_MANAGER_HPP__
#define __OBOTCHA_HTTP_LINKER_MANAGER_HPP__

#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "HttpHeader.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpPacket.hpp"
#include "HttpLinker.hpp"
#include "Random.hpp"
#include "Socket.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_CLASS(HttpLinkerManager) {
public:
    _HttpLinkerManager();

    void add(sp<_HttpLinker>);

    HttpLinker get(Socket);

    void remove(sp<_HttpLinker>);
    
    void clear();

    ~_HttpLinkerManager();
    
private:
    //Mutex mMutex;
    ReadWriteLock mReadWriteLock;
    ReadLock mReadLock;
    WriteLock mWriteLock;

    HashMap<Socket,HttpLinker> mClients;

    //Random mRand;
};


}
#endif
