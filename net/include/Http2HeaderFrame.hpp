#ifndef __OBOTCHA_HTTP_V2_HEADER_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_HEADER_FRAME_HPP__

#include "Object.hpp"
#include "Byte.hpp"
#include "Http2Frame.hpp"
#include "HttpHeader.hpp"
#include "HPackDecoder.hpp"
#include "HPackEncoder.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|    0x1 (8)    | 00?0 ??0? (8) |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============+===============================================+
|Pad Length? (8)|
+-+-------------+-----------------------------------------------+
|E|                 Stream Dependency? (31)                     |
+-+-------------+-----------------------------------------------+
|  Weight? (8)  |
+-+-------------+-----------------------------------------------+
|                   Header Block Fragment (*)                 ...
+---------------------------------------------------------------+
|                           Padding (*)                       ...
+---------------------------------------------------------------+

Pad Length:  An 8-bit field containing the length of the frame
    padding in units of octets.  This field is only present if the
    PADDED flag is set.

E: A single-bit flag indicating that the stream dependency is
    exclusive (see Section 5.3).  This field is only present if the
    PRIORITY flag is set.

Stream Dependency:  A 31-bit stream identifier for the stream that
    this stream depends on (see Section 5.3).  This field is only
    present if the PRIORITY flag is set.

Weight:  An unsigned 8-bit integer representing a priority weight for
    the stream (see Section 5.3).  Add one to the value to obtain a
    weight between 1 and 256.  This field is only present if the
    PRIORITY flag is set.
*/

DECLARE_CLASS(Http2HeaderFrame) IMPLEMENTS(Http2Frame) {
public:
    _Http2HeaderFrame(HPackDecoder decoder = nullptr,HPackEncoder encoder = nullptr);

    ByteArray toByteArray();
    void import(ByteArray); 

    HttpHeader getHeader();
    void setHeader(HttpHeader);

    ByteArray getPaddingData();
    void setPaddingData(ByteArray);

    uint32_t getDependency();
    void setDependency(uint32_t);
    
private:
    HttpHeader headers;
    ByteArray paddingData;
    
    HPackDecoder decoder;
    HPackEncoder encoder;

    uint32_t dependencyStream;
};

}

#endif
