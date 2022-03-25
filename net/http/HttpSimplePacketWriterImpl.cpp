#include "HttpSimplePacketWriterImpl.hpp"

namespace obotcha {

//support Http0.9 simple request
_HttpSimplePacketWriterImpl::_HttpSimplePacketWriterImpl(OutputStream stream) {
    mStream = stream;
}

int _HttpSimplePacketWriterImpl::write(HttpPacket p) {
    return mStream->write(p->getEntity()->getContent());
}

ByteArray _HttpSimplePacketWriterImpl::data(HttpPacket p) {
    return p->getEntity()->getContent();
}

}
