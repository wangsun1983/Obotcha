#ifndef __OBOTCHA_HTTP_V2_WINDOW_UPDATE_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_WINDOW_UPDATE_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"

namespace obotcha {

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

DECLARE_CLASS(Http2WindowUpdateFrame) {

};

}

#endif
