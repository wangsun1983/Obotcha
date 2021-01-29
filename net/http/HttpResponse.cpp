#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

_HttpResponse::_HttpResponse() {

}

_HttpResponse::_HttpResponse(HttpPacket p) {
    this->setEntity(p->getEntity());
    this->setHeader(p->getHeader());
    this->setMethod(p->getMethod());
    this->setReason(p->getReason());
    this->setUrl(p->getUrl());
    this->setStatus(p->getStatus());
    this->setVersion(p->getVersion());
}

void _HttpResponse::setFile(File f) {
    mFile = f;
}

File _HttpResponse::getFile() {
    return mFile;
}

String _HttpResponse::toString() {
    //TODO
}


}