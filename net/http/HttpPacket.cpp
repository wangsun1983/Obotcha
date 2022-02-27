#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpHeader.hpp"
#include "HttpMethod.hpp"
#include "HttpPacket.hpp"
#include "String.hpp"

namespace obotcha {

_HttpPacket::_HttpPacket() {
    mHeader = createHttpHeader();
    mEntity = createHttpEntity();
}

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

void _HttpPacket::setType(int type) {
    mType = type;
}

int _HttpPacket::getType() {
    return mType;
}

bool _HttpPacket::isChunked() {
    auto encoding = mHeader->getTransferEncoding();
    if(encoding != nullptr) {
        ArrayList<String> items = encoding->get();
        return items->contains(st(HttpHeader)::TransferChunked);
    }

    return false;
}

} // namespace obotcha
