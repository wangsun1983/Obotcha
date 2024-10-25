#include "Http2PriorityFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2PriorityFrame::_Http2PriorityFrame():_Http2Frame() {
    this->type = Type::Priority;
}

uint32_t _Http2PriorityFrame::getDependency() const {
    return dependencyStream;
}

void _Http2PriorityFrame::setDependency(uint32_t s) {
    dependencyStream = s;
}

void _Http2PriorityFrame::load(ByteArray data) {
    ByteArrayReader reader = ByteArrayReader::New(data);
    uint32_t dependencyData = reader->read<uint32_t>();
    exclusive = (((dependencyData >>24) & 0x80) != 0);
    dependencyStream = dependencyData & 0x7FFFFFFF;
    weight = reader->read<byte>();
}

ByteArray _Http2PriorityFrame::toByteArray() {
    ByteArray data = ByteArray::New(5);
    ByteArrayWriter writer = ByteArrayWriter::New(data,st(IO)::Endianness::Big);
    uint32_t data1 = dependencyStream;
    if(exclusive) {
        data1 |= 0x8000000000;
    }

    writer->write<uint32_t>(data1);
    writer->write<byte>(weight);

    return data;
}


}
