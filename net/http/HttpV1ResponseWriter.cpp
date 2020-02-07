#include "HttpV1ResponseWriter.hpp"
#include "AutoMutex.hpp"
#include "FileInputStream.hpp"
#include "Enviroment.hpp"
#include "HttpResponse.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_HttpV1ResponseWriter::_HttpV1ResponseWriter(HttpV1ClientInfo client) {
    mClient = client;
    mPacket = createHttpPacket();
}
    
void _HttpV1ResponseWriter::writeHeader(String key,String value) {
    mPacket->getHeader()->setValue(key,value);
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
}

int _HttpV1ResponseWriter::write(File file) {
    mFile = file;
}

int _HttpV1ResponseWriter::flush() {
    AutoMutex l(mClient->getResponseWriteMutex());

    if(mFile != nullptr) {
        Enviroment env = st(Enviroment)::getInstance();
        int buffsize = env->getInt(st(Enviroment)::gHttpServerSendFileBufferSize);
        if(mFile->exists()) {
            printf("file size is %d \n",buffsize);

            FileInputStream stream = createFileInputStream(mFile);
            stream->open();
            //update HttpHeader
            ByteArray buff = createByteArray(buffsize);
            bool isFirstChunk = true;

            while(1) {
                int length = stream->read(buff);
                printf("length is %d \n",length);
                //printf("buff is %s \n",buff->toString()->toChars());
                String lengthHexStr = createString(length)->toHexString()->append("\r\n");
                printf("lengthHex str is %s \n",lengthHexStr->toChars());
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
                    //printf("1.body is %s \n",body->toString()->toChars());
                    if(length != 0) {
                        writer->writeByteArray(buff,length);               
                    }
                    //printf("2.boyd is %s \n",body->toString()->toChars());
                    //send
                    mPacket->setBody(body);
                    ByteArray resp = mPacket->genHttpResponse();
                    printf("send message is %s \n",resp->toString()->toChars());
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
                    //printf("1.body is %s \n",body->toString()->toChars());
                    if(length != 0) {
                        writer->writeByteArray(buff,length);               
                    } else {
                        writer->writeString(line);
                    }

                    for(int i = 0;i<body->size();i++) {
                        printf("body value is %x \n",body->at(i));
                    }
                    mClient->send(body);
                }
                
                if(length == 0) {
                    break;
                }
            }
        }
    } else {
        ByteArray resp = mPacket->genHttpResponse();
        mClient->send(resp);
    }

    return  0;
}

}
