#include "Http2Frame.hpp"
#include "ByteArrayWriter.hpp"
#include "Definations.hpp"

namespace obotcha {

const int _Http2Frame::DefaultWeight = 16;
const int _Http2Frame::MaxWeight = 256;

void _Http2Frame::setEndStream(bool s) {
    if(s) {
        flags |= FlagEndStream;
    } else {
        flags &= ~FlagEndStream;
    }
}

bool _Http2Frame::isEndStream() const {
    return (flags & FlagEndStream) != 0;
}

void _Http2Frame::setEndHeaders(bool s) {
    if(s) {
        flags |= FlagEndHeaders;
    } else {
        flags &= ~FlagEndHeaders;
    }
}

bool _Http2Frame::isEndHeaders() const {
    return (flags & FlagEndHeaders) != 0;
}

void _Http2Frame::setAck(bool s) {
    if(s) {
        flags |= FlagAck;
    } else {
        flags &= ~FlagAck;
    }
}

bool _Http2Frame::isAck() const {
    return (flags & FlagAck) != 0;
}

void _Http2Frame::setPadding(bool s) {
    if(s) {
        flags |= FlagPadded;
    } else {
        flags &= ~FlagPadded;
    }
}

bool _Http2Frame::isPadding() const {
    return (flags & FlagPadded) != 0;
}

void _Http2Frame::setPriority(bool s) {
    if(s) {
        flags |= FlagPriority;
    } else {
        flags &= ~FlagPriority;
    }
}

bool _Http2Frame::isPrioroty() const {
    return (flags & FlagPriority) != 0;
}

void _Http2Frame::setWeight(int s) {
    weight = s;
    setPriority(true);
}

int _Http2Frame::getWeight() const {
    return weight;
}

Http2FrameByteArray _Http2Frame::toFrameData() {
    ByteArray payload = toByteArray();
    int len = 0;
    //setting ack frame has no payload
    if(payload != nullptr && payload->size() != 0) {
        len = payload->size();
    }

    Http2FrameByteArray frame = createHttp2FrameByteArray(len + 9);
    ByteArrayWriter writer = createByteArrayWriter(frame,st(Defination)::BigEndian);
    writer->write((uint32_t)(len << 8 | type));
    writer->write((byte)flags);
    writer->write((uint32_t)(streamid & 0x7FFFFFFF));
    if(payload != nullptr) {
        writer->write(payload);
    }

    frame->setPriorityWeight(weight);
    frame->setType(type);

    return frame;
}

int _Http2Frame::getType() const {
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
