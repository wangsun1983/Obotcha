#ifndef __OBOTCHA_HTTP_V2_PING_HPP__
#define __OBOTCHA_HTTP_V2_PING_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
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
 */

DECLARE_CLASS(Http2PingFrame) IMPLEMENTS(Http2Frame){

};

}

#endif
