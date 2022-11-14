#ifndef __OBOTCHA_HTTP_V2_PING_HPP__
#define __OBOTCHA_HTTP_V2_PING_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                0x8 (24)                       |
+---------------+---------------+---------------+
|  0x6 (8)      | 0000 000? (8) |
+-+-------------+---------------+-------------------------------+
|R|                          0x0 (32)                           |
+=+=============================================================+
|                        Opaque Data (64)                       |
+---------------------------------------------------------------+
In addition to the frame header, PING frames MUST contain 8 octets of
opaque data in the payload.  A sender can include any value it
chooses and use those octets in any fashion.

 */

DECLARE_CLASS(Http2PingFrame) IMPLEMENTS(Http2Frame){

public:
    _Http2PingFrame();
    void import(ByteArray);
    ByteArray toByteArray();

    ByteArray getInfo();
    void setInfo(ByteArray);

private:
    ByteArray info;
};

}

#endif
