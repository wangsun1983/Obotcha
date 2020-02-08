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
#include "ByteArray.hpp"

namespace obotcha {

    const String _WebSocketProtocol::ACCEPT_MAGIC = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

    void _WebSocketProtocol::toggleMask(ByteArray buffer, ByteArray key) {
        int keyLength = key->size();
        int byteCount = buffer->size();
        int frameBytesRead = 0;
        for (int i = 0; i < byteCount; i++, frameBytesRead++) {
            int keyIndex = (int) (frameBytesRead % keyLength);
            buffer->fill(i,(byte) (buffer->at(i) ^ key->at(keyIndex)));
        }
    }

}

