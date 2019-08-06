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
    if (header->getIsControlFrame() && !header->getIsFinalFrame()) {
        //throw new ProtocolException("Control frames must be final.");
        return header;
    }
    printf("parseHeader trace1 \n");
    header->setReservedFlag1((b0 & st(WebSocketProtocol)::B0_FLAG_RSV1) != 0);
    header->setReservedFlag2((b0 & st(WebSocketProtocol)::B0_FLAG_RSV2) != 0);
    header->setReservedFlag3((b0 & st(WebSocketProtocol)::B0_FLAG_RSV3) != 0);

    if (header->getReservedFlag1() || header->getReservedFlag2() || header->getReservedFlag3()) {
        // Reserved flags are for extensions which we currently do not support.
        return header;
    }
    printf("parseHeader trace2 \n");

    int b1 = mReader->readByte() & 0xff;
    
    header->setMasked((b1 & st(WebSocketProtocol)::B1_FLAG_MASK) != 0);
    
    //if (header->getMasked() == isClient) {
        //Masked payloads must be read on the server. Unmasked payloads must be read on the client.
        //throw new ProtocolException("Client-sent frames must be masked. Server sent must not.");
    //    return header;
    //}

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

ByteArray _WebSocketHybi13Parser::parseContent() {
    ByteArray load = createByteArray(mHeader->getFrameLength());
    char *payload = load->toValue();
    char *msg = mData->toValue();
    int pos = mReader->getIndex();
    printf("pos is %d,msg is %s \n",pos,&msg[pos]);

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        char *masking_key_ = mHeader->getMaskKey()->toValue();
        printf("framesize is %d,masking_key is %s \n",framesize,masking_key_);

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

ByteArray _WebSocketHybi13Parser::parsePingBuff(){
    ByteArray load = createByteArray(mHeader->getFrameLength());
    char *payload = load->toValue();
    char *msg = mData->toValue();
    int pos = mReader->getIndex();
    printf("parsePingBuff pos is %d,msg is %s \n",pos,&msg[pos]);

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        char *masking_key_ = mHeader->getMaskKey()->toValue();
        printf("framesize is %d,masking_key is %s \n",framesize,masking_key_);

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

ByteArray _WebSocketHybi13Parser::parsePongBuff() {
    ByteArray load = createByteArray(mHeader->getFrameLength());
    char *payload = load->toValue();
    char *msg = mData->toValue();
    int pos = mReader->getIndex();
    printf("parsePongBuff pos is %d,msg is %s \n",pos,&msg[pos]);

	if(!mHeader->getMasked()){
		memcpy(payload, 
        (const char *)&msg[pos], 
        mHeader->getFrameLength());
	} else {
        int framesize = mHeader->getFrameLength();
        char *masking_key_ = mHeader->getMaskKey()->toValue();
        printf("framesize is %d,masking_key is %s \n",framesize,masking_key_);

		for(uint i = 0; i < framesize; i++){
			int j = i % 4;
			payload[i] = msg[pos + i] ^ masking_key_[j];
		}
	}

	return load;
}

}

