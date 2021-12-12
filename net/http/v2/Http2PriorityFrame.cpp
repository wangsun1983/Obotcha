#include "Http2PriorityFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2PriorityFrame::_Http2PriorityFrame() {
    exclusive = false;
}

void _Http2PriorityFrame::import(ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data);
    uint32_t v = reader->readUint32();
    exclusive = ((v & 0x8F) == 1);
    dependency = (v & 0x7F);
    weight = reader->readByte();
}

ByteArray _Http2PriorityFrame::toByteArray() {
    ByteArray data = createByteArray(5);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);
    uint32_t data1 = dependency;
    if(exclusive) {
        dependency |= 0x80;
    }

    writer->writeUint32(data1);
    writer->writeByte(weight);

    return data;
}

bool _Http2PriorityFrame::isExclusive() {
    return exclusive;
}

void _Http2PriorityFrame::setExclusive(bool v) {
    exclusive = v;
}

uint32_t _Http2PriorityFrame::getDependency() {
    return dependency;
}
void _Http2PriorityFrame::setDependency(uint32_t v) {
    dependency = v;
}

uint8_t _Http2PriorityFrame::getWeight() {
    return weight;
}

void _Http2PriorityFrame::setWeight(uint8_t v) {
    weight = v;
}
    

}