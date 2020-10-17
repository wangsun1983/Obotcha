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
#include "WebSocketFrameComposer.hpp"
#include "WebSocketProtocol.hpp"
#include "ByteArrayWriter.hpp"
#include "Random.hpp"
#include "Sha.hpp"

namespace obotcha {

_WebSocketFrameComposer::_WebSocketFrameComposer(bool isclient) {
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
    mIsClient = isclient;
    mRand = createRandom();
}

ByteArray _WebSocketFrameComposer::generateControlFrame(int opcode, ByteArray payload) {
    ByteArray sink = createByteArray(payload->size() + 16);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | opcode;
    sinkWriter->writeByte(b0);

    int b1 = payload->size();
    if (mIsClient) {
        b1 |= st(WebSocketProtocol)::B1_FLAG_MASK;
        sinkWriter->writeByte(b1);

        ByteArray maskKey = createByteArray(4);
        mRand->nextBytes(maskKey);
        sinkWriter->writeByteArray(maskKey);

        if (payload != nullptr) {
            //writeMaskedSynchronized(payload, length);
            ByteArray maskBuff = createByteArray(payload);
            st(WebSocketProtocol)::toggleMask(maskBuff,maskKey);
            sinkWriter->writeByteArray(maskBuff);
        }
    } else {
        sinkWriter->writeByte(b1);
        if (payload != nullptr) {
            sinkWriter->writeByteArray(payload);
        }
    }

    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

ByteArray _WebSocketFrameComposer::generateMessageFrame(int formatOpcode,ByteArray message) {
    ByteArray sink = createByteArray(message->size() + 14);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    //int b0 = formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
    int b0 = formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
    sinkWriter->writeByte(b0);

    int b1 = 0;
    ByteArray maskKey = createByteArray(4);

    if (mIsClient) {
        b1 |= st(WebSocketProtocol)::B1_FLAG_MASK;
        //random.nextBytes(maskKey);
        mRand->nextBytes(maskKey);
    }

    int byteCount = message->size();
    if (byteCount <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
        b1 |= (int) byteCount;
        sinkWriter->writeByte(b1);
    } else if (byteCount <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
        b1 |= st(WebSocketProtocol)::PAYLOAD_SHORT;
        sinkWriter->writeByte(b1);
        sinkWriter->writeShort((int) byteCount);
    } else {
        b1 |= st(WebSocketProtocol)::PAYLOAD_LONG;
        sinkWriter->writeByte(b1);
        sinkWriter->writeLong(byteCount);
    }

    if (mIsClient) {
        sinkWriter->writeByteArray(maskKey);
        //writeMaskedSynchronized(buffer, byteCount);
        ByteArray maskBuff = createByteArray(message);
        st(WebSocketProtocol)::toggleMask(maskBuff,maskKey);
        sinkWriter->writeByteArray(maskBuff);
    } else {
        sinkWriter->writeByteArray(message);
    }

    sink->quickShrink(sinkWriter->getIndex());
    
    return sink;
}


String _WebSocketFrameComposer::generateShakeHandFrame(String key) {
    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    String base64 = mBase64->encode(sha1_content)->toString();
    
    String head = "HTTP/1.1 101 Switching Protocols\r\n";
    String upgrade = head->append("Upgrade: websocket\r\n");
    String connection = upgrade->append("Connection: Upgrade\r\n");
    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n\r\n");

    return resp;
}

}
