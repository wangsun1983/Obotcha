#include "HttpResponseWriter.hpp"
#include "AutoLock.hpp"
#include "FileInputStream.hpp"
#include "Enviroment.hpp"
#include "HttpResponse.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpText.hpp"
#include "HttpProtocol.hpp"
#include "HttpStatus.hpp"
#include "Log.hpp"

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

_HttpResponseWriter::_HttpResponseWriter(OutputStream stream) {
    mOutputStream = stream;
    mResponsible = true;
    mSendBuff = createByteArray(128);
}

_HttpResponseWriter::_HttpResponseWriter() {
    mResponsible = true;
    mSendBuff = createByteArray(128);
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
    //AutoLock l(mClient->getResponseWriteMutex());
    mSendBuff->clear();
    ByteArrayWriter writer = createByteArrayWriter(mSendBuff);

    File file = response->getFile();
    ArrayList<KeyValuePair<String,String>> encodedValues = response->getEntity()->getEncodedKeyValues();
    ByteArray body = response->getEntity()->getContent();

    //start compose
    auto header = response->getHeader();

    int status = header->getResponseStatus();
    //String statusStr = st(HttpStatus)::toString(status);
    AUTO_FLUSH(writer->writeString(header->getVersion()->toString()));

    AUTO_FLUSH(writer->writeString(" "));
    AUTO_FLUSH(writer->writeString(createString(status)));
    AUTO_FLUSH(writer->writeString(" "));

    String reason = header->getResponseReason();
    if(reason != nullptr) {
        AUTO_FLUSH(writer->writeString(reason));
    } else {
        AUTO_FLUSH(writer->writeString(st(HttpStatus)::toString(status)));
    }

    AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF));

    //update content-length
    int contentlength = 0;
    if(file != nullptr) {
        response->getHeader()->setValue(st(HttpHeader)::TransferEncoding,st(HttpHeader)::TransferChunked);
    } else {
        contentlength = computeContentLength(response);
        response->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(contentlength));
    }

    AUTO_FLUSH(writer->writeString(response->getHeader()->toString(st(HttpProtocol)::HttpResponse)));
    AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF)); //change line
    AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF)); //blank line

    if(file != nullptr && file->exists()) {
        if(file->exists()) {
            FileInputStream stream = createFileInputStream(file);
            stream->open();
            long filesize = file->length();
            if(response->getType() == st(HttpResponse)::CHUNCKED) {
                while(filesize != 0) {
                    int readlength = mSendBuff->size() - writer->getIndex() - 32 /*reserve data */;
                    if(readlength > filesize) {
                        readlength = filesize;
                    }
                    filesize -= readlength;
                    AUTO_FLUSH(writer->writeString(createInteger(readlength)->toHexString()));
                    AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF));
                    //stream->readByLength(mSendBuff,writer->getIndex(),readlength);
                    stream->readTo(mSendBuff,writer->getIndex(),readlength);
                    writer->skipBy(readlength);
                    if(filesize == 0) {
                        AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF));
                        AUTO_FLUSH(writer->writeString(createString("0")));
                        AUTO_FLUSH(writer->writeString(st(HttpText)::HttpEnd));
                    } else {
                        AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF));
                    }
                    FORCE_FLUSH();
                }
            } else {
                LOG(ERROR)<<"send file only support chunck";
            }
        }
    } else if(encodedValues != nullptr && encodedValues->size() != 0){
        auto iterator = encodedValues->getIterator();
        bool isFirstKey = true;
        while(iterator->hasValue()) {
            auto pair = iterator->getValue();
            String key = pair->getKey();
            String value = pair->getValue();
            if(!isFirstKey) {
                AUTO_FLUSH(writer->writeByte('&'));
            }
            AUTO_FLUSH(writer->writeString(key));
            AUTO_FLUSH(writer->writeByte('='));
            AUTO_FLUSH(writer->writeString(value));
            iterator->next();
            isFirstKey = false;
        }
        AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF));
    } else if(body != nullptr && body->size() != 0) {
        AUTO_FLUSH(writer->writeByteArray(body));
        AUTO_FLUSH(writer->writeString(st(HttpText)::CRLF));
    }
   
    FORCE_FLUSH();

    return writer->getIndex();
}

ByteArray _HttpResponseWriter::compose(HttpResponse response) {
    int length = write(response,false);
    ByteArray data = createByteArray(mSendBuff->toValue(),length);
    return data;
}

long _HttpResponseWriter::computeContentLength(HttpResponse response) {

    //if(response->getType() == st(HttpResponse)::CHUNCKED) {
    //    return response->getFile()->length();
    //}

    ArrayList<KeyValuePair<String,String>> encodedUrlMap = response->getEntity()->getEncodedKeyValues();
    int length = 0;
    if(encodedUrlMap != nullptr && encodedUrlMap->size() != 0) {
        ListIterator<KeyValuePair<String,String>> iterator = encodedUrlMap->getIterator();
        while(iterator->hasValue()) {
            auto pair = iterator->getValue();
            String key = pair->getKey();
            String value = pair->getValue();
            length += key->size() + value->size();
            iterator->next();
        }
        length += encodedUrlMap->size()*2 - 1; /*=&*/
        return length;
    } else {
        if(response->getEntity()->getContent() != nullptr) {
            return response->getEntity()->getContent()->size();
        }
    } 

    return 0;
}

int _HttpResponseWriter::send(int size) {
    return mOutputStream->write(mSendBuff,size);
}

}
