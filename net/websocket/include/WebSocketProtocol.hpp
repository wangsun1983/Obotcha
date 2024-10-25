#ifndef __OBOTCHA_WEBSOCKET_PROTOCOL_HPP__
#define __OBOTCHA_WEBSOCKET_PROTOCOL_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketProtocol) {
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
    static const int B0_FLAG_FIN = 0b10000000;

    /** Byte 0 reserved flag 1. Must be 0 unless negotiated otherwise. */
    static const int B0_FLAG_RSV1 = 0b01000000;

    /** Byte 0 reserved flag 2. Must be 0 unless negotiated otherwise. */
    static const int B0_FLAG_RSV2 = 0b00100000;

    /** Byte 0 reserved flag 3. Must be 0 unless negotiated otherwise. */
    static const int B0_FLAG_RSV3 = 0b00010000;

    /** Byte 0 mask for the frame opcode. */
    static const int B0_MASK_OPCODE = 0b00001111;

    /** Flag in the opcode which indicates a control frame. */
    static const int OPCODE_FLAG_CONTROL = 0b00001000;

    /**
     * Byte 1 flag for whether the payload data is masked.
     * <p>
     * If this flag is set, the next four bytes represent the mask key. These
     * bytes appear after any additional bytes specified by {@link
     * #B1_MASK_LENGTH}.
     */
    static const int B1_FLAG_MASK = 0b10000000;

    /**
     * Byte 1 mask for the payload length.
     * <p>
     * If this value is {@link #PAYLOAD_SHORT}, the next two bytes represent the
     * length. If this value is {@link #PAYLOAD_LONG}, the next eight bytes
     * represent the length.
     */
    static const int B1_MASK_LENGTH = 0b01111111;

    static const int OPCODE_CONTINUATION = 0x0;

    static const int OPCODE_TEXT = 0x1;

    static const int OPCODE_BINARY = 0x2;

    static const int OPCODE_CONTROL_CLOSE = 0x8;

    static const int OPCODE_CONTROL_PING = 0x9;

    static const int OPCODE_CONTROL_PONG = 0xa;

    /**
     * Maximum length of frame payload. Larger payloads, if supported by the
     * frame type, can use the special values {@link #PAYLOAD_SHORT} or {@link
     * #PAYLOAD_LONG}.
     */
    static const long PAYLOAD_BYTE_MAX = 125L;

    /**
     * Value for {@link #B1_MASK_LENGTH} which indicates the next two bytes are
     * the unsigned length.
     */
    static const int PAYLOAD_SHORT = 126;

    /** Maximum length of a frame payload to be denoted as {@link
     * #PAYLOAD_SHORT}. */
    static const long PAYLOAD_SHORT_MAX = 0xffffL;

    /**
     * Value for {@link #B1_MASK_LENGTH} which indicates the next eight bytes
     * are the unsigned length.
     */
    static const int PAYLOAD_LONG = 127;

    /*
     *
     */
    static const int CLOSE_STATUS_NORMAL = 1000;
    static const int CLOSE_STATUS_GOING_AWAY = 1001;
    static const int CLOSE_STATUS_PROTOCOL_ERROR = 1002;
    static const int CLOSE_STATUS_UNSUPPORTED_DATA_TYPE = 1003;
    static const int CLOSE_STATUS_STATUS_NOT_AVAILABLE = 1005;
    static const int CLOSE_STATUS_ABNORMAL_CLOSED = 1006;
    static const int CLOSE_STATUS_INVALID_PAYLOAD = 1007;
    static const int CLOSE_STATUS_POLICY_VIOLATION = 1008;
    static const int CLOSE_STATUS_MESSAGE_TOO_BIG = 1009;
    static const int CLOSE_STATUS_INVALID_EXTENSION = 1010;
    static const int CLOSE_STATUS_UNEXPECTED_CONDITION = 1011;
    static const int CLOSE_STATUS_SERVICE_RESTART = 1012;
    static const int CLOSE_STATUS_TRY_AGAIN_LATER = 1013;
    static const int CLOSE_STATUS_BAD_GATEWAY = 1014;
    static const int CLOSE_STATUS_TLS_HANDSHAKE_ERROR = 1015;

    enum class Model {
        Server = 0,
        Client
    };
};

} // namespace obotcha
#endif
