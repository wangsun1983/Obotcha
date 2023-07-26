#include "Http2WindowUpdateFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

const uint32_t _Http2WindowUpdateOption::DeafaultWindowSize = 1024*1024*2;

_Http2WindowUpdateOption::_Http2WindowUpdateOption() {
    windowSize = DeafaultWindowSize;
}

uint32_t _Http2WindowUpdateOption::getWindowSize() {
    return windowSize;
}

void _Http2WindowUpdateOption::setWindowSize(uint32_t size) {
    windowSize = size;
}

//----------Http2WindowUpdateFrame-----------
_Http2WindowUpdateFrame::_Http2WindowUpdateFrame():_Http2WindowUpdateOption() {
    type = TypeWindowUpdate;
}

void _Http2WindowUpdateFrame::load(ByteArray s) {
    ByteArrayReader reader = createByteArrayReader(s,Defination::BigEndian);
    setWindowSize(reader->read<uint32_t>()&0x7FFFFFFF);
}

ByteArray _Http2WindowUpdateFrame::toByteArray() {
    ByteArray data = createByteArray(4);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);
    writer->write<uint32_t>(getWindowSize());
    return data;
}


}
