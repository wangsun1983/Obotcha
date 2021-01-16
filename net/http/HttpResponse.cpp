#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

_HttpResponse::_HttpResponse(HttpPacket packet) {
    mPacket = packet;
}

_HttpResponse::_HttpResponse() {
    mPacket = createHttpPacket();
}

int _HttpResponse::getStatus() {
    return mPacket->getStatusCode();
}

void _HttpResponse::setStatus(int s) {
    return mPacket->setStatusCode(s);
}

ByteArray _HttpResponse::getBody() {
    return mPacket->getBody();
}

String _HttpResponse::getHeader(String key) {
    return mPacket->getHeader()->getValue(key);
}

void _HttpResponse::setBody(ByteArray data) {
    mPacket->setBody(data);
}

void _HttpResponse::setHeader(String key,String val) {
    mPacket->getHeader()->setValue(key,val);
}

HttpHeader _HttpResponse::getHeaders() {
    return nullptr;
}

void _HttpResponse::setFile(File f) {
    mFile = f;
}

File _HttpResponse::getFile() {
    return mFile;
}

void _HttpResponse::addCookie(HttpCookie cookie) {
    mPacket->addCookie(cookie);
}


}