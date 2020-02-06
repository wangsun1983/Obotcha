#include "HttpV1ResponseWriter.hpp"
#include "AutoMutex.hpp"

namespace obotcha {

_HttpV1ResponseWriter::_HttpV1ResponseWriter(HttpV1ClientInfo client) {
    mClient = client;
    mPacket = createHttpPacket();
}
    
void _HttpV1ResponseWriter::writeHeader(String key,String value) {
    mPacket->getHeader()->setValue(key,value);
}

void _HttpV1ResponseWriter::setStatus(int status) {
    mPacket->getHeader()->setValue(st(HttpHeader)::Status,createString(status));
}

void _HttpV1ResponseWriter::writeBody(ByteArray content) {
    //update content length
    mPacket->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(content->size()));
    mPacket->setBody(content);
}

int _HttpV1ResponseWriter::write(HttpPacket packet) {
    mPacket = packet;
}

int _HttpV1ResponseWriter::flush() {
    AutoMutex l(mClient->getResponseWriteMutex());
    String resp = mPacket->genHttpResponse();
    mClient->send(resp);
}

}
