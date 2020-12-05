#include "HttpV1ResponseWriter.hpp"
#include "AutoLock.hpp"
#include "FileInputStream.hpp"
#include "Enviroment.hpp"
#include "HttpResponse.hpp"
#include "ByteArrayWriter.hpp"

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
    printf("HttpV1ResponseWriter flush start \n");
    if(!mResponsible) {
        return -1;
    }
    
    AutoLock l(mClient->getResponseWriteMutex());
    printf("HttpV1ResponseWriter flush trace1 \n");
    if(mFile != nullptr) {
        printf("HttpV1ResponseWriter flush trace2 \n");
        Enviroment env = st(Enviroment)::getInstance();
        int buffsize = env->getInt(st(Enviroment)::gHttpServerSendFileBufferSize,64*1024);
        if(mFile->exists()) {
            FileInputStream stream = createFileInputStream(mFile);
            stream->open();
            //update HttpHeader
            ByteArray buff = createByteArray(buffsize);
            bool isFirstChunk = true;

            while(1) {
                int length = stream->read(buff);
                String lengthHexStr = createString(length)->toHexString()->append("\r\n");
                int hexStrLen = lengthHexStr->size();
                if(isFirstChunk) {
                    mPacket->getHeader()->setValue(st(HttpHeader)::TransferEncoding,st(HttpHeader)::TransferChunked);
                    mPacket->getHeader()->setValue(st(HttpHeader)::Status,createString(st(HttpResponse)::Ok));

                    mPacket->getHeader()->setValue(st(HttpHeader)::ContentType,createString("text/plain"));
                    //createByteArray
                    ByteArray body = createByteArray(length + hexStrLen);
                    ByteArrayWriter writer = createByteArrayWriter(body);

                    writer->writeByteArray(createByteArray((const byte *)lengthHexStr->toChars(),
                                                 lengthHexStr->size()));
                    if(length != 0) {
                        writer->writeByteArray(buff,length);               
                    }
                    //send
                    mPacket->setBody(body);
                    ByteArray resp = mPacket->genHttpResponse();
                    mClient->send(resp);
                    isFirstChunk = false;
                } else {
                    String line = "\r\n";
                    int linesize = 0;

                    if(length == 0) {
                        linesize = line->size()*2;
                    } else {
                        linesize = line->size();
                    }

                    ByteArray body = createByteArray(linesize + length + hexStrLen);
                    ByteArrayWriter writer = createByteArrayWriter(body);
                    writer->writeString(line);
                    writer->writeByteArray(createByteArray((const byte *)lengthHexStr->toChars(),
                                                 lengthHexStr->size()));
                    if(length != 0) {
                        writer->writeByteArray(buff,length);               
                    } else {
                        writer->writeString(line);
                    }

                    mClient->send(body);
                }
                
                if(length == 0) {
                    break;
                }
            }
        }
    } else {
        printf("HttpV1ResponseWriter flush trace2 \n");
        ByteArray resp = mPacket->genHttpResponse();
        printf("response is %s \n",resp->toString()->toChars());
        int ret = mClient->send(resp);
        printf("send result is %d \n",ret);
    }

    return  0;
}

}
