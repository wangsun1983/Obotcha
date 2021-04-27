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

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpLinkerManager) {
public:
    static sp<_HttpLinkerManager> getInstance();

    void addLinker(sp<_HttpLinker>);

    HttpLinker getLinker(Socket);

    HttpLinker removeLinker(Socket);
    
    void clear();
    
private:
    static std::once_flag s_flag;
    static sp<_HttpLinkerManager> mInstance;
    
    Mutex mMutex;

    HashMap<Socket,HttpLinker> mClients;

    _HttpLinkerManager();

    Random mRand;
};


}
#endif
