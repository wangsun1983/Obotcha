#ifndef __OBOTCHA_HTTP_V2_CONTINUATION_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_CONTINUATION_FRAME_HPP__

#include "Object.hpp"
#include "Byte.hpp"
#include "Http2Frame.hpp"
#include "HPackDecoder.hpp"
#include "HPackEncoder.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|  0x9 (8)      |  0x0/0x4  (8) |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (32)                       |
+=+=============================================================+
|                  Header Block Fragment (*)                    |
+---------------------------------------------------------------+
 */

DECLARE_CLASS(Http2ContinuationFrame) IMPLEMENTS(Http2Frame){

public:
    _Http2ContinuationFrame(HPackDecoder d = nullptr,HPackEncoder e = nullptr);
    void load(ByteArray);
    ByteArray toByteArray();

    // void setHeaders(HttpHeader);
    // HttpHeader getHeaders();

    ByteArray getHeadBlockFragment();
    void setHeadBlockFragment(ByteArray data);

private:
    HPackDecoder decoder;
    HPackEncoder encoder;
    HttpHeader headers;
    ByteArray mHeadBlockFragment;
};

}

#endif
