#ifndef __OBOTCHA_HTTP_V2_SETTING_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_SETTING_FRAME_HPP__

#include "Object.hpp"
#include "Http2Frame.hpp"
#include "ByteArray.hpp"

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

DECLARE_CLASS(Http2FrameOption) {
public:
    _Http2FrameOption();
    void setAsDefault();

    void setHeaderTableSize(uint32_t);
    uint32_t getHeaderTableSize();

    void setEnablePush(uint32_t);
    uint32_t getEnablePush();

    void setMaxConcurrentStreams(uint32_t);
    uint32_t getMaxConcurrentStreams();

    void setInitialWindowSize(uint32_t);
    uint32_t getInitialWindowSize();

    void setMaxFrameSize(uint32_t);
    uint32_t getMaxFrameSize();

    void setMaxHeaderListSize(uint32_t);
    uint32_t getMaxHeaderListSize();

    static const uint32_t DefaultHeaderTableSize;
    static const uint32_t DefaultMaxConcurrentStreams;
    static const uint32_t DefaultInitialWindowSize;
    static const uint32_t DefaultMaxFrameSize;
    static const uint32_t DefaultmMaxHeaderListSize;
    static const uint32_t DefaultEnablePush;

protected:
    uint32_t mHeaderTableSize;
    uint32_t mEnablePush;
    uint32_t mMaxConcurrentStreams;
    uint32_t mInitialWindowSize;
    uint32_t mMaxFrameSize;
    uint32_t mMaxHeaderListSize;
};

DECLARE_CLASS(Http2SettingFrame) IMPLEMENTS(Http2Frame,Http2FrameOption) {
public:
    enum {
        SettingHeaderTableSize = 0,
        SettingEnablePush,
        SetttingMaxConcurrentStreams,
        SettingInitialWindowSize,
        SettingMaxFrameSize,
        SettingMaxHeaderListSize,
        SettingStandardNum
    };

    _Http2SettingFrame();
    _Http2SettingFrame(Http2FrameOption);
    
    void import(ByteArray);
    ByteArray toByteArray();
};

}

#endif
