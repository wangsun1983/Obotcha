#include "Uint16.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketProtocol.hpp"
#include "IllegalStateException.hpp"
#include "Log.hpp"


namespace obotcha {

const int _WebSocketParser::kDefaultBuffSize = 1024*128;

_WebSocketParser::_WebSocketParser() {
    mRingBuff = createByteRingArray(kDefaultBuffSize);
    mReader = createByteRingArrayReader(mRingBuff,st(Defination)::BigEndian);
}

void _WebSocketParser::pushParseData(ByteArray data) {
    mRingBuff->push(data);
}

ArrayList<WebSocketFrame> _WebSocketParser::doParse() {
    ArrayList<WebSocketFrame> mFrames = createArrayList<WebSocketFrame>();
    while (mReader->getReadableLength() > 0) {
        bool isContinue = false;
        if(mStatus == ParseB0||mStatus == ParseB1||mStatus == ParseFrameLength||mStatus == ParseMask) {
            if(!parseHeader()) {
                break;
            }
        }

        int opcode = mHeader->getOpCode();
        int framesize = mHeader->getFrameLength();
        Panic(framesize < 0,IllegalStateException,"frame is %d",framesize)
        switch(opcode) {
            case st(WebSocketProtocol)::OPCODE_TEXT: {
                if(parseContent(true)) {
                    WebSocketFrame frame = createWebSocketFrame(mHeader,mContinueBuff);
                    mFrames->add(frame);
                    mContinueBuff = nullptr;
                    isContinue = true;
                    mStatus = ParseB0;
                }
            } break;
            
            case st(WebSocketProtocol)::OPCODE_CONTROL_PING: {
                if(parsePingBuff()) {
                    WebSocketFrame frame = createWebSocketFrame(mHeader,mContinueBuff);
                    mFrames->add(frame);
                    mContinueBuff = nullptr;
                    isContinue = true;
                    mStatus = ParseB0;
                }
            } break;
            
            case st(WebSocketProtocol)::OPCODE_CONTROL_PONG: {
                if(parsePongBuff()) {
                    mFrames->add(createWebSocketFrame(mHeader,mContinueBuff));
                    mContinueBuff = nullptr;
                    isContinue = true;
                    mStatus = ParseB0;
                }
            } break;
            
            case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE: {
                if(parseContent(false)) {
                    WebSocketFrame frame = createWebSocketFrame();
                    frame->setHeader(mHeader);
                    if(mContinueBuff->size() > 2) {
                        frame->setCloseStatus(mContinueBuff[0]*256 + mContinueBuff[1]);
                        if(mContinueBuff->size() >= 3) {
                            ByteArray data = createByteArray(mContinueBuff,2,mContinueBuff->size() - 2);
                            frame->setData(data);
                        }
                    }
                    mContinueBuff = nullptr;
                    mFrames->add(frame);
                    mStatus = ParseB0;
                    isContinue = true;
                }           
            } break;
            
            case st(WebSocketProtocol)::OPCODE_CONTINUATION:
            case st(WebSocketProtocol)::OPCODE_BINARY: {
                if(parseContent(false)) {
                    if (mHeader->isFinalFrame()) {
                        ByteArray out = mContinueBuff;
                        if(opcode == st(WebSocketProtocol)::OPCODE_CONTINUATION) {
                            out = parseContinuationContent(out);
                        }

                        WebSocketFrame frame = createWebSocketFrame(mHeader,out);
                        mContinueBuff = nullptr;
                        mFrames->add(frame);
                        mStatus = ParseB0;
                    }
                    isContinue = true;
                }
            } break;

            default:
                LOG(ERROR)<<"WebSocketParser doParse unknow opcode:"<<opcode;
            break;
        }

        if(!isContinue) {
            break;
        }
    }

    return mFrames;
}

bool _WebSocketParser::hasData() {
    return mReader->getReadableLength() > 0;
}

byte _WebSocketParser::readbyte() {
    byte value = 0;
    mReader->read<byte>(value);
    mReader->pop();
    return value;
}

uint16_t _WebSocketParser::readUint16() {
    unsigned short value = 0;
    mReader->read<unsigned short>(value);
    mReader->pop();
    return value;
}

long _WebSocketParser::readLong(){
    long value = 0;
    mReader->read<long>(value);
    mReader->pop();
    return value;
}

void _WebSocketParser::unMask(byte *payload,const byte *mask,int framesize) {
    for(int i = 0; i < framesize; i++){
	    int j = i % 4;
		payload[i] = payload[i] ^ mask[j];
	}
}

}