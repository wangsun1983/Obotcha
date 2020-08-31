#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketProtocol.hpp"


namespace obotcha {

WebSocketHeader _WebSocketHybi13Parser::parseHeader() {
    WebSocketHeader header = createWebSocketHeader();

    int b0 = mReader->readByte() & 0xff;
    header->setOpCode(b0 & st(WebSocketProtocol)::B0_MASK_OPCODE);
    
    header->setIsFinalFrame((b0 & st(WebSocketProtocol)::B0_FLAG_FIN) != 0);
    header->setIsControlFrame((b0 & st(WebSocketProtocol)::OPCODE_FLAG_CONTROL) != 0);

    // Control frames must be final frames (cannot contain continuations).
    if (header->getIsControlFrame() && !header->isFinalFrame()) {
        //throw new ProtocolException("Control frames must be final.");
        return header;
    }
    
    header->setReservedFlag1((b0 & st(WebSocketProtocol)::B0_FLAG_RSV1) != 0);
    header->setReservedFlag2((b0 & st(WebSocketProtocol)::B0_FLAG_RSV2) != 0);
    header->setReservedFlag3((b0 & st(WebSocketProtocol)::B0_FLAG_RSV3) != 0);
    
    int b1 = mReader->readByte() & 0xff;
    
    header->setMasked((b1 & st(WebSocketProtocol)::B1_FLAG_MASK) != 0);
    
    // Get frame length, optionally reading from follow-up bytes if indicated by special values.
    long frameLength = b1 & st(WebSocketProtocol)::B1_MASK_LENGTH;
    
    if (frameLength == st(WebSocketProtocol)::PAYLOAD_SHORT) {
        header->setFrameLength(mReader->readShort() & 0xffffL); // Value is unsigned.
    } else if (frameLength == st(WebSocketProtocol)::PAYLOAD_LONG) {
        frameLength = mReader->readLong();
        if (frameLength < 0) {
            return nullptr;
        }

        header->setFrameLength(frameLength);
    } else {
        header->setFrameLength(frameLength);
    }
    
    if (header->getIsControlFrame() 
        && header->getFrameLength() > st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
        return header;
    }
    
    if(header->getMasked()) {
        ByteArray maskKey = createByteArray(4);
        mReader->readByteArray(maskKey);
        header->setMaskKey(maskKey);
    }
    
    mHeader = header;
    header->setHeadSize(mReader->getIndex());
    return header;
}

ByteArray _WebSocketHybi13Parser::parseContent(bool isDeflate) {
    ByteArray load = createByteArray(mHeader->getFrameLength());
    byte *payload = load->toValue();
    byte *msg = mData->toValue();
    int pos = mReader->getIndex();
    
    if(!mHeader->getMasked()){
        memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        byte *masking_key_ = mHeader->getMaskKey()->toValue();
        
		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

    //whether we need do decompose
    if(mDeflate != nullptr && isDeflate) {
        byte trailer[4] = {0x00, 0x00, 0xff, 0xff};
        ByteArray t = createByteArray(trailer,4);
        load->append(t);
        ByteArray out = mDeflate->decompress(load);
        return out;
    }

	return load;
}

ByteArray _WebSocketHybi13Parser::parsePingBuff(){
    ByteArray load = createByteArray(mHeader->getFrameLength());
    byte *payload = load->toValue();
    byte *msg = mData->toValue();
    int pos = mReader->getIndex();

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        byte *masking_key_ = mHeader->getMaskKey()->toValue();
        
		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

String _WebSocketHybi13Parser::getOrigin(HttpHeader h) {
    return h->getValue(st(HttpHeader)::Origin);
}

int _WebSocketHybi13Parser::getVersion() {
    return 13;
}

WebSocketPermessageDeflate _WebSocketHybi13Parser::validateExtensions(HttpHeader h) {
    String extensions = h->getValue(st(HttpHeader)::SecWebSocketExtensions);
    if(extensions == nullptr) {
        return nullptr;
    }

    ArrayList<String> list = extensions->trimAll()->split(";");
    if(list == nullptr){
        list = createArrayList<String>();
        list->add(extensions);
    }

    mDeflate = createWebSocketPermessageDeflate();
    if(mDeflate->fit(list)) {
        return mDeflate;
    }

    mDeflate = nullptr;
    return nullptr;
}

ByteArray _WebSocketHybi13Parser::validateContinuationContent(ByteArray in) {
    //whether we need do decompose
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
bool _WebSocketHybi13Parser::validateEntirePacket(ByteArray pack) {
    if(pack->size() < 2) {
        return false;
    }

    ByteArrayReader preReader = createByteArrayReader(pack);
    //check whether it has an entire header
    int b0 = (preReader->readByte() & 0xff);
    int b1 = (preReader->readByte() & 0xff);
    
    bool isMask = ((b1 & st(WebSocketProtocol)::B1_FLAG_MASK) != 0);
    if(isMask) {
        printf("it is mask \n");
    } else {
        printf("it is not mask \n");
    }

    // Get frame length, optionally reading from follow-up bytes if indicated by special values.
    long frameLength = b1 & st(WebSocketProtocol)::B1_MASK_LENGTH;
    int headSize = 0;
    long contentSize = 0;
    
    if(isMask) {
        if(frameLength < st(WebSocketProtocol)::PAYLOAD_SHORT) {
            headSize = 6;
            contentSize = frameLength;
        } else if(frameLength == st(WebSocketProtocol)::PAYLOAD_SHORT) {
            headSize = 8;
            contentSize = (preReader->readShort() & 0xffffL);
        } else if(frameLength == st(WebSocketProtocol)::PAYLOAD_LONG) {
            headSize = 14;
            contentSize = preReader->readLong();
        }
    } else {
        if(frameLength < st(WebSocketProtocol)::PAYLOAD_SHORT) {
            headSize = 2;
            contentSize = frameLength;
        } else if(frameLength == st(WebSocketProtocol)::PAYLOAD_SHORT) {
            headSize = 4;
            contentSize = (preReader->readShort() & 0xffffL);
        } else if(frameLength == st(WebSocketProtocol)::PAYLOAD_LONG) {
            headSize = 10;
            contentSize = preReader->readLong();
        }
    }

    if(headSize >= pack->size()) {
        return false;
    }

    //check whether it has an entire frame
    if((headSize + contentSize) > pack->size()) {
        return false;
    }

    return true;
}

bool _WebSocketHybi13Parser::validateHandShake(HttpHeader h) {
    if(h->getMethod() != HTTP_GET) {        
        return false;
    }

    if(h->getValue(st(HttpHeader)::SecWebSocketKey) == nullptr) {
        return false;
    }

    return true;
}

ArrayList<String> _WebSocketHybi13Parser::extractSubprotocols(HttpHeader h) {
    ArrayList<String> protocols = createArrayList<String>();
    String protocolstr = h->getValue(st(HttpHeader)::SecWebSocketProtocol);
    if(protocolstr == nullptr) {
        return nullptr;
    }

    return protocolstr->trimAll()->split(",");
}

ByteArray _WebSocketHybi13Parser::parsePongBuff() {
    ByteArray load = createByteArray(mHeader->getFrameLength());
    byte *payload = load->toValue();
    byte *msg = mData->toValue();
    int pos = mReader->getIndex();

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        byte *masking_key_ = mHeader->getMaskKey()->toValue();

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

}

