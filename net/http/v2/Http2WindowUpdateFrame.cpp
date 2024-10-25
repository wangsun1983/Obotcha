#include "Http2WindowUpdateFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

const uint32_t _Http2WindowUpdateOption::DeafaultWindowSize = 1024*1024*2;

_Http2WindowUpdateOption::_Http2WindowUpdateOption() {
    windowSize = DeafaultWindowSize;
}

uint32_t _Http2WindowUpdateOption::getWindowSize() const {
    return windowSize;
}

void _Http2WindowUpdateOption::setWindowSize(uint32_t size) {
    windowSize = size;
}

//----------Http2WindowUpdateFrame-----------
_Http2WindowUpdateFrame::_Http2WindowUpdateFrame():_Http2WindowUpdateOption() {
    type = Type::WindowUpdate;
}

void _Http2WindowUpdateFrame::load(ByteArray s) {
    ByteArrayReader reader = ByteArrayReader::New(s,st(IO)::Endianness::Big);
    setWindowSize(reader->read<uint32_t>()&0x7FFFFFFF);
}

ByteArray _Http2WindowUpdateFrame::toByteArray() {
    ByteArray data = ByteArray::New(4);
    ByteArrayWriter writer = ByteArrayWriter::New(data,st(IO)::Endianness::Big);
    writer->write<uint32_t>(getWindowSize());
    return data;
}


}
