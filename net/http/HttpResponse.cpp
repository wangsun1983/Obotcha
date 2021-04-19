#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"

namespace obotcha {

_HttpResponse::_HttpResponse():_HttpPacket() {
    st(HttpPacket)::getHeader()->setResponseStatus(st(HttpStatus)::Ok);
}

_HttpResponse::_HttpResponse(HttpPacket p):_HttpPacket() {
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
}

void _HttpResponse::setChunkedFile(File f) {
    mFile = f;
}

File _HttpResponse::getChunkedFile() {
    return mFile;
}

String _HttpResponse::toString() {
    //TODO
    return nullptr;
}


}