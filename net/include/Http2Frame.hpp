#ifndef __OBOTCHA_HTTP_V2_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

/* Common frame format
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|  Type (8)     |  Flags (8)    |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============================================================+
|                  Frame Payload (0...)                       ...
+---------------------------------------------------------------+
 */

DECLARE_CLASS(Http2Frame) {

};

}

#endif
