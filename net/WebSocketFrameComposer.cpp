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
    mSha = createSha(AbstractSHA1);
    mBase64 = createBase64();
    mIsClient = isclient;
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
        st(Random)::nextBytes(maskKey);
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

    sink->qucikShrink(sinkWriter->getIndex());
    return sink;
}

ByteArray _WebSocketFrameComposer::generateMessageFrame(int formatOpcode,ByteArray message) {
    ByteArray sink = createByteArray(message->size() + 14);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    //int b0 = formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
    int b0 = formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
    printf("b0 is %x \n",b0);
    sinkWriter->writeByte(b0);

    int b1 = 0;
    ByteArray maskKey = createByteArray(4);

    if (mIsClient) {
        b1 |= st(WebSocketProtocol)::B1_FLAG_MASK;
        //random.nextBytes(maskKey);
        st(Random)::nextBytes(maskKey);
    }

    int byteCount = message->size();
    printf("byteCount is %x \n",byteCount);
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
        printf("start toggleMask,maskBuff size is %d,message size is %d \n",maskBuff->size(),message->size());
        st(WebSocketProtocol)::toggleMask(maskBuff,maskKey);
        printf("finish toggleMask \n");
        sinkWriter->writeByteArray(maskBuff);
    } else {
        sinkWriter->writeByteArray(message);
    }

    sink->qucikShrink(sinkWriter->getIndex());
    
    return sink;
}


String _WebSocketFrameComposer::generateShakeHandFrame(String key) {
    printf("key is %s \n",key->toChars());
    printf("accept magic is %s \n",st(WebSocketProtocol)::ACCEPT_MAGIC->toChars());
    String key_mgic = key->append(st(WebSocketProtocol)::ACCEPT_MAGIC);
    printf("key_mgic is %s \n",key_mgic->toChars());
    ByteArray sha1_content = mSha->encryptRawData(createByteArray(key_mgic));
    printf("sha1_content is %s \n",sha1_content->toValue());
    String base64 = mBase64->encode(sha1_content)->toString();
    printf("base64 is %s \n",base64->toChars());

    String head = "HTTP/1.1 101 Switching Protocols\r\n";
    String upgrade = head->append("Upgrade: websocket\r\n");
    String connection = upgrade->append("Connection: Upgrade\r\n");
    String resp = connection->append("Sec-WebSocket-Accept:")->append(base64)->append("\r\n\r\n");

    //printf("generate shake resp is %s \n",resp->toChars());
    return resp;
}

}
