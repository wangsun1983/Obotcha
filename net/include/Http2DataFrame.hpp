#ifndef __OBOTCHA_HTTP_V2_DATA_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_DATA_FRAME_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
| 0x0 (8)       | 0000 ?00? (8) |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============+===============================================+
|Pad Length? (8)|
+---------------+-----------------------------------------------+
|                            Data (*)                         ...
+---------------------------------------------------------------+
|                          Padding? (*)                       ...
+---------------------------------------------------------------+

Pad Length:  An 8-bit field containing the length of the frame
      padding in units of octets.  This field is conditional (as
      signified by a "?" in the diagram) and is only present if the
      PADDED flag is set.

Data:  Application data.  The amount of data is the remainder of the
    frame payload after subtracting the length of the other fields
    that are present.

Padding:  Padding octets that contain no application semantic value.
    Padding octets MUST be set to zero when sending.  A receiver is
    not obligated to verify padding but MAY treat non-zero padding as
    a connection error (Section 5.4.1) of type PROTOCOL_ERROR.
    
    payload = Padding Length + Data + Padding

 */

DECLARE_CLASS(Http2DataFrame) IMPLEMENTS(Http2Frame){
public:
    _Http2DataFrame();
    ByteArray toByteArray();
    void import(ByteArray);

    ByteArray getData();
    void setData(ByteArray);

    ByteArray getPaddingData();
    void setPaddingData(ByteArray);

private:
    ByteArray data;
    ByteArray paddingData;
};

}

#endif
