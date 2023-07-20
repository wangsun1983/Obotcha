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


const uint32_t _Http2FrameOption::DefaultHeaderTableSize = 0;
const uint32_t _Http2FrameOption::DefaultMaxConcurrentStreams = 250;
const uint32_t _Http2FrameOption::DefaultInitialWindowSize = 1024*48;
const uint32_t _Http2FrameOption::DefaultMaxFrameSize = 1024*1024*32;
const uint32_t _Http2FrameOption::DefaultmMaxHeaderListSize = 1024*1024;
const uint32_t _Http2FrameOption::DefaultEnablePush = 0;

_Http2FrameOption::_Http2FrameOption() {
    mHeaderTableSize = 0;
    mEnablePush = 0;
    mMaxConcurrentStreams = 0;
    mInitialWindowSize = 0;
    mMaxFrameSize = 0;
    mMaxHeaderListSize = 0;
}

void _Http2FrameOption::setAsDefault() {
    mHeaderTableSize = DefaultHeaderTableSize;
    mEnablePush = DefaultEnablePush;
    mMaxConcurrentStreams = DefaultMaxConcurrentStreams;
    mInitialWindowSize = DefaultInitialWindowSize;
    mMaxFrameSize = DefaultMaxFrameSize;
    mMaxHeaderListSize = DefaultmMaxHeaderListSize;
}

void _Http2FrameOption::setHeaderTableSize(uint32_t v) {
    mHeaderTableSize = v;
}

uint32_t _Http2FrameOption::getHeaderTableSize() {
    return mHeaderTableSize;
}

void _Http2FrameOption::setEnablePush(uint32_t v) {
    mEnablePush = v;
}

uint32_t _Http2FrameOption::getEnablePush() {
    return mEnablePush;
}

void _Http2FrameOption::setMaxConcurrentStreams(uint32_t v) {
    mMaxConcurrentStreams = v;
}

uint32_t _Http2FrameOption::getMaxConcurrentStreams() {
    return mMaxConcurrentStreams;
}

void _Http2FrameOption::setInitialWindowSize(uint32_t v) {
    mInitialWindowSize = v;
}

uint32_t _Http2FrameOption::getInitialWindowSize() {
    return mInitialWindowSize;
}

void _Http2FrameOption::setMaxFrameSize(uint32_t v) {
    mMaxFrameSize = v;
}

uint32_t _Http2FrameOption::getMaxFrameSize() {
    return mMaxFrameSize;
}

void _Http2FrameOption::setMaxHeaderListSize(uint32_t v) {
    mMaxHeaderListSize = v;
}

uint32_t _Http2FrameOption::getMaxHeaderListSize() {
    return mMaxHeaderListSize;
}

//---- Http2SettingFrame ----//
_Http2SettingFrame::_Http2SettingFrame():_Http2Frame(),_Http2FrameOption() {
    this->type = TypeSettings;
}

_Http2SettingFrame::_Http2SettingFrame(Http2FrameOption option) {
    this->type = TypeSettings;
    
    auto headerTableSize = option->getHeaderTableSize();
    if(headerTableSize != 0) {
        setHeaderTableSize(headerTableSize);
    }

    auto enablePush = option->getEnablePush();
    if(enablePush != 0) {
        setEnablePush(enablePush);
    }

    auto maxConcurrentStreams = option->getMaxConcurrentStreams();
    if(maxConcurrentStreams != 0) {
        setMaxConcurrentStreams(maxConcurrentStreams);
    }

    auto initialWindowSize = option->getInitialWindowSize();
    if(initialWindowSize != 0) {
        setInitialWindowSize(initialWindowSize);
    }

    auto maxFrameSize = option->getMaxFrameSize();
    if(maxFrameSize != 0) {
        setMaxFrameSize(maxFrameSize);
    }

    auto maxHeaderListSize = option->getMaxHeaderListSize();
    if(maxHeaderListSize != 0) {
        setMaxHeaderListSize(maxHeaderListSize);
    }
}

void _Http2SettingFrame::load(ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data,Global::BigEndian);
    while(reader->isReadable()) {
        uint16_t identity = reader->read<uint16_t>();
        uint32_t value = reader->read<uint32_t>();
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

}
