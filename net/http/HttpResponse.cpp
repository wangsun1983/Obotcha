#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "String.hpp"

namespace obotcha {

_HttpResponse::_HttpResponse() : _HttpPacket() {
    st(HttpPacket)::getHeader()->setResponseStatus(st(HttpStatus)::Ok);
    mType = NORMAL;
    mFile = nullptr;
}

_HttpResponse::_HttpResponse(HttpPacket p) : _HttpPacket() {
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
}

void _HttpResponse::setFile(File f, int type) {
    mFile = f;
    mType = type;
}

File _HttpResponse::getFile() { return mFile; }

int _HttpResponse::getType() { return mType; }

String _HttpResponse::toString() {
    // TODO
    return nullptr;
}

} // namespace obotcha