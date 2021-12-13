#include "Http2PriorityFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2PriorityFrame::_Http2PriorityFrame():_Http2Frame() {
    
}

void _Http2PriorityFrame::import(ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data);
    uint32_t dependencyData = reader->readUint32();
    exclusive = (((dependencyData >>24) & 0x80) != 0);
    dependency = dependencyData & 0x7FFFFFFF;
    weight = reader->readByte();
}

ByteArray _Http2PriorityFrame::toByteArray() {
    ByteArray data = createByteArray(5);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);
    uint32_t data1 = dependency;
    if(exclusive) {
        dependency |= 0x8000000000;
    }

    writer->writeUint32(data1);
    writer->writeByte(weight);

    return data;
}
    

}