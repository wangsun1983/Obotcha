#include "Http2SettingFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|     0x4 (8)   | 0000 000? (8) |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier/0x0 (32)                   |
+=+=============================+===============================+
|       Identifier (16)         |
+-------------------------------+-------------------------------+
|                        Value (32)                             |
+---------------------------------------------------------------+
|       Identifier (16)         |
+-------------------------------+-------------------------------+
|                        Value (32)                             |
+---------------------------------------------------------------+
 */
//https://skyao.io/learning-http2/frame/definition/settings.html

_Http2SettingFrame::_Http2SettingFrame():_Http2Frame() {
    mHeaderTableSize = 0;
    mEnablePush = 0;
    mMaxConcurrentStreams = 0;
    mInitialWindowSize = 0;
    mMaxFrameSize = 0;
    mMaxHeaderListSize = 0;

    this->type = TypeSettings;
}

void _Http2SettingFrame::import(ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data,Global::BigEndian);
    while(reader->isReadable()) {
        uint16_t identity = reader->readUint16();
        uint32_t value = reader->readUint32();
        switch(identity) {
            case SettingHeaderTableSize:
                mHeaderTableSize = value;
            break;

            case SettingEnablePush:
                mEnablePush = value;
            break;

            case SetttingMaxConcurrentStreams:
                mMaxConcurrentStreams = value;
            break;

            case SettingInitialWindowSize:
                mInitialWindowSize = value;
            break;

            case SettingMaxFrameSize:
                mMaxFrameSize = value;
            break;

            case SettingMaxHeaderListSize:
                mMaxHeaderListSize = value;
            break;

            default:
            break;
        }
    }
}

ByteArray _Http2SettingFrame::toByteArray() {
    ByteArray data = createByteArray(48 * SettingStandardNum);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);

    if(mHeaderTableSize > 0) {
        writer->write<uint32_t>(SettingHeaderTableSize);
        writer->write<uint32_t>(mHeaderTableSize);
    }

    if(mEnablePush > 0) {
        writer->write<uint16_t>(SettingEnablePush);
        writer->write<uint32_t>(mEnablePush);
    }

    if(mMaxConcurrentStreams > 0) {
        writer->write<uint16_t>(SetttingMaxConcurrentStreams);
        writer->write<uint32_t>(mMaxConcurrentStreams);
    }

    if(mInitialWindowSize > 0) {
        writer->write<uint16_t>(SettingInitialWindowSize);
        writer->write<uint32_t>(mInitialWindowSize);
    }

    if(mMaxFrameSize > 0) {
        writer->write<uint16_t>(SettingMaxFrameSize);
        writer->write<uint32_t>(mMaxFrameSize);
    }

    if(mMaxHeaderListSize > 0) {
        writer->write<uint16_t>(SettingMaxHeaderListSize);
        writer->write<uint32_t>(mMaxHeaderListSize);
    }

    data->quickShrink(writer->getIndex());
    return data;
}

void _Http2SettingFrame::setHeaderTableSize(uint32_t v) {
    mHeaderTableSize = v;
}

uint32_t _Http2SettingFrame::getHeaderTableSize() {
    return mHeaderTableSize;
}

void _Http2SettingFrame::setEnablePush(uint32_t v) {
    mEnablePush = v;
}

uint32_t _Http2SettingFrame::getEnablePush() {
    return mEnablePush;
}

void _Http2SettingFrame::setMaxConcurrentStreams(uint32_t v) {
    mMaxConcurrentStreams = v;
}

uint32_t _Http2SettingFrame::getMaxConcurrentStreams() {
    return mMaxConcurrentStreams;
}

void _Http2SettingFrame::setInitialWindowSize(uint32_t v) {
    mInitialWindowSize = v;
}

uint32_t _Http2SettingFrame::getInitialWindowSize() {
    return mInitialWindowSize;
}

void _Http2SettingFrame::setMaxFrameSize(uint32_t v) {
    mMaxFrameSize = v;
}

uint32_t _Http2SettingFrame::getMaxFrameSize() {
    return mMaxFrameSize;
}

void _Http2SettingFrame::setMaxHeaderListSize(uint32_t v) {
    mMaxHeaderListSize = v;
}

uint32_t _Http2SettingFrame::getMaxHeaderListSize() {
    return mMaxHeaderListSize;
}

}
