#include "Http2Frame.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

const int _Http2Frame::DefaultWeight = 16;
const int _Http2Frame::MaxWeight = 256;

_Http2Frame::_Http2Frame() {
    type = 0;
    flags = 0;
    length = 0;
    weight = DefaultWeight;
    streamid = 0;
}

void _Http2Frame::setEndStream(bool s) {
    if(s) {
        flags |= FlagEndStream;
    } else {
        flags &= ~FlagEndStream;
    }
}

bool _Http2Frame::isEndStream() {
    return (flags & FlagEndStream) != 0;
}

void _Http2Frame::setEndHeaders(bool s) {
    if(s) {
        flags |= FlagEndHeaders;
    } else {
        flags &= ~FlagEndHeaders;
    }
}

bool _Http2Frame::isEndHeaders() {
    return (flags & FlagEndHeaders) != 0;
}

void _Http2Frame::setAck(bool s) {
    if(s) {
        flags |= FlagAck;
    } else {
        flags &= ~FlagAck;
    }
}

bool _Http2Frame::isAck() {
    return (flags & FlagAck) != 0;
}

void _Http2Frame::setPadding(bool s) {
    if(s) {
        flags |= FlagPadded;
    } else {
        flags &= ~FlagPadded;
    }
}

bool _Http2Frame::isPadding() {
    return (flags & FlagPadded) != 0;
}

void _Http2Frame::setPriority(bool s) {
    if(s) {
        flags |= FlagPriority;
    } else {
        flags &= ~FlagPriority;
    }
}

bool _Http2Frame::isPrioroty() {
    return (flags & FlagPriority) != 0; 
}

void _Http2Frame::setWeight(int s) {
    weight = s;
    setPriority(true);
}

int _Http2Frame::getWeight() {
    return weight;
}


ByteArray _Http2Frame::toFrameData() {
    ByteArray payload = toByteArray();
    int length = 0;
    //setting ack frame has no payload
    if(payload != nullptr) {
        length = payload->size();
    }
    ByteArray frame = createByteArray(length + 9);
    ByteArrayWriter writer = createByteArrayWriter(frame,BigEndian);
    writer->writeUint32(length << 8 | type);
    writer->writeByte(flags);
    writer->writeUint32(streamid & 0x7FFFFFFF);
    if(payload != nullptr) {
        writer->writeByteArray(payload);
    }

    frame->setPriorityWeight(weight);

    return frame;
}

int _Http2Frame::getType() {
    return type;
}

int _Http2Frame::getLength() {
    return length;
}

void _Http2Frame::setLength(int s) {
    length = s;
}

uint32_t _Http2Frame::getFlags() {
    return flags;
}

void _Http2Frame::setFlags(uint32_t s) {
    flags = s;
}

uint32_t _Http2Frame::getStreamId() {
    return streamid;
}

void _Http2Frame::setStreamId(uint32_t s) {
    streamid = s;
}

void _Http2Frame::import(ByteArray) {
    //do nothing
}

void _Http2Frame::setExclusive(bool s) {
    exclusive = s;
}

bool _Http2Frame::getExclusive() {
    return exclusive;
}


}
