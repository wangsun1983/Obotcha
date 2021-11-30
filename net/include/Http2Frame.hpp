#ifndef __OBOTCHA_HTTP_V2_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ByteRingArrayReader.hpp"

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

public:
    enum Flag {
        /**
         * No flag set.
         */
        FlagNone = 0,
        /**
         * The END_STREAM flag.
         */
        FlagEndStream = 0x01,
        /**
         * The END_HEADERS flag.
         */
        FlagEndHeaders = 0x04,
        /**
         * The ACK flag.
         */
        FlagAck = 0x01,
        /**
         * The PADDED flag.
         */
        FlagPadded = 0x08,
        /**
         * The PRIORITY flag.
         */
        FlagPriority = 0x20
    };

    enum Type {
        TypeData = 0x0,
        TypeHeaders,
        TypePriority,
        TypeRstStream,
        TypeSettings,
        TypePushPromise,
        TypePing,
        TypeGoAway,
        TypeWindowUpdate,
        TypeContinuation,
        TypeMax
    };

    int getType();
    int getLength();
    void setLength(int);

    uint32_t getFlags();
    void setFlags(uint32_t);

    ByteArray toFrameData(int streamid = 0x0,int flags = FlagNone);

protected:
    virtual ByteArray toByteArray() = 0;
    int type;
    int flags;
    int length;
};

}

#endif
