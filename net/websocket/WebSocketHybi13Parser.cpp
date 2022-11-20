#include "WebSocketHybi13Parser.hpp"
#include "ProtocolNotSupportException.hpp"
#include "WebSocketProtocol.hpp"
#include "HttpMethod.hpp"
#include "Inspect.hpp"

namespace obotcha {

_WebSocketHybi13Parser::_WebSocketHybi13Parser() :_WebSocketParser(),mDeflate(nullptr){

}

bool _WebSocketHybi13Parser::parseHeader() {

    switch(mStatus) {
        case ParseB0B1: {
            mHeader = createWebSocketHeader();
            byte b0 = readbyte();

            mHeader->setOpCode(b0 & st(WebSocketProtocol)::B0_MASK_OPCODE);
            mHeader->setIsFinalFrame((b0 & st(WebSocketProtocol)::B0_FLAG_FIN) != 0);
            mHeader->setIsControlFrame((b0 & st(WebSocketProtocol)::OPCODE_FLAG_CONTROL) != 0);

            // Control frames must be final frames (cannot contain continuations).
            if (mHeader->getIsControlFrame() && !mHeader->isFinalFrame()) {
                Trigger(ProtocolNotSupportException,"Control frames must be final.");
                //TODO
                //return true;
            }

            mHeader->setReservedFlag1((b0 & st(WebSocketProtocol)::B0_FLAG_RSV1) != 0);
            mHeader->setReservedFlag2((b0 & st(WebSocketProtocol)::B0_FLAG_RSV2) != 0);
            mHeader->setReservedFlag3((b0 & st(WebSocketProtocol)::B0_FLAG_RSV3) != 0);

            byte b1 = readbyte();

            mHeader->setMasked((b1 & st(WebSocketProtocol)::B1_FLAG_MASK) != 0);
            mHeader->setB1(b1);
            mStatus = ParseFrameLength;
        }

        case ParseFrameLength: {
            // Get frame length, optionally reading from follow-up bytes 
            //if indicated by special values.
            int b1 = mHeader->getB1();
            int frameLength = b1 & st(WebSocketProtocol)::B1_MASK_LENGTH;

            if (frameLength == st(WebSocketProtocol)::PAYLOAD_SHORT) {
                Inspect(mReader->getReadableLength() < sizeof(short int),false);
                mHeader->setFrameLength(readShortInt());
            } else if (frameLength == st(WebSocketProtocol)::PAYLOAD_LONG) {
                Inspect(mReader->getReadableLength() < sizeof(long),false);
                mHeader->setFrameLength(readLong());
            } else {
                mHeader->setFrameLength(frameLength);
            }

            mStatus = mHeader->getMasked()?ParseMask:ParseData;
            Inspect(mStatus == ParseData,true);
        }

        case ParseMask: {
            Inspect(mReader->getReadableLength() < 4,false);
            if(mHeader->getMasked()) {
                mReader->move(4);
                auto maskKey = mReader->pop();
                mHeader->setMaskKey(maskKey);
            }
            mStatus = ParseData;
        }
        return true;
    }
    return false;
}

bool _WebSocketHybi13Parser::parseContent(bool isDeflate) {
    long framelength = mHeader->getFrameLength();
    if(framelength == 0) {
        mStatus = ParseB0B1;
        mParseData = nullptr;
        return true;
    }
    //TODO if frame length is larger than mReader->getReadableLength(),
    //save it to continue buff?
    Inspect(mReader->getReadableLength() < framelength,false);
    
    if(mHeader->getOpCode() != st(WebSocketProtocol)::OPCODE_CONTINUATION) {
        mStatus = ParseB0B1;
    }

    mReader->move(framelength);
    mParseData = mReader->pop();
    if(mHeader->getMasked()) {
        unMask(mParseData->toValue(),
               mHeader->getMaskKey()->toValue(),
               framelength);
	}
    
    //whether we need do decompose
    if(mDeflate != nullptr && isDeflate) {
        byte trailer[4] = {0x00, 0x00, 0xff, 0xff};
        ByteArray t = createByteArray(trailer,4);
        mParseData->append(t);
        mParseData = mDeflate->decompress(mParseData);
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

// WebSocketPermessageDeflate _WebSocketHybi13Parser::validateExtensions(HttpHeader h) {
//     auto ext = h->getWebSocketExtensions();
//     Inspect(ext == nullptr,nullptr);

//     mDeflate = createWebSocketPermessageDeflate();
//     Inspect(mDeflate->fit(ext->get()),mDeflate);

//     mDeflate = nullptr;
//     return nullptr;
// }

ByteArray _WebSocketHybi13Parser::parseContinuationContent(ByteArray in) {
    //whether we need do decompose
    mStatus = ParseB0B1;
    if(mDeflate != nullptr) {
        byte trailer[4] = {0x00, 0x00, 0xff, 0xff};
        ByteArray t = createByteArray(trailer,4);
        in->append(t);
        ByteArray out = mDeflate->decompress(in);
        return out;
    }

	return in;
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
// bool _WebSocketHybi13Parser::validateEntirePacket(ByteArray pack) {
//     //use ringbuff,do not need validateEntirePacket
//     return true;
// }

// bool _WebSocketHybi13Parser::validateHandShake(HttpHeader h) {
//     Inspect(h->getMethod() != st(HttpMethod)::Get || h->getWebSocketKey() == nullptr,
//             false);
//     return true;
// }

// ArrayList<String> _WebSocketHybi13Parser::extractSubprotocols(HttpHeader h) {
//     ArrayList<String> protocols = createArrayList<String>();
//     auto protocol = h->getWebSocketProtocol();
//     Inspect(protocol == nullptr,nullptr);

//     return protocol->get();
// }

bool _WebSocketHybi13Parser::parsePongBuff() {
    //return parsePingBuff(); //same
    return parseContent(false);
}

}
