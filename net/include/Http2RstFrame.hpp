#ifndef __OBOTCHA_HTTP_V2_RST_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_RST_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                0x4 (24)                       |
+---------------+---------------+---------------+
|  0x3  (8)     |  0x0 (8)      |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============================================================+
|                        Error Code (32)                        |
+---------------------------------------------------------------+
 */

DECLARE_CLASS(Http2RstFrame) IMPLEMENTS(Http2Frame) {
public:
    void import(ByteArray);
    ByteArray toByteArray();

    int getErrorCode();
    void setErrorCode(int);
private:
    uint32_t errcode;
};

}

#endif
