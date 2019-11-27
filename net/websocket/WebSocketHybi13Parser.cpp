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
    printf("opcode is %d,b0 is %d \n",header->getOpCode(),b0);

    header->setIsFinalFrame((b0 & st(WebSocketProtocol)::B0_FLAG_FIN) != 0);
    header->setIsControlFrame((b0 & st(WebSocketProtocol)::OPCODE_FLAG_CONTROL) != 0);

    // Control frames must be final frames (cannot contain continuations).
    if (header->getIsControlFrame() && !header->isFinalFrame()) {
        //throw new ProtocolException("Control frames must be final.");
        return header;
    }
    printf("parseHeader trace1 \n");
    header->setReservedFlag1((b0 & st(WebSocketProtocol)::B0_FLAG_RSV1) != 0);
    header->setReservedFlag2((b0 & st(WebSocketProtocol)::B0_FLAG_RSV2) != 0);
    header->setReservedFlag3((b0 & st(WebSocketProtocol)::B0_FLAG_RSV3) != 0);
    printf("sv1 is %d",header->getReservedFlag1());
    printf("sv2 is %d",header->getReservedFlag2());
    printf("sv3 is %d",header->getReservedFlag3());
    //TODO
    //if (header->getReservedFlag1() || header->getReservedFlag2() || header->getReservedFlag3()) {
        // Reserved flags are for extensions which we currently do not support.
    //    return header;
    //}

    printf("parseHeader trace2 \n");

    int b1 = mReader->readByte() & 0xff;
    
    header->setMasked((b1 & st(WebSocketProtocol)::B1_FLAG_MASK) != 0);
    
    printf("parseHeader trace3 \n");

    // Get frame length, optionally reading from follow-up bytes if indicated by special values.
    long frameLength = b1 & st(WebSocketProtocol)::B1_MASK_LENGTH;
    printf("framelength aaaa is %ld \n ",frameLength);

    if (frameLength == st(WebSocketProtocol)::PAYLOAD_SHORT) {
        //printf("header frame length is %ld \n",mReader->readShort() & 0xffffL);
        header->setFrameLength(mReader->readShort() & 0xffffL); // Value is unsigned.
    } else if (frameLength == st(WebSocketProtocol)::PAYLOAD_LONG) {
        //printf("header frame long length is %ld \n",mReader->readShort() & 0xffffL);
        frameLength = mReader->readLong();
        if (frameLength < 0) {
            //throw new ProtocolException(
            //  "Frame length 0x" + Long.toHexString(frameLength) + " > 0x7FFFFFFFFFFFFFFF");
            return nullptr;
        }

        header->setFrameLength(frameLength);
    } else {
        header->setFrameLength(frameLength);
    }
    printf("parseHeader trace4 \n");

    printf("frameLength is %ld \n",frameLength);

    //frameBytesRead = 0;

    //if (isControlFrame && frameLength > PAYLOAD_BYTE_MAX) {
    if (header->getIsControlFrame() 
        && header->getFrameLength() > st(WebSocketProtocol)::PAYLOAD_BYTE_MAX) {
        //throw new ProtocolException("Control frame must be less than " + PAYLOAD_BYTE_MAX + "B.");
        return header;
    }
    printf("parseHeader trace5 \n");

    if(header->getMasked()) {
        printf("get mask \n");
        ByteArray maskKey = createByteArray(4);
        mReader->readByteArray(maskKey);
        header->setMaskKey(maskKey);
    }
    printf("parseHeader trace6 \n");

    mHeader = header;
    header->setHeadSize(mReader->getIndex());
    return header;
}

ByteArray _WebSocketHybi13Parser::parseContent(bool isDeflate) {
    ByteArray load = createByteArray(mHeader->getFrameLength());
    byte *payload = load->toValue();
    byte *msg = mData->toValue();
    int pos = mReader->getIndex();
    //printf("pos is %d,msg is %s£¬opcode is %d,framelength is %d \n",pos,&msg[pos],mHeader->getOpCode(),mHeader->getFrameLength());
    //for(int i = 0;i<mData->size();i++) {
    //    printf("0x%x ",msg[i]);
    //}
    printf("\n");
	if(!mHeader->getMasked()){
        printf("binary file,no need unmask!!!! \n");
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        byte *masking_key_ = mHeader->getMaskKey()->toValue();
        printf("framesize is %d,masking_key is %s \n",framesize,masking_key_);
        //printf("masking_key[0] is %x \n",masking_key_[0]);
        //printf("masking_key[1] is %x \n",masking_key_[1]);
        //printf("masking_key[2] is %x \n",masking_key_[2]);
        //printf("masking_key[3] is %x \n",masking_key_[3]);

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}

        printf("payload start: ");
        //for(int i = 0;i<framesize;i++) {
        //    printf("0x%x ",payload[i]);
        //}
	}

    //whether we need do decompose
    if(mDeflate != nullptr && isDeflate) {
        byte trailer[4] = {0x00, 0x00, 0xff, 0xff};
        ByteArray t = createByteArray(trailer,4);
        load->append(t);
        ByteArray out = mDeflate->decompress(load);
        //printf("after decompress is %s \n",out->toString()->toChars());
        return out;
    }

	return load;
}

ByteArray _WebSocketHybi13Parser::parsePingBuff(){
    ByteArray load = createByteArray(mHeader->getFrameLength());
    byte *payload = load->toValue();
    byte *msg = mData->toValue();
    int pos = mReader->getIndex();
    //printf("parsePingBuff pos is %d,msg is %s \n",pos,&msg[pos]);

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        byte *masking_key_ = mHeader->getMaskKey()->toValue();
        printf("framesize is %d,masking_key is %s \n",framesize,masking_key_);

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

String _WebSocketHybi13Parser::getOrigin(HttpHeader h) {
    return h->getValue(Http_Header_Origin);
}

int _WebSocketHybi13Parser::getVersion() {
    return 13;
}

WebSocketPermessageDeflate _WebSocketHybi13Parser::validateExtensions(HttpHeader h) {
    String extensions = h->getValue(Http_Header_Sec_WebSocket_Extensions);
    if(extensions == nullptr) {
        printf("validateExtensions trace1 \n");
        return nullptr;
    }
    printf("extensions is %s \n",extensions->toChars());

    ArrayList<String> list = extensions->trimAll()->split(";");
    if(list == nullptr){
        list = createArrayList<String>();
        list->add(extensions);
    }

    mDeflate = createWebSocketPermessageDeflate();
    if(mDeflate->fit(list)) {
        printf("validateExtensions trace3 \n");
        return mDeflate;
    }

    printf("validateExtensions trace4 \n");

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
        //printf("after decompress is %s \n",out->toString()->toChars());
        return out;
    }

	return in;
}

bool _WebSocketHybi13Parser::validateHandShake(HttpHeader h) {
    if(h->getMethod() != HTTP_GET) {        
        return false;
    }

    if(h->getValue(Http_Header_Sec_WebSocket_Key) == nullptr) {
        return false;
    }

    return true;
}

ArrayList<String> _WebSocketHybi13Parser::extractSubprotocols(HttpHeader h) {
    ArrayList<String> protocols = createArrayList<String>();
    String protocolstr = h->getValue(Http_Header_Sec_WebSocket_Protocol);
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
    //printf("parsePongBuff pos is %d,msg is %s \n",pos,&msg[pos]);

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        byte *masking_key_ = mHeader->getMaskKey()->toValue();
        printf("framesize is %d,masking_key is %s \n",framesize,masking_key_);

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

}

