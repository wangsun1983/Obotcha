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
    _Http2FrameOption() = default;
    void setAsDefault();

    void setHeaderTableSize(uint32_t);
    uint32_t getHeaderTableSize() const;

    void setEnablePush(uint32_t);
    uint32_t getEnablePush() const;

    void setMaxConcurrentStreams(uint32_t);
    uint32_t getMaxConcurrentStreams() const;

    void setInitialWindowSize(uint32_t);
    uint32_t getInitialWindowSize() const;

    void setMaxFrameSize(uint32_t);
    uint32_t getMaxFrameSize() const;

    void setMaxHeaderListSize(uint32_t);
    uint32_t getMaxHeaderListSize() const;

    static const uint32_t DefaultHeaderTableSize;
    static const uint32_t DefaultMaxConcurrentStreams;
    static const uint32_t DefaultInitialWindowSize;
    static const uint32_t DefaultMaxFrameSize;
    static const uint32_t DefaultmMaxHeaderListSize;
    static const uint32_t DefaultEnablePush;

protected:
    uint32_t mHeaderTableSize = 0;
    uint32_t mEnablePush = 0;
    uint32_t mMaxConcurrentStreams = 0;
    uint32_t mInitialWindowSize = 0;
    uint32_t mMaxFrameSize = 0;
    uint32_t mMaxHeaderListSize = 0;
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
    explicit _Http2SettingFrame(Http2FrameOption);
    
    void load(ByteArray);
    ByteArray toByteArray();
};

}

#endif
