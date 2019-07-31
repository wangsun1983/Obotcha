#ifndef __WEBSOCKET_PROTOCOL_HPP__
#define __WEBSOCKET_PROTOCOL_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"

#include "String.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(WebSocketProtocol) {
public:
    /** Magic value which must be appended to the key in a response header. */
    static const String ACCEPT_MAGIC;

    /*
    Each frame starts with two bytes of data.

    0 1 2 3 4 5 6 7    0 1 2 3 4 5 6 7
    +-+-+-+-+-------+  +-+-------------+
    |F|R|R|R| OP    |  |M| LENGTH      |
    |I|S|S|S| CODE  |  |A|             |
    |N|V|V|V|       |  |S|             |
    | |1|2|3|       |  |K|             |
    +-+-+-+-+-------+  +-+-------------+
    */

    /** Byte 0 flag for whether this is the final fragment in a message. */
    static const int B0_FLAG_FIN;

    /** Byte 0 reserved flag 1. Must be 0 unless negotiated otherwise. */
    static const int B0_FLAG_RSV1;

    /** Byte 0 reserved flag 2. Must be 0 unless negotiated otherwise. */
    static const int B0_FLAG_RSV2;
    
    /** Byte 0 reserved flag 3. Must be 0 unless negotiated otherwise. */
    static const int B0_FLAG_RSV3;

    /** Byte 0 mask for the frame opcode. */
    static const int B0_MASK_OPCODE;

    /** Flag in the opcode which indicates a control frame. */
    static const int OPCODE_FLAG_CONTROL;

    /**
     * Byte 1 flag for whether the payload data is masked.
     * <p>
     * If this flag is set, the next four bytes represent the mask key. These bytes appear after
     * any additional bytes specified by {@link #B1_MASK_LENGTH}.
     */
    static const int B1_FLAG_MASK;

    /**
     * Byte 1 mask for the payload length.
     * <p>
     * If this value is {@link #PAYLOAD_SHORT}, the next two bytes represent the length.
     * If this value is {@link #PAYLOAD_LONG}, the next eight bytes represent the length.
     */
    static const int B1_MASK_LENGTH;

    static const int OPCODE_CONTINUATION;
    static const int OPCODE_TEXT;
    static const int OPCODE_BINARY;

    static const int OPCODE_CONTROL_CLOSE;
    static const int OPCODE_CONTROL_PING;
    static const int OPCODE_CONTROL_PONG;

    /**
     * Maximum length of frame payload. Larger payloads, if supported by the frame type, can use the
     * special values {@link #PAYLOAD_SHORT} or {@link #PAYLOAD_LONG}.
     */
    static const long PAYLOAD_BYTE_MAX;
  
    /**
     * Value for {@link #B1_MASK_LENGTH} which indicates the next two bytes are the unsigned length.
     */
    static const int PAYLOAD_SHORT;

    /** Maximum length of a frame payload to be denoted as {@link #PAYLOAD_SHORT}. */
    static const long PAYLOAD_SHORT_MAX;
  
    /**
     * Value for {@link #B1_MASK_LENGTH} which indicates the next eight bytes are the unsigned
     * length.
     */
    static const int PAYLOAD_LONG;

    static void toggleMask(ByteArray buffer, ByteArray key);
};

}
#endif
