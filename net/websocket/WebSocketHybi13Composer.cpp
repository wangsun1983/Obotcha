#include "WebSocketHybi13Composer.hpp"
#include "HttpMethod.hpp"
#include "WebSocketProtocol.hpp"
#include "Byte.hpp"
#include "HttpStatus.hpp"
#include "ByteArrayWriter.hpp"
#include "InfiniteLoop.hpp"
#include "Log.hpp"

namespace obotcha {

_WebSocketHybi13Composer::_WebSocketHybi13Composer(int type,int ver,int maxFrameSize):_WebSocketComposer(type,ver,maxFrameSize){
    mSha = createSha(SHA_1);
    mBase64 = createBase64();
    mRand = createRandom();
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genTextMessage(String content) {
    switch(mType) {
        case st(WebSocketProtocol)::Client:
            return genClientMessage(content->toByteArray(),
                                    st(WebSocketProtocol)::OPCODE_TEXT);

        case st(WebSocketProtocol)::Server:
            return genServerMessage(content->toByteArray(),
                                    st(WebSocketProtocol)::OPCODE_TEXT);
        
        default:
            LOG(ERROR)<<"WebSocketHybi13Composer,genTextMessage unknow type:"<<mType;
            return nullptr;
    }
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genClientMessage(ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();
    ByteArray entireMessage = (mDeflate == nullptr)?content:mDeflate->compress(content);

    byte *pData = entireMessage->toValue();
    int index = 0;
    bool isFirstFrame = true;
    bool isLastFrame = false;
    while(!isLastFrame) {
        int len = (entireMessage->size()-index) > mMaxFrameSize?mMaxFrameSize:(entireMessage->size() - index);
        ByteArray message = createByteArray(pData + index,len);
        index += len;
        if(index == entireMessage->size()) {
            isLastFrame = true;
        }

        ByteArray sink = createByteArray(message->size() + 64);
        ByteArrayWriter sinkWriter = createByteArrayWriter(sink,st(Defination)::BigEndian);

        int b0 = isFirstFrame?type:st(WebSocketProtocol)::OPCODE_CONTINUATION;
        isFirstFrame = false;
        
        if(isLastFrame) {
            b0 |= st(WebSocketProtocol)::B0_FLAG_FIN;
        }

        if(mDeflate != nullptr) {
           b0 |= st(WebSocketProtocol)::B0_FLAG_RSV1; //TODO
        }

        sinkWriter->write<byte>(b0);

        ByteArray maskKey = createByteArray(4);
        int b1 = 0;

        //client message need use mask.
        b1 = st(WebSocketProtocol)::B1_FLAG_MASK;
        mRand->nextBytes(maskKey);

        int byteCount = message->size();
        if (byteCount <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
            b1 |= byteCount;
            sinkWriter->write<byte>(b1);
        } else if (byteCount <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
            b1 |= st(WebSocketProtocol)::PAYLOAD_SHORT;
            sinkWriter->write<byte>(b1);
            sinkWriter->write<short int>(byteCount);
        } else {
            b1 |= st(WebSocketProtocol)::PAYLOAD_LONG;
            sinkWriter->write<byte>(b1);
            sinkWriter->write<long>(byteCount);
        }

        //client message need use mask.
        sinkWriter->write(maskKey);
        ByteArray maskBuff = createByteArray(message);
        toggleMask(maskBuff,maskKey);
        sinkWriter->write(maskBuff);
        sink->quickShrink(sinkWriter->getIndex());
        genResult->add(sink);
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genServerMessage(ByteArray content,int type) {
    ArrayList<ByteArray> genResult = createArrayList<ByteArray>();

    ByteArray entireMessage = content;

    byte *pData = entireMessage->toValue();
    int index = 0;
    bool isFirstFrame = true;
    bool isLastFrame = false;
    while(!isLastFrame) {
        int len = (entireMessage->size() - index) > mMaxFrameSize?mMaxFrameSize:(entireMessage->size() - index);
        ByteArray message = createByteArray(pData + index,len);
        index += len;
        if(index == entireMessage->size()) {
            isLastFrame = true;
        }

        ByteArray sink = createByteArray(message->size() + 64);
        ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

        int b0 = 0;//formatOpcode|st(WebSocketProtocol)::B0_FLAG_FIN;
        if(isFirstFrame) {
            b0 = type;
            isFirstFrame = false;
        } else {
            b0 = st(WebSocketProtocol)::OPCODE_CONTINUATION;
        }

        if(isLastFrame) {
            b0 |= st(WebSocketProtocol)::B0_FLAG_FIN;
        }

        sinkWriter->write<byte>(b0);

        int b1 = message->size();
        if (b1 <= st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
            sinkWriter->write<byte>(b1);
        } else if (b1 <= st(WebSocketProtocol)::PAYLOAD_SHORT_MAX) {
            sinkWriter->write<byte>(st(WebSocketProtocol)::PAYLOAD_SHORT);
            sinkWriter->write<short int>(b1);
        } else {
            sinkWriter->write<byte>(st(WebSocketProtocol)::PAYLOAD_BYTE_MAX);
            sinkWriter->write<long>(b1);
        }

        sinkWriter->write(message);
        sink->quickShrink(sinkWriter->getIndex());

        genResult->add(sink);
    }

    return genResult;
}

ArrayList<ByteArray> _WebSocketHybi13Composer::genBinaryMessage(ByteArray content) {
    switch(mType) {
        case st(WebSocketProtocol)::Client:
            return genClientMessage(content,
                                    st(WebSocketProtocol)::OPCODE_BINARY);

        case st(WebSocketProtocol)::Server:
            return genServerMessage(content,
                                    st(WebSocketProtocol)::OPCODE_BINARY);
        
        default:
            LOG(ERROR)<<"WebSocketHybi13Composer genBinaryMessage unknow type:"<<mType;
            return nullptr;
    }
}

ByteArray _WebSocketHybi13Composer::genPingMessage(String msg) {
    switch(mType) {
        case st(WebSocketProtocol)::Client:
        return genClientControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);

        case st(WebSocketProtocol)::Server:
        return genServerControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PING);

        default:
            LOG(ERROR)<<"WebSocketHybi13Composer genPingMessage unknow type:"<<mType;
            return nullptr;
    }
}

ByteArray _WebSocketHybi13Composer::genPongMessage(String msg) {
    switch(mType) {
        case st(WebSocketProtocol)::Client:
        return genClientControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);

        case st(WebSocketProtocol)::Server:
        return genServerControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_PONG);

        default:
            LOG(ERROR)<<"WebSocketHybi13Composer genPongMessage unknow type:"<<mType;
            return nullptr;
    }    
}

ByteArray _WebSocketHybi13Composer::genCloseMessage(String msg) {
    switch(mType) {
        case st(WebSocketProtocol)::Client:
        return genClientControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);

        case st(WebSocketProtocol)::Server:
        return genServerControlMessage(msg->toByteArray(),
                                        st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE);
    
        default:
            LOG(ERROR)<<"WebSocketHybi13Composer genCloseMessage unknow type:"<<mType;
            return nullptr;
    }
}

ByteArray _WebSocketHybi13Composer::genClientControlMessage(ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->write<byte>(b0);

    int b1 = payload->size();
    b1 |= st(WebSocketProtocol)::B1_FLAG_MASK;
    sinkWriter->write<byte>(b1);

    ByteArray maskKey = createByteArray(4);
    mRand->nextBytes(maskKey);
    sinkWriter->write(maskKey);

    if (payload != nullptr) {
        ByteArray maskBuff = createByteArray(payload);
        toggleMask(maskBuff,maskKey);
        sinkWriter->write(maskBuff);
    }

    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

ByteArray _WebSocketHybi13Composer::genServerControlMessage(ByteArray payload,int type) {
    ByteArray sink = createByteArray(payload->size() + 64);
    ByteArrayWriter sinkWriter = createByteArrayWriter(sink);

    int b0 = st(WebSocketProtocol)::B0_FLAG_FIN | type;
    sinkWriter->write<byte>(b0);

    int b1 = payload->size();
    sinkWriter->write<byte>(b1);
    if (payload != nullptr) {
        sinkWriter->write(payload);
    }
    sink->quickShrink(sinkWriter->getIndex());
    return sink;
}

}
