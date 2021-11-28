#ifndef __OBOTCHA_HTTP_V2_SETTING_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_SETTING_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
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

DECLARE_CLASS(Http2SettingFrame) IMPLEMENTS(Http2Frame) {
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
    
    void import(ByteArray);
    ByteArray toByteArray();

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

    //void setStandardNum(uint32_t);
    //uint32_t getStandardNum();

private:
    uint32_t mHeaderTableSize;
    uint32_t mEnablePush;
    uint32_t mMaxConcurrentStreams;
    uint32_t mInitialWindowSize;
    uint32_t mMaxFrameSize;
    uint32_t mMaxHeaderListSize;
};

}

#endif
