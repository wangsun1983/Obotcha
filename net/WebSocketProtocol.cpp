#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

#include "WebSocketProtocol.hpp"

namespace obotcha {

    const String _WebSocketProtocol::ACCEPT_MAGIC = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
  
    const int _WebSocketProtocol::B0_FLAG_FIN = 0b10000000;
  
    const int _WebSocketProtocol::B0_FLAG_RSV1 = 0b01000000;
  
    const int _WebSocketProtocol::B0_FLAG_RSV2 = 0b00100000;
  
    const int _WebSocketProtocol::B0_FLAG_RSV3 = 0b00010000;

    const int _WebSocketProtocol::B0_MASK_OPCODE = 0b00001111;

    const int _WebSocketProtocol::OPCODE_FLAG_CONTROL = 0b00001000;

    const int _WebSocketProtocol::B1_FLAG_MASK = 0b10000000;
  
    const int _WebSocketProtocol::B1_MASK_LENGTH = 0b01111111;

    const int _WebSocketProtocol::OPCODE_CONTINUATION = 0x0;

    const int _WebSocketProtocol::OPCODE_TEXT = 0x1;

    const int _WebSocketProtocol::OPCODE_BINARY = 0x2;

    const int _WebSocketProtocol::OPCODE_CONTROL_CLOSE = 0x8;

    const int _WebSocketProtocol::OPCODE_CONTROL_PING = 0x9;
    
    const int _WebSocketProtocol::OPCODE_CONTROL_PONG = 0xa;

    const long _WebSocketProtocol::PAYLOAD_BYTE_MAX = 125L;
  
    const int _WebSocketProtocol::PAYLOAD_SHORT = 126;
  
    const long _WebSocketProtocol::PAYLOAD_SHORT_MAX = 0xffffL;
  
    const int _WebSocketProtocol::PAYLOAD_LONG = 127;

}

