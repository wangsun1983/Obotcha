#include "Http2Frame.hpp"
#include "ByteArrayWriter.hpp"
#include "Http2FrameByteArray.hpp"

namespace obotcha {

const byte _Http2Frame::DefaultWeight = 16;
const int _Http2Frame::MaxWeight = 256;

void _Http2Frame::setEndStream(bool s) {
    if(s) {
        flags |= Flag::EndStream;
    } else {
        flags &= ~Flag::EndStream;
    }
}

bool _Http2Frame::isEndStream() const {
    return (flags & Flag::EndStream) != 0;
}

void _Http2Frame::setEndHeaders(bool s) {
    if(s) {
        flags |= Flag::EndHeaders;
    } else {
        flags &= ~Flag::EndHeaders;
    }
}

bool _Http2Frame::isEndHeaders() const {
    return (flags & Flag::EndHeaders) != 0;
}

void _Http2Frame::setAck(bool s) {
    if(s) {
        flags |= Flag::Ack;
    } else {
        flags &= ~Flag::Ack;
    }
}

bool _Http2Frame::isAck() const {
    return (flags & Flag::Ack) != 0;
}

void _Http2Frame::setPadding(bool s) {
    if(s) {
        flags |= Flag::Padded;
    } else {
        flags &= ~Flag::Padded;
    }
}

bool _Http2Frame::isPadding() const {
    return (flags & Flag::Padded) != 0;
}

void _Http2Frame::setPriority(bool s) {
    if(s) {
        flags |= Flag::Priority;
    } else {
        flags &= ~Flag::Priority;
    }
}

bool _Http2Frame::isPrioroty() const {
    return (flags & Flag::Priority) != 0;
}

void _Http2Frame::setWeight(byte s) {
    weight = s;
    setPriority(true);
}

byte _Http2Frame::getWeight() const {
    return weight;
}

Http2FrameByteArray _Http2Frame::toFrameData() {
    ByteArray payload = toByteArray();
    size_t len = 0;
    //setting ack frame has no payload
    if(payload != nullptr && payload->size() != 0) {
        len = payload->size();
    }

    Http2FrameByteArray frame = Http2FrameByteArray::New(len + 9);
    ByteArrayWriter writer = ByteArrayWriter::New(frame,st(IO)::Endianness::Big);
    writer->write((uint32_t)(len << 8 | static_cast<int>(type)));
    writer->write((byte)flags);
    writer->write((streamid & 0x7FFFFFFF));
    if(payload != nullptr) {
        writer->write(payload);
    }

    frame->setPriorityWeight(weight);
    frame->setType(type);

    return frame;
}

_Http2Frame::Type _Http2Frame::getType() const {
    return type;
}

int _Http2Frame::getLength() const {
    return length;
}

void _Http2Frame::setLength(int s) {
    length = s;
}

uint32_t _Http2Frame::getFlags() const {
    return flags;
}

void _Http2Frame::setFlags(uint32_t s) {
    flags = s;
}

uint32_t _Http2Frame::getStreamId() const {
    return streamid;
}

void _Http2Frame::setStreamId(uint32_t s) {
    streamid = s;
}

void _Http2Frame::load(ByteArray) {
    //do nothing
}

void _Http2Frame::setExclusive(bool s) {
    exclusive = s;
}

bool _Http2Frame::getExclusive() const {
    return exclusive;
}


}
