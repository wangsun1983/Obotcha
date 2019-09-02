#ifndef __WEBSOCKET_FRAME_COMPOSER_HPP__
#define __WEBSOCKET_FRAME_COMPOSER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Sha.hpp"
#include "Base64.hpp"
#include "Random.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketFrameComposer) {

public:
    _WebSocketFrameComposer(bool isClient);
    ByteArray generateControlFrame(int opcode, ByteArray payload);
    ByteArray generateMessageFrame(int formatOpcode,ByteArray message);

    String generateShakeHandFrame(String key);

private:
    Sha mSha;
    Base64 mBase64;
    bool mIsClient;
    Random mRand;

}; 

}
#endif
