#ifndef __OBOTCHA_HTTP_V2_PUSH_PROMISE_HPP__
#define __OBOTCHA_HTTP_V2_PUSH_PROMISE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
#include "Http2Frame.hpp"
#include "HttpHeader.hpp"
#include "HPackEncoder.hpp"
#include "HPackDecoder.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|  0x5 (8)      | 0000 ??00 (8) |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (32)                       |
+=+=============================================================+
|Pad Length? (8)|
+-+-------------+-----------------------------------------------+
|R|                Promised Stream ID (31)                      |
+-+-------------------------------------------------------------+
|                  Header Block Fragment (*)                . . .
+---------------------------------------------------------------+
|                           Padding (*)                     . . .
+---------------------------------------------------------------+
Pad Length:  An 8-bit field containing the length of the frame
      padding in units of octets.  This field is only present if the
      PADDED flag is set.

R: A single reserved bit.

Promised Stream ID:  An unsigned 31-bit integer that identifies the
    stream that is reserved by the PUSH_PROMISE.  The promised stream
    identifier MUST be a valid choice for the next stream sent by the
    sender (see "new stream identifier" in Section 5.1.1).

Header Block Fragment:  A header block fragment (Section 4.3)
    containing request header fields.

Padding:  Padding octets.
 */

DECLARE_CLASS(Http2PushPromiseFrame) IMPLEMENTS(Http2Frame) {

public:
    _Http2PushPromiseFrame(HPackDecoder d = nullptr,HPackEncoder e = nullptr);

    ByteArray toByteArray();
    void import(ByteArray);

    void setHttpHeaders(HttpHeader h);
    HttpHeader getHttpHeaders();

    ByteArray getPaddingData();
    void setPaddingData(ByteArray);

    uint32_t getPromiseStream();
    void setPromiseStream(uint32_t);

public:
    HttpHeader headers;
    ByteArray paddingData;
    
    uint32_t promiseStreamId;

    HPackEncoder encoder;
    HPackDecoder decoder;
};

}

#endif
