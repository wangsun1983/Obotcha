#include "Http2RstFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2RstFrame::_Http2RstFrame():_Http2Frame() {
    this->type = TypeRstStream;
}

void _Http2RstFrame::load(ByteArray bytes) {
    auto reader = createByteArrayReader(bytes,st(Defination)::BigEndian);
    this->errcode = reader->read<uint32_t>();
}

ByteArray _Http2RstFrame::toByteArray() {
    ByteArray data = createByteArray(1);
    ByteArrayWriter writer = createByteArrayWriter(data,st(Defination)::BigEndian);
    writer->write<uint32_t>(errcode);
    return data;
}

}
