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
_Http2SettingFrame::_Http2SettingFrame() {
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
    printf("reader size is %d \n",reader->getRemainSize());
    while(reader->getRemainSize() > 0) {
        uint16_t identity = reader->readUint16();
        uint32_t value = reader->readUint32();
        printf("identity is %d,value is %d \n",identity,value);
        switch(identity) {
            case SettingHeaderTableSize:
                mHeaderTableSize = value;
                printf("mHeaderTableSize is %d \n",mHeaderTableSize);
            break;

            case SettingEnablePush:
                mEnablePush = value;
                printf("mEnablePush is %d \n",mEnablePush);
            break;

            case SetttingMaxConcurrentStreams:
                mMaxConcurrentStreams = value;
                printf("mMaxConcurrentStreams is %d \n",mMaxConcurrentStreams);
            break;

            case SettingInitialWindowSize:
                mInitialWindowSize = value;
                printf("mInitialWindowSize is %d \n",mInitialWindowSize);
            break;

            case SettingMaxFrameSize:
                mMaxFrameSize = value;
                printf("mMaxFrameSize is %d \n",mMaxFrameSize);
            break;

            case SettingMaxHeaderListSize:
                mMaxHeaderListSize = value;
                printf("mMaxHeaderListSize is %d \n",mMaxHeaderListSize);
            break;
            
            default:
            break;
        }
    }
}

ByteArray _Http2SettingFrame::toByteArray() {
    ByteArray data = createByteArray(48 * SettingStandardNum);
    ByteArrayWriter writer = createByteArrayWriter(data);

    if(mHeaderTableSize > 0) {
        writer->writeUint16(SettingHeaderTableSize);
        writer->writeUint32(mHeaderTableSize);
    }

    if(mEnablePush > 0) {
        writer->writeUint16(SettingEnablePush);
        writer->writeUint32(mEnablePush);
    }

    if(mMaxConcurrentStreams > 0) {
        writer->writeUint16(SetttingMaxConcurrentStreams);
        writer->writeUint32(mMaxConcurrentStreams);
    }

    if(mInitialWindowSize > 0) {
        writer->writeUint16(SettingInitialWindowSize);
        writer->writeUint32(mInitialWindowSize);
    }

    if(mMaxFrameSize > 0) {
        writer->writeUint16(SettingMaxFrameSize);
        writer->writeUint32(mMaxFrameSize);
    }

    if(mMaxHeaderListSize > 0) {
        writer->writeUint16(SettingMaxHeaderListSize);
        writer->writeUint32(mMaxHeaderListSize);
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
