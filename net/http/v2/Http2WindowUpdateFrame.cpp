#include "Http2WindowUpdateFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2WindowUpdateFrame::_Http2WindowUpdateFrame() {
    type = TypeWindowUpdate;
}

void _Http2WindowUpdateFrame::import(ByteArray s) {
    ByteArrayReader reader = createByteArrayReader(s,Global::BigEndian);
    windowSize = reader->readUint32()&0x7FFFFFFF;
}

ByteArray _Http2WindowUpdateFrame::toByteArray() {
    ByteArray data = createByteArray(4);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);
    writer->writeUint32(windowSize);
    return data;
}

uint32_t _Http2WindowUpdateFrame::getWindowSize() {
    return windowSize;
}

void _Http2WindowUpdateFrame::setWindowSize(uint32_t s) {
    windowSize = s;
}



}
