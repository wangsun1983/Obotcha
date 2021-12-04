#include "Http2Frame.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

/* Common frame format
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|  Type (8)     |  Flags (8)    |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============================================================+
|                  Frame Payload (0...)                       ...
+---------------------------------------------------------------+
 */

ByteArray _Http2Frame::toFrameData(int streamid,int flags) {
    ByteArray payload = toByteArray();
    int length = 0;
    //setting ack frame has no payload
    if(payload != nullptr) {
        length = payload->size();
    }
    ByteArray frame = createByteArray(length + 9);
    printf("to framedata size is %d \n",frame->size());
    ByteArrayWriter writer = createByteArrayWriter(frame,BigEndian);
    writer->writeUint32(length << 8 | type);
    if(mAck) {
        flags |= 1;
    }
    writer->writeByte(flags);
    writer->writeUint32(streamid & 0x7FFFFFFF);
    if(payload != nullptr) {
        writer->writeByteArray(payload);
    }

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

void _Http2Frame::setAck(bool s) {
    mAck = s;
}

bool _Http2Frame::isAck() {
    return mAck;
}

}
