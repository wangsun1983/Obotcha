#ifndef __WEBSOCKET_RESPONSE_HPP__
#define __WEBSOCKET_RESPONSE_HPP__

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

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketResponse) {

public:
    _WebSocketResponse(bool isClient);
    ByteArray generateResponse(int opcode, ByteArray payload);
    String generateShakeHandResponse(String key);

private:
    Sha mSha;
    Base64 mBase64;
    bool mIsClient;

}; 

}
#endif
