#include "Http2RstFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2RstFrame::_Http2RstFrame():_Http2Frame() {
    this->type = Type::RstStream;
}

void _Http2RstFrame::load(ByteArray bytes) {
    auto reader = createByteArrayReader(bytes,st(IO)::Endianness::Big);
    this->errcode = reader->read<uint32_t>();
}

ByteArray _Http2RstFrame::toByteArray() {
    ByteArray data = createByteArray(1);
    ByteArrayWriter writer = createByteArrayWriter(data,st(IO)::Endianness::Big);
    writer->write<uint32_t>(errcode);
    return data;
}

}
