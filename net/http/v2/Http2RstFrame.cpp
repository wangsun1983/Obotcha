#include "Http2RstFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2RstFrame::_Http2RstFrame():_Http2Frame() {
    this->type = Type::RstStream;
}

int _Http2RstFrame::getErrorCode() {
    return errcode;
}

void _Http2RstFrame::setErrorCode(int e) {
    errcode = e;
}

void _Http2RstFrame::load(ByteArray bytes) {
    auto reader = ByteArrayReader::New(bytes,st(IO)::Endianness::Big);
    this->errcode = reader->read<uint32_t>();
}

ByteArray _Http2RstFrame::toByteArray() {
    ByteArray data = ByteArray::New(4);
    ByteArrayWriter writer = ByteArrayWriter::New(data,st(IO)::Endianness::Big);
    writer->write<uint32_t>(errcode);
    return data;
}

}
