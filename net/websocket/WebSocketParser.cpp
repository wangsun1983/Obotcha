#include "WebSocketParser.hpp"
#include "WebSocketProtocol.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

_WebSocketParser::_WebSocketParser() {
    //mData = nullptr;
    mContinueBuff = nullptr;
    mRingBuff = createByteRingArray(1024*1024*8);
    mReader = createByteRingArrayReader(mRingBuff,Global::BigEndian);
    mHeader = nullptr;
    mStatus = ParseB0B1;
}

void _WebSocketParser::pushParseData(ByteArray data) {
    mRingBuff->push(data);
}

ArrayList<WebSocketFrame> _WebSocketParser::doParse() {
    ArrayList<WebSocketFrame> mFrames = createArrayList<WebSocketFrame>();

    while (mReader->getReadableLength() >= 2) {
        if(mStatus == ParseB0B1||mStatus == ParseFrameLength||mStatus == ParseMask) {
            if(!parseHeader()) {
                break;
            }
        }

        int opcode = mHeader->getOpCode();
        int framesize = mHeader->getFrameLength();
        int headersize = mHeader->getHeadSize();
        
        if(framesize < 0) {
            Trigger(IllegalStateException,"frame is %d",framesize);
        }

        if (opcode == st(WebSocketProtocol)::OPCODE_TEXT) {
            if(parseContent(true)) {
                WebSocketFrame frame = createWebSocketFrame(mHeader,mParseData);
                mFrames->add(frame);
            } else {
                break;
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
            if(parsePingBuff()) {
                WebSocketFrame frame = createWebSocketFrame(mHeader,mParseData);
                mFrames->add(frame);
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_PONG) {
            if(parsePongBuff()) {
                mFrames->add(createWebSocketFrame(mHeader,mParseData));
            }
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE) {
            if(parseContent(false)) {
                WebSocketFrame frame = createWebSocketFrame();
                frame->setHeader(mHeader);
                if(mParseData->size() > 2) {
                    frame->setCloseStatus(mParseData[0]*256 + mParseData[1]);
                    if(mParseData->size() >= 3) {
                        ByteArray data = createByteArray(mParseData,2,mParseData->size() - 2);
                        frame->setData(data);
                    }
                }
                mFrames->add(frame);
                mStatus = ParseB0B1;
            } else {
                break;
            }           
        } else if (opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION
                ||opcode == st(WebSocketProtocol)::OPCODE_BINARY) {
            if(parseContent(false)) {
                if(mContinueBuff == nullptr) {
                    mContinueBuff = mParseData;
                } else {
                    mContinueBuff->append(mParseData);
                }
                if (mHeader->isFinalFrame()) {
                    ByteArray out = mContinueBuff;
                    if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
                        out = parseContinuationContent(out);
                    }

                    WebSocketFrame frame = createWebSocketFrame(mHeader,out);
                    mContinueBuff = nullptr;
                    mFrames->add(frame);
                }
            } else {
                break;
            }
        }
    }

    return mFrames;
}

byte _WebSocketParser::readbyte() {
    byte value = 0;
    mReader->read<byte>(value);
    value = value & 0xff;
    mReader->pop();
    return value;
}

short int _WebSocketParser::readShortInt() {
    short int value = 0;
    mReader->read<short int>(value);
    value = value & 0xffffL;
    mReader->pop();
    return value;
}

long _WebSocketParser::readLong(){
    long value = 0;
    mReader->read<long>(value);
    mReader->pop();
    return value;
}

void _WebSocketParser::unMask(byte *payload,byte *mask,int framesize) {
    for(int i = 0; i < framesize; i++){
	    int j = i % 4;
		payload[i] = payload[i] ^ mask[j];
	}
}

}