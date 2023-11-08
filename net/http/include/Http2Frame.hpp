#ifndef __OBOTCHA_HTTP_V2_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"

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
Length:  The length of the frame payload expressed as an unsigned
      24-bit integer.  Values greater than 2^14 (16,384) MUST NOT be
      sent unless the receiver has set a larger value for
      SETTINGS_MAX_FRAME_SIZE.

      The 9 octets of the frame header are not included in this value.

Type:  The 8-bit type of the frame.  The frame type determines the
    format and semantics of the frame.  Implementations MUST ignore
    and discard any frame that has a type that is unknown.

Flags:  An 8-bit field reserved for boolean flags specific to the
    frame type.

    Flags are assigned semantics specific to the indicated frame type.
    Flags that have no defined semantics for a particular frame type
    MUST be ignored and MUST be left unset (0x0) when sending.

R: A reserved 1-bit field.  The semantics of this bit are undefined,
    and the bit MUST remain unset (0x0) when sending and MUST be
    ignored when receiving.

Stream Identifier:  A stream identifier (see Section 5.1.1) expressed
    as an unsigned 31-bit integer.  The value 0x0 is reserved for
    frames that are associated with the connection as a whole as
    opposed to an individual stream.

The structure and content of the frame payload is dependent entirely
on the frame type.
 */

class _Http2FrameByteArray;

DECLARE_CLASS(Http2Frame) {

public:
    enum Flag {
        /**
         * No flag set.
         */
        None = 0,
        /**
         * The END_STREAM flag.
         */
        EndStream = 0x01,
        /**
         * The END_HEADERS flag.
         */
        EndHeaders = 0x04,
        /**
         * The ACK flag.
         */
        Ack = 0x01,
        /**
         * The PADDED flag.
         */
        Padded = 0x08,
        /**
         * The PRIORITY flag.
         */
        Priority = 0x20
    };

    enum class Type {
        Data = 0x0,
        Headers,
        Priority,
        RstStream,
        Settings,
        PushPromise,
        Ping,
        GoAway,
        WindowUpdate,
        Continuation,
        Max
    };

    explicit _Http2Frame() = default;

    _Http2Frame::Type getType() const;
    int getLength() const;
    void setLength(int);

    uint32_t getFlags() const;
    void setFlags(uint32_t);

    uint32_t getStreamId() const;
    void setStreamId(uint32_t);

    void setExclusive(bool);
    bool getExclusive() const;

    void setEndStream(bool);
    bool isEndStream() const;

    void setEndHeaders(bool);
    bool isEndHeaders() const;

    void setAck(bool);
    bool isAck() const;

    void setPadding(bool);
    bool isPadding() const;

    void setPriority(bool);
    bool isPrioroty() const;

    void setWeight(byte);
    byte getWeight() const;

    sp<_Http2FrameByteArray> toFrameData();
    virtual void load(ByteArray);

    static const byte DefaultWeight;
    static const int MaxWeight;

protected:
    virtual ByteArray toByteArray() = 0;
    Type type = Type::Data;
    int flags = 0;
    int length = 0;
    byte weight = DefaultWeight;
    bool exclusive = false;
    uint32_t dependency;

    uint32_t streamid = 0;
};

}

#endif
