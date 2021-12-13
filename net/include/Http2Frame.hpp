#ifndef __OBOTCHA_HTTP_V2_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HashMap.hpp"

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
    
    _Http2Frame();

    int getType();
    int getLength();
    void setLength(int);

    uint32_t getFlags();
    void setFlags(uint32_t);

    uint32_t getStreamId();
    void setStreamId(uint32_t);

    void setExclusive(bool);
    bool getExclusive();

    uint32_t getDependency();
    void setDependency(uint32_t);

    void setEndStream(bool);
    bool isEndStream();

    void setEndHeaders(bool);
    bool isEndHeaders();

    void setAck(bool);
    bool isAck();

    void setPadding(bool);
    bool isPadding();

    void setPriority(bool);
    bool isPrioroty();

    void setWeight(int);
    int getWeight();

    ByteArray toFrameData(int streamid = 0x0,int flags = FlagNone);
    virtual void import(ByteArray);
    
protected:
    virtual ByteArray toByteArray() = 0;
    int type;
    int flags;
    int length;
    int weight;
    bool exclusive;
    uint32_t dependency;

    uint32_t streamid;
};

}

#endif
