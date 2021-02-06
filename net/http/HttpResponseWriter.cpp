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
        this->send(writer->getIndex());\
        mSendBuff->clear();\
        writer->reset();\
    } else {\
        mSendBuff->growBy(mSendBuff->size() *2);\
        writer->updateSize();\
    }\
}

#define FORCE_FLUSH() \
{\
    if(flush) {\
        if(writer->getIndex() > 0) {\
            this->send(writer->getIndex());\
            mSendBuff->clear();\
            writer->reset();\
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
    HashMap<String,String> encodedUrlMap = response->getEntity()->getEncodedKeyValues();
    ByteArray body = response->getEntity()->getContent();

    //start compose 
    int status = response->getStatus();
    //String statusStr = st(HttpStatus)::toString(status);
    AUTO_FLUSH(writer->writeString(response->getVersion()->toString()));
    AUTO_FLUSH(writer->writeString(" "));
    AUTO_FLUSH(writer->writeString(createString(status)));
    AUTO_FLUSH(writer->writeString(" "));
    AUTO_FLUSH(writer->writeString(st(HttpStatus)::toString(status)));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));

    //update content-length
    int contentlength = 0;
    if(file != nullptr) {
        response->getHeader()->setValue(st(HttpHeader)::TransferEncoding,st(HttpHeader)::TransferChunked);
    } else {
        contentlength = computeContentLength(response);
        response->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(contentlength));
    }

    AUTO_FLUSH(writer->writeString(response->getHeader()->toString(st(HttpProtocol)::HttpResponse)));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd)); //change line
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd)); //blank line

    if(file != nullptr && file->exists()) {
        if(file->exists()) {
            FileInputStream stream = createFileInputStream(file);
            stream->open();
            int filesize = file->length();
            while(filesize != 0) {
                int readlength = mSendBuff->size() - writer->getIndex() - 32 /*reserve data */;
                //printf("readlength is %d,mSendBuff is %d,index is %d \n",readlength,mSendBuff->size(),writer->getIndex());

                if(readlength > filesize) {
                    readlength = filesize;
                }
                filesize -= readlength;
                AUTO_FLUSH(writer->writeString(createString(readlength)->toHexString()));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                stream->readByLength(mSendBuff,writer->getIndex(),readlength);
                writer->skipBy(readlength);
                if(filesize == 0) {
                    AUTO_FLUSH(writer->writeString(st(HttpText)::ChunkEnd));
                } else {
                    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                }
                FORCE_FLUSH();
                //printf("flush trace2,body size is %d,length is %d,reason is %s \n",body->size(),length,strerror(errno));
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
    return writer->getIndex();
}

ByteArray _HttpResponseWriter::compose(HttpResponse response) {
    int length = write(response,false);
    ByteArray data = createByteArray(mSendBuff->toValue(),length);
    return data;
}

long _HttpResponseWriter::computeContentLength(HttpResponse response) {
    HashMap<String,String> encodedUrlMap = response->getEntity()->getEncodedKeyValues();
    int length = 0;
    if(encodedUrlMap != nullptr && encodedUrlMap->size() != 0) {
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
        return response->getEntity()->getContent()->size();
    }

    return 0;
}

int _HttpResponseWriter::send(int size) {
    mClient->send(mSendBuff,size);
}

}
