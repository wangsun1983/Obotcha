#include "HttpV1ResponseWriter.hpp"
#include "AutoLock.hpp"
#include "FileInputStream.hpp"
#include "Enviroment.hpp"
#include "HttpResponse.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpText.hpp"

namespace obotcha {

_HttpV1ResponseWriter::_HttpV1ResponseWriter(HttpV1ClientInfo client) {
    mClient = client;
    mPacket = createHttpPacket();
    mResponsible = true;
}

void _HttpV1ResponseWriter::disableResponse() {
    mResponsible = false;
}

bool _HttpV1ResponseWriter::isResponsible() {
    return mResponsible;
}
    
void _HttpV1ResponseWriter::writeHeader(String key,String value) {
    mPacket->getHeader()->setValue(key,value);
}

void _HttpV1ResponseWriter::writeCookie(HttpCookie c) {
    mPacket->addCookie(c);
}

void _HttpV1ResponseWriter::setStatus(int status) {
    mPacket->getHeader()->setValue(st(HttpHeader)::Status,createString(status));
}

void _HttpV1ResponseWriter::writeBody(ByteArray content) {
    //update content length
    mPacket->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(content->size()));
    mPacket->setBody(content);
}

int _HttpV1ResponseWriter::write(HttpPacket packet) {
    mPacket = packet;
    return 0;
}

int _HttpV1ResponseWriter::write(File file) {
    mFile = file;
    return 0;
}

int _HttpV1ResponseWriter::flush() {
    if(!mResponsible) {
        return -1;
    }
    int totalsend = 0;
    printf("flush trace1 \n");
    AutoLock l(mClient->getResponseWriteMutex());
    if(mFile != nullptr) {
        printf("flush trace1_1 \n");
        Enviroment env = st(Enviroment)::getInstance();
        int buffsize = env->getInt(st(Enviroment)::gHttpServerSendFileBufferSize,64*1024);
        if(mFile->exists()) {
            printf("flush trace2 \n");
            FileInputStream stream = createFileInputStream(mFile);
            stream->open();
            //update HttpHeader
            ByteArray buff = createByteArray(buffsize);
            bool isFirstChunk = true;
            printf("flush trace2 \n");
            while(1) {
                int length = stream->read(buff);
                if(length == 0) {
                    break;
                }
                printf("flush trace3 \n");
                String lengthHexStr = createString(length)->toHexString()->append("\r\n");
                int hexStrLen = lengthHexStr->size();
                if(isFirstChunk) {
                    printf("flush trace4 \n");
                    mPacket->getHeader()->setValue(st(HttpHeader)::TransferEncoding,st(HttpHeader)::TransferChunked);
                    mPacket->getHeader()->setValue(st(HttpHeader)::Status,createString(st(HttpResponse)::Ok));

                    mPacket->getHeader()->setValue(st(HttpHeader)::ContentType,createString("text/plain"));
                    //createByteArray
                    int buffsize = length + hexStrLen;

                    if(length == mFile->length()) {
                        buffsize += 7;
                    }

                    ByteArray body = createByteArray(buffsize);
                    ByteArrayWriter writer = createByteArrayWriter(body);

                    writer->writeByteArray(createByteArray((const byte *)lengthHexStr->toChars(),
                                                 lengthHexStr->size()));
                    if(length != 0) {
                        writer->writeByteArray(buff,length);               
                    }
                    printf("length is %d,file size is %d \n",length,mFile->length());
                    if(length == mFile->length()) {
                        static const byte data[] = {0x0d,0x0a,0x30,0x0d,0x0a,0x0d,0x0a};
                        writer->writeByteArray(createByteArray(data,7),7);
                    }
                    
                    //send
                    mPacket->setBody(body);
                    ByteArray resp = compose(mPacket);
                    mClient->send(resp);
                    isFirstChunk = false;
                    printf("flush trace5 \n");
                } else {
                    String line = "\r\n";
                    int linesize = 0;

                    if(length == buffsize) {
                        linesize = line->size();
                    } else {
                        linesize = line->size()*2 + 5;//line->size()*2;
                    }

                    ByteArray body = createByteArray(linesize + length + hexStrLen);
                    ByteArrayWriter writer = createByteArrayWriter(body);
                    writer->writeString(line);
                    writer->writeByteArray(createByteArray((const byte *)lengthHexStr->toChars(),
                                                 lengthHexStr->size()));
                    if(length == buffsize) {
                        writer->writeByteArray(buff,length);               
                    } else {
                        printf("final data,length is %d  \n",length);
                        writer->writeByteArray(buff,length);
                        writer->writeString(line);
                        static const byte data[] = {0x30,0x0d,0x0a,0x0d,0x0a};
                        int ret = writer->writeByteArray(createByteArray(data,5),5);
                        printf("ret is %d \n",ret);
                    }
                    
                    
                    int size = mClient->send(body);
                    totalsend += size;
                    printf("flush trace2 totalsend is %d,body size is %d,length is %d,reason is %s \n",totalsend,body->size(),length,strerror(errno));

                }
            }
        }
    } else {
        printf("flush trace 333 \n");
        ByteArray resp = compose(mPacket);
        printf("flush resp is %s \n",resp->toString()->toChars());
        mClient->send(resp);
    }

    return  0;
}

ByteArray _HttpV1ResponseWriter::compose(HttpPacket packet) {
    String statusString = packet->getHeader()->getValue(st(HttpHeader)::Status);
	if(statusString == nullptr) {
		return nullptr;
	}

	String status = st(HttpResponse)::castStatus(statusString->toBasicInt());
	String responseStr = createString("HTTP/1.1 ")->append(statusString," ",status,"\r\n");
    
	String headerStr = packet->getHeader()->toString();
    
    int responseStrSize = responseStr->size();
    int headerStrSize = headerStr->size();
    int bodySize = 0;
    if(mPacket->getBody() != nullptr) {
        bodySize = mPacket->getBody()->size();
    }

    ByteArray response = createByteArray(responseStr->size() + headerStr->size() + bodySize);
    ByteArrayWriter writer = createByteArrayWriter(response);
	//String bodyStr = createString((char *)mBody->toValue(),0,mBody->size());
    writer->writeString(responseStr);
	writer->write((byte *)headerStr->toChars(),headerStr->size());
    writer->writeString(st(HttpText)::LineEnd);

    if(packet->getBody() != nullptr) {
        writer->writeByteArray(packet->getBody());
    }
 
    return response;
}

}
