#ifndef __OBOTCHA_HTTP_V2_GO_AWAY_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_GO_AWAY_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|  0x7 (8)      |     0x0 (8)   |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (32)                       |
+=+=============================================================+
|R|                  Last-Stream-ID (31)                        |
+-+-------------------------------------------------------------+
|                      Error Code (32)                          |
+---------------------------------------------------------------+
|                  Additional Debug Data (*)                    |
+---------------------------------------------------------------+
 */

DECLARE_CLASS(Http2GoAwayFrame) {

};

}

#endif
