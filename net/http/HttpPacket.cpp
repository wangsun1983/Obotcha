#include "HttpPacket.hpp"
#include "ArrayList.hpp"
#include "HttpHeader.hpp"
#include "HttpMethod.hpp"
#include "String.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

const int _HttpPacket::kHttpBufferSize = 64*1024;

void _HttpPacket::setHeader(HttpHeader h) { 
    mHeader = h; 
}

HttpHeader _HttpPacket::getHeader() { 
    return mHeader; 
}

HttpEntity _HttpPacket::getEntity() { 
    return mEntity; 
}

void _HttpPacket::setEntity(HttpEntity entity) { 
    mEntity = entity; 
}

void _HttpPacket::setType(st(Http)::PacketType type) {
    mType = type;
}

st(Http)::PacketType _HttpPacket::getType() const {
    return mType;
}

bool _HttpPacket::isChunked() {
    if(auto encoding = mHeader->getTransferEncoding();
        encoding != nullptr) {
        ArrayList<String> items = encoding->get();
        ForEveryOne(item,items) {
            if(item->equalsIgnoreCase(st(HttpHeader)::TransferChunked)) {
                return true;
            }
        }
    }

    return false;
}

} // namespace obotcha
