#include "WebSocketParser.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {

_WebSocketParser::_WebSocketParser() {
    mData = nullptr;
    mContinueBuff = nullptr;
    mReader = nullptr;
    mHeader = nullptr;
}

void _WebSocketParser::pushParseData(ByteArray data) {
    if(mData == nullptr) {
        mData = data;
    } else {
        mData->append(data);
    }

    mReader = createByteArrayReader(mData,Global::BigEndian);
}

ArrayList<WebSocketFrame> _WebSocketParser::doParse() {
    ArrayList<WebSocketFrame> mFrames = createArrayList<WebSocketFrame>();

    while (1) {
        int readIndex = 0;
        if (!validateEntirePacket(mData)) {
            break;
        }

        WebSocketHeader header = parseHeader();

        int opcode = header->getOpCode();
        int framesize = header->getFrameLength();
        int headersize = header->getHeadSize();

        if (opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            ByteArray msgData = parseContent(true);
            WebSocketFrame frame = createWebSocketFrame(header,msgData);
            mFrames->add(frame);
        } else if (opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
            if (header->isFinalFrame()) {
                ByteArray msgData = parseContent(true);
                WebSocketFrame frame = createWebSocketFrame(header,msgData);
                mFrames->add(frame);
            } else {
                ByteArray msgData = parseContent(false);
                if(mContinueBuff == nullptr) {
                    mContinueBuff = msgData;
                } else {
                    mContinueBuff->append(msgData);
                }
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            ByteArray buff = parsePingBuff();
            WebSocketFrame frame = createWebSocketFrame(header,buff);
            mFrames->add(frame);
            //if (mWsListener->onPing(client, buff->toString()) == PingResultResponse) {
            //    ByteArray resp = client->getComposer()->genPongMessage(client,buff->toString());
            //    send(fd,resp->toValue(),resp->size(),0);
            //}
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            ByteArray pong = parsePongBuff();
            //String msg = pong->toString();
            //mWsListener->onPong(client, msg);
            mFrames->add(createWebSocketFrame(header,pong));
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            //isRmClient = true;
            //TODO
            WebSocketFrame frame = createWebSocketFrame();
            frame->setHeader(header);
            mFrames->add(frame);
            break;
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
            ByteArray msgData = parseContent(false);
            //WebSocketBuffer continuebuff = client->getContinueBuffer();
            //continuebuff->mBuffer->append(msgData);
            if(mContinueBuff == nullptr) {
                mContinueBuff = msgData;
            } else {
                mContinueBuff->append(msgData);
            }

            if (header->isFinalFrame()) {
                ByteArray out = validateContinuationContent(mContinueBuff);
                WebSocketFrame frame = createWebSocketFrame(header,out);
                //mWsListener->onData(client, frame);
                //continuebuff->mBuffer = nullptr;
                mFrames->add(frame);
            }
        }

        // check whether there are two ws messages received in one buffer!
        // len -= (framesize + headersize);
        int resetLength = (mData->size() - (framesize + headersize));
        readIndex += (framesize + headersize);
        
        if (resetLength > 0) {
            byte *pdata = mData->toValue();
            mData = createByteArray(&pdata[readIndex], resetLength);
            mReader = createByteArrayReader(mData,Global::BigEndian);
            continue;
        } else {
            mData = nullptr;
        }

        //client->setDefferedBuffer(nullptr);
        break;
    }

    return mFrames;
}

}
