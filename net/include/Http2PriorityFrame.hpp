#ifndef __OBOTCHA_HTTP_V2_PRIORITY_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_PRIORITY_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                   0x5 (24)                    |
+---------------+---------------+---------------+
|   0x2 (8)     |    0x0 (8)    |
+-+-------------+---------------+-------------------------------+
|R|                  Stream Identifier (31)                     |
+=+=============================================================+
|E|                  Stream Dependency (31)                     |
+-+-------------+-----------------------------------------------+
| Weight (8)    |
+---------------+
 */

DECLARE_CLASS(Http2PriorityFrame) {

};

}

#endif
