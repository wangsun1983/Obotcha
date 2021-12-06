#include "Http2RstFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                0x4 (24)                       |
+---------------+---------------+---------------+
|  0x3  (8)     |  0x0 (8)      |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============================================================+
|                        Error Code (32)                        |
+---------------------------------------------------------------+
 */

void _Http2RstFrame::import(ByteArray bytes) {
    auto reader = createByteArrayReader(bytes,BigEndian);
    this->errcode = reader->readUint32();
}

ByteArray _Http2RstFrame::toByteArray() {
    ByteArray data = createByteArray(1);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);
    return data;
}

}

