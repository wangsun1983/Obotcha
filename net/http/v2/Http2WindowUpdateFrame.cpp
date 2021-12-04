#include "Http2WindowUpdateFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                0x4 (24)                       |
+---------------+---------------+---------------+
|   0x8 (8)     |    0x0 (8)    |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============================================================+
|R|              Window Size Increment (31)                     |
+-+-------------------------------------------------------------+
 */

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
