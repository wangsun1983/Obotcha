#include "WebSocketHybi13Parser.hpp"
#include "ProtocolNotSupportException.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpMethod.hpp"
#include "Inspect.hpp"

namespace obotcha {

_WebSocketHybi13Parser::_WebSocketHybi13Parser() :_WebSocketParser(),mDeflate(nullptr){

}

/*-----------------------------------------------------------------------------------
* 1.Masking Head Size:
*   1.1 FrameSize <= 125
*       |++++++++++++|++++++++++++++|++++++++++++++++++++++++++++++++|
*          1byte(op)     1byte(size)         4byte(mask)
*
*   1.2 FrameSize = 126
*       |++++++++++++|++++++++++++++|++++++++++++++++++++++++++++|+++++++++++++++++++++++++++++|
*          1byte(op)     1byte(size)         2byte(real size)            4byte(mask)
*
*   1.3 FrameSize > 126
*       |++++++++++++|++++++++++++++|++++++++++++++++++++++++++++|+++++++++++++++++++++++++++++|
*          1byte(op)     1byte(size)         8byte(real size)            4byte(mask)
*
* 2.Unmasking Head Size:
*   2.1 FrameSize <= 125
*       |++++++++++++|++++++++++++++|
*          1byte(op)     1byte(size)
*
*   2.2 FrameSize = 126
*       |++++++++++++|++++++++++++++|++++++++++++++++++++++++++++|
*          1byte(op)     1byte(size)         2byte(real size)
*
*   2.3 FrameSize > 126
*       |++++++++++++|++++++++++++++|++++++++++++++++++++++++++++|
*          1byte(op)     1byte(size)         8byte(real size)
*-----------------------------------------------------------------------------------
*/
bool _WebSocketHybi13Parser::parseHeader() {
    switch(mStatus) {
        case Status::ParseB0: {
            mHeader = createWebSocketHeader();
            byte b0 = readbyte();
            mHeader->setOpCode(b0 & st(WebSocketProtocol)::B0_MASK_OPCODE);
            mHeader->setIsFinalFrame((b0 & st(WebSocketProtocol)::B0_FLAG_FIN) != 0);
            mHeader->setIsControlFrame((b0 & st(WebSocketProtocol)::OPCODE_FLAG_CONTROL) != 0);

            // Control frames must be final frames (cannot contain continuations).
            if (mHeader->getIsControlFrame() && !mHeader->isFinalFrame()) {
                Trigger(ProtocolNotSupportException,"Control frames must be final.")
            }

            mHeader->setReservedFlag1((b0 & st(WebSocketProtocol)::B0_FLAG_RSV1) != 0);
            mHeader->setReservedFlag2((b0 & st(WebSocketProtocol)::B0_FLAG_RSV2) != 0);
            mHeader->setReservedFlag3((b0 & st(WebSocketProtocol)::B0_FLAG_RSV3) != 0);
            mStatus = Status::ParseB1;
        } [[fallthrough]];
        
        case Status::ParseB1: {
            if(!hasData()) {
                break;
            }
            byte b1 = readbyte();
            mHeader->setMasked((b1 & st(WebSocketProtocol)::B1_FLAG_MASK) != 0);
            mHeader->setB1(b1);
            mStatus = Status::ParseFrameLength;
        } [[fallthrough]];

        case Status::ParseFrameLength: {
            // Get frame length, optionally reading from follow-up bytes 
            //if indicated by special values.
            int b1 = mHeader->getB1();
            int frameLength = b1 & st(WebSocketProtocol)::B1_MASK_LENGTH;
            if (frameLength == st(WebSocketProtocol)::PAYLOAD_SHORT) {
                Inspect(mReader->getReadableLength() < sizeof(short int),false)
                //read 16 bits
                mHeader->setFrameLength(readUint16());
            } else if (frameLength == st(WebSocketProtocol)::PAYLOAD_LONG) {
                Inspect(mReader->getReadableLength() < sizeof(long),false)
                mHeader->setFrameLength(readLong());
            } else {
                mHeader->setFrameLength(frameLength);
            }

            mStatus = mHeader->getMasked()?Status::ParseMask:Status::ParseData;
            Inspect(mStatus == Status::ParseData,true)
        }
        [[fallthrough]];
        
        case Status::ParseMask: {
            Inspect(mReader->getReadableLength() < 4,false)
            if(mHeader->getMasked()) {
                mReader->move(4);
                auto maskKey = mReader->pop();
                mHeader->setMaskKey(maskKey);
            }
            mStatus = Status::ParseData;
            return true;
        }
       
        case Status::ParseData: {
            //Do nothing in header parser
        }
    }
    return false;
}

bool _WebSocketHybi13Parser::parseContent(bool isDeflate) {
    long framelength = mHeader->getFrameLength();
    if(framelength == 0) {
        mStatus = Status::ParseB0;
        return true;
    }

    //if frame length is larger than mReader->getReadableLength(),
    //save it to continue buff
    long currentSize = (mContinueBuff == nullptr)?0:mContinueBuff->size();
    if((mReader->getReadableLength() + currentSize)< framelength) {
        mReader->move(mReader->getReadableLength());
        st(ByteArray)::Combine(mContinueBuff,mReader->pop());
        return false;
    }
    
    if(mHeader->getOpCode() != st(WebSocketProtocol)::OPCODE_CONTINUATION) {
        mStatus = Status::ParseB0;
    }

    mReader->move(framelength - currentSize);
    st(ByteArray)::Combine(mContinueBuff,mReader->pop());
    if(mHeader->getMasked()) {
        unMask(mContinueBuff->toValue(),
               mHeader->getMaskKey()->toValue(),
               framelength);
	}
    
    //whether we need do decompose
    if(mDeflate != nullptr && isDeflate) {
        byte trailer[4] = {0x00, 0x00, 0xff, 0xff};
        ByteArray t = createByteArray(trailer,4);
        mContinueBuff->append(t);
        mContinueBuff = mDeflate->decompress(mContinueBuff);
    }
	return true;
}

bool _WebSocketHybi13Parser::parsePingBuff() {
    return parseContent(false);
}

String _WebSocketHybi13Parser::getOrigin(HttpHeader h) {
    auto origin = h->getOrigin();
    return (origin != nullptr)?origin->get()->toString():nullptr;
}

int _WebSocketHybi13Parser::getVersion() {
    return 13;
}

ByteArray _WebSocketHybi13Parser::parseContinuationContent(ByteArray in) {
    //whether we need do decompose
    mStatus = Status::ParseB0;
    if(mDeflate != nullptr) {
        byte trailer[4] = {0x00, 0x00, 0xff, 0xff};
        ByteArray t = createByteArray(trailer,4);
        in->append(t);
        return mDeflate->decompress(in);
    }

	return in;
}

bool _WebSocketHybi13Parser::parsePongBuff() {
    return parseContent(false);
}

}
