#ifndef __OBOTCHA_HTTP_V2_WINDOW_UPDATE_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_WINDOW_UPDATE_FRAME_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

DECLARE_CLASS(Http2WindowUpdateOption) {
public:
    _Http2WindowUpdateOption();
    uint32_t getWindowSize();
    void setWindowSize(uint32_t);
    static const uint32_t DeafaultWindowSize;
private:
    uint32_t windowSize;
};

/*
+-----------------------------------------------+
|                0x4 (24)                       |
+---------------+---------------+---------------+
|   0x8 (8)     |    0x0 (8)    |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============================================================+
|R|              Window Size Increment (31)                     |
+-+-------------------------------------------------------------+
 */

DECLARE_CLASS(Http2WindowUpdateFrame) IMPLEMENTS(Http2Frame,Http2WindowUpdateOption) {
public:
    _Http2WindowUpdateFrame();
    void import(ByteArray);
    ByteArray toByteArray();
};

}

#endif
