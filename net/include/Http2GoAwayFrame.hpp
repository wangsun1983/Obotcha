#ifndef __OBOTCHA_HTTP_V2_GO_AWAY_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_GO_AWAY_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
#include "Http2Frame.hpp"

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

DECLARE_CLASS(Http2GoAwayFrame) IMPLEMENTS(Http2Frame){
public:
    _Http2GoAwayFrame();
    void import(ByteArray);
    ByteArray toByteArray();

    uint32_t getLastStreamId();
    void setLastStreamId(uint32_t);

    uint32_t getErrorCode();
    void setErrorCode(uint32_t);

    void setDebugData(ByteArray);
    ByteArray getDebugData();

private:
    uint32_t lastStreamId;
    uint32_t errorCode;
    ByteArray additionalDebugData;
};

}

#endif
