#include "Http2RstFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2RstFrame::_Http2RstFrame():_Http2Frame() {
    errcode = 0;
    this->type = TypeRstStream;
}

void _Http2RstFrame::import(ByteArray bytes) {
    auto reader = createByteArrayReader(bytes,BigEndian);
    this->errcode = reader->readUint32();
}

ByteArray _Http2RstFrame::toByteArray() {
    ByteArray data = createByteArray(1);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);
    writer->write<uint32_t>(errcode);
    return data;
}

}
