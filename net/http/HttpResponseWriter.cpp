#include "HttpResponseWriter.hpp"
#include "AutoLock.hpp"
#include "FileInputStream.hpp"
#include "Enviroment.hpp"
#include "HttpResponse.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpText.hpp"
#include "HttpProtocol.hpp"
#include "HttpStatus.hpp"

namespace obotcha {

#define AUTO_FLUSH(X) \
while(X == -1) {\
    if(flush) {\
        send(writer->getIndex());\
        mSendBuff->clear();\
        writer = createByteArrayWriter(mSendBuff);\
    } else {\
        mSendBuff->growBy(mSendBuff->size() *2);\
        writer->updateSize();\
    }\
}

#define FORCE_FLUSH() \
{\
    if(flush) {\
        if(writer->getIndex() > 0) {\
            send(writer->getIndex());\
            mSendBuff->clear();\
            writer = createByteArrayWriter(mSendBuff);\
        }\
    }\
}

_HttpResponseWriter::_HttpResponseWriter(HttpClientInfo client) {
    mClient = client;
    mResponsible = true;
    mSendBuff = createByteArray(1024*32);
}

_HttpResponseWriter::_HttpResponseWriter() {
    mResponsible = true;
    mSendBuff = createByteArray(1024*32);
}

void _HttpResponseWriter::disableResponse() {
    mResponsible = false;
}

bool _HttpResponseWriter::isResponsible() {
    return mResponsible;
}

int _HttpResponseWriter::write(HttpResponse response,bool flush) {
    if(!mResponsible) {
        return -1;
    }
    AutoLock l(mClient->getResponseWriteMutex());
    mSendBuff->clear();
    ByteArrayWriter writer = createByteArrayWriter(mSendBuff);

    File file = response->getFile();
    HashMap<String,String> encodedUrlMap = response->mPacket->getEncodedKeyValues();
    ByteArray body = response->mPacket->getBody();

    //start compose 
    int status = response->getStatus();
    printf("status is %d \n",status);
    String statusStr = st(HttpStatus)::toString(status);
    AUTO_FLUSH(writer->writeString(response->mPacket->getVersion()->toString()));
    AUTO_FLUSH(writer->writeString(" "));
    AUTO_FLUSH(writer->writeString(createString(status)));
    AUTO_FLUSH(writer->writeString(" "));
    AUTO_FLUSH(writer->writeString(st(HttpStatus)::toString(status)));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));

    //update content-length
    int contentlength = 0;
    if(file != nullptr) {
        response->mPacket->getHeader()->setValue(st(HttpHeader)::TransferEncoding,st(HttpHeader)::TransferChunked);
    } else {
        contentlength = computeContentLength(response);
        response->mPacket->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(contentlength));
    }

    AUTO_FLUSH(writer->writeString(response->mPacket->getHeader()->toString(st(HttpProtocol)::HttpResponse)));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd)); //change line
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd)); //blank line

    if(file != nullptr && file->exists()) {
        FORCE_FLUSH();

        printf("flush trace1_1 \n");
        Enviroment env = st(Enviroment)::getInstance();
        int buffsize = env->getInt(st(Enviroment)::gHttpServerSendFileBufferSize,64*1024);
        if(file->exists()) {
            printf("flush trace2 \n");
            FileInputStream stream = createFileInputStream(file);
            stream->open();
            //update HttpHeader
            ByteArray buff = createByteArray(buffsize);
            bool isFirstChunk = true;
            printf("flush trace2 \n");
            int totalsend = 0;
            while(1) {
                int length = stream->read(buff);
                if(length == 0) {
                    break;
                }
                printf("flush trace3 \n");
                String lengthHexStr = createString(length)->toHexString()->append("\r\n");
                int hexStrLen = lengthHexStr->size();
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
    } else if(encodedUrlMap != nullptr && encodedUrlMap->size() != 0){
        MapIterator<String,String> iterator = encodedUrlMap->getIterator();
        bool isFirstKey = true;
        while(iterator->hasValue()) {
            String key = iterator->getKey();
            String value = iterator->getValue();
            if(!isFirstKey) {
                AUTO_FLUSH(writer->writeByte('&'));
            }
            AUTO_FLUSH(writer->writeString(key));
            AUTO_FLUSH(writer->writeByte('='));
            AUTO_FLUSH(writer->writeString(value));
            iterator->next();
        }
        AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    } else if(body != nullptr && body->size() != 0) {
        AUTO_FLUSH(writer->writeByteArray(body));
        AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
        FORCE_FLUSH();
    }
    
}

ByteArray _HttpResponseWriter::compose(HttpResponse response) {
    int length = write(response,false);
    ByteArray data = createByteArray(mSendBuff->toValue(),length);
    return data;
}

long _HttpResponseWriter::computeContentLength(HttpResponse response) {
    HashMap<String,String> encodedUrlMap = response->mPacket->getEncodedKeyValues();
    int length = 0;
    if(encodedUrlMap != nullptr) {
        MapIterator<String,String> iterator = encodedUrlMap->getIterator();
        while(iterator->hasValue()) {
            String key = iterator->getKey();
            String value = iterator->getValue();
            length += key->size() + value->size();
            iterator->next();
        }
        length += encodedUrlMap->size()*2 - 1; /*=&*/
        return length;
    } else {
        return response->mPacket->getBody()->size();
    }

    return 0;
}

int _HttpResponseWriter::send(int size) {
    mClient->send(mSendBuff,size);
}

/*
int _HttpResponseWriter::flush() {
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

ByteArray _HttpResponseWriter::compose(HttpPacket packet) {
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
*/
}
