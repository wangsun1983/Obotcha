#include "Http2GoAwayFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2GoAwayFrame::_Http2GoAwayFrame():_Http2Frame() {
    this->type = TypeGoAway;
}

void _Http2GoAwayFrame::load(ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data,st(IO)::Endianness::Big);
    lastStreamId = reader->read<uint32_t>();
    errorCode = reader->read<uint32_t>();

    if(reader->isReadable()) {
        int size = reader->getRemainSize();
        additionalDebugData = createByteArray(size);
        reader->read(additionalDebugData);
    }
}

ByteArray _Http2GoAwayFrame::toByteArray() {
    int size = 8;
    if(additionalDebugData != nullptr) {
        size += additionalDebugData->size();
    }

    ByteArray data = createByteArray(size);
    ByteArrayWriter writer = createByteArrayWriter(data,st(IO)::Endianness::Big);

    writer->write<uint32_t>(lastStreamId);
    writer->write<uint32_t>(errorCode);

    if(additionalDebugData != nullptr) {
        writer->write(additionalDebugData);
    }

    return data;
}

uint32_t _Http2GoAwayFrame::getLastStreamId() const {
    return lastStreamId;
}

void _Http2GoAwayFrame::setLastStreamId(uint32_t v) {
    lastStreamId = v;
}

uint32_t _Http2GoAwayFrame::getErrorCode() const {
    return errorCode;
}

void _Http2GoAwayFrame::setErrorCode(uint32_t e) {
    errorCode = e;
}

void _Http2GoAwayFrame::setDebugData(ByteArray s) {
    additionalDebugData = s;
}

ByteArray _Http2GoAwayFrame::getDebugData() {
    return additionalDebugData;
}

}
