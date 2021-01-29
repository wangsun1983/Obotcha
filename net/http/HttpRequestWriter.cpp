#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "HttpRequestWriter.hpp"
#include "HttpContentType.hpp"
#include "HttpHeader.hpp"
#include "Log.hpp"
#include "UUID.hpp"
#include "HttpText.hpp"
#include "FileInputStream.hpp"
#include "HttpProtocol.hpp"

namespace obotcha {

#define AUTO_FLUSH(X) \
while(X == -1) {\
    if(mTcpClient != nullptr) {\
        flush(writer->getIndex());\
        mSendBuff->clear();\
        writer->reset();\
    } else {\
        mSendBuff->growBy(mSendBuff->size() *2);\
        writer->updateSize();\
    }\
}

#define FORCE_FLUSH() \
{\
    if(mTcpClient != nullptr) {\
        flush(writer->getIndex());\
        mSendBuff->clear();\
        writer->reset();\
    }\
}

_HttpRequestWriter::_HttpRequestWriter(TcpClient c) {
    mTcpClient = c;
    mSendBuff = createByteArray(1024*4);
}

_HttpRequestWriter::_HttpRequestWriter() {
    mTcpClient = nullptr;
    mSendBuff = createByteArray(1024*4);
}

ByteArray _HttpRequestWriter::compose(HttpRequest p) {
    int length = write(p);
    ByteArray data = createByteArray(mSendBuff->toValue(),length);
    return data;
}

int _HttpRequestWriter::write(HttpRequest p) {
    mSendBuff->clear();
    ByteArrayWriter writer = createByteArrayWriter(mSendBuff);
    String boundary = nullptr;
    //check body
    HttpMultiPart multiPart = p->getEntity()->getMultiPart();
    HashMap<String,String> encodedUrlMap = p->getEntity()->getEncodedKeyValues();

    //1.create head
    HttpContentType contentType = p->getHeader()->getContentType();
    if(contentType == nullptr) {
        if(multiPart != nullptr) {
            boundary = st(HttpText)::BoundarySeperator->append(generateMultiPartBoundary());
            //contentType = st(HttpContentType)::MultiPartFormData->append(";","boundary=",boundary);
            contentType = createHttpContentType();
            contentType->setBoundary(boundary);
            contentType->setType(st(HttpContentType)::MultiPartFormData);
            p->getHeader()->setContentType(contentType);
            //p->setHeader(st(HttpHeader)::ContentType,contentType);
            long length = computeContentLength(p,boundary);
            p->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(length));
        } else if(encodedUrlMap != nullptr) {
            long length = computeContentLength(p);
            p->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(length));
            //p->setHeader(st(HttpHeader)::ContentType,st(HttpContentType)::XFormUrlEncoded);
            contentType = createHttpContentType();
            contentType->setType(st(HttpContentType)::XFormUrlEncoded);
            p->getHeader()->setContentType(contentType);
        } else {
            ByteArray body = p->getEntity()->getContent();
            if(body != nullptr && body->size() != 0) {
                p->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(body->size()));
            }
            contentType = createHttpContentType();
            contentType->setType(st(HttpContentType)::XFormUrlEncoded);
            p->getHeader()->setContentType(contentType);
            //p->setHeader(st(HttpHeader)::ContentType,st(HttpContentType)::XFormUrlEncoded);
        }
    }
    AUTO_FLUSH(writer->writeString(st(HttpMethod)::toString(p->getMethod())));
    AUTO_FLUSH(writer->writeString(st(HttpText)::ContentSpace));
    AUTO_FLUSH(writer->writeString(p->getUrl()->getPath()));
    AUTO_FLUSH(writer->writeString(st(HttpText)::ContentSpace));
    AUTO_FLUSH(writer->writeString(p->getVersion()->toString()));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    AUTO_FLUSH(writer->writeString(p->getHeader()->toString(st(HttpProtocol)::HttpRequest)));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    //2. multipart
    
    //ContentType multipart/form-data
    if(multiPart != nullptr) {
        if(multiPart->contents->size() > 0) {
            ListIterator<HttpMultiPartContent> iterator = multiPart->contents->getIterator();
            while(iterator->hasValue()) {
                HttpMultiPartContent content = iterator->getValue();
                AUTO_FLUSH(writer->writeString(st(HttpText)::BoundaryBeginning));
                AUTO_FLUSH(writer->writeString(boundary));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                AUTO_FLUSH(writer->writeString(st(HttpHeader)::ContentDisposition));
                AUTO_FLUSH(writer->writeString(createString(": ")));
                AUTO_FLUSH(writer->writeString(st(HttpContentType)::FormData));
                AUTO_FLUSH(writer->writeString(createString("; ")));
                AUTO_FLUSH(writer->writeString(st(HttpText)::PartName));
                AUTO_FLUSH(writer->writeString(createString("=")));
                AUTO_FLUSH(writer->writeByte('"'));
                AUTO_FLUSH(writer->writeString(content->getName()));
                AUTO_FLUSH(writer->writeByte('"'));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                AUTO_FLUSH(writer->writeString(content->getValue()));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                iterator->next();
            }
        }

        if(multiPart->files->size() > 0) {
            ListIterator<HttpMultiPartFile> iterator = multiPart->files->getIterator();
            FORCE_FLUSH();

            while(iterator->hasValue()) {
                HttpMultiPartFile partFile = iterator->getValue();
                AUTO_FLUSH(writer->writeString(st(HttpText)::BoundaryBeginning));
                AUTO_FLUSH(writer->writeString(boundary));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                AUTO_FLUSH(writer->writeString(st(HttpHeader)::ContentDisposition));
                AUTO_FLUSH(writer->writeString(createString(": ")));
                AUTO_FLUSH(writer->writeString(st(HttpContentType)::FormData));
                AUTO_FLUSH(writer->writeString(createString("; ")));
                AUTO_FLUSH(writer->writeString(st(HttpText)::PartName));
                AUTO_FLUSH(writer->writeString(createString("=")));
                AUTO_FLUSH(writer->writeByte('"'));
                if(partFile->getHttpFile() != nullptr){
                    AUTO_FLUSH(writer->writeString(partFile->getHttpFile()->getName()));
                }
                
                AUTO_FLUSH(writer->writeByte('"'));
                AUTO_FLUSH(writer->writeString("; "));
                AUTO_FLUSH(writer->writeString(st(HttpText)::PartFileName));
                AUTO_FLUSH(writer->writeString(createString("=")));
                AUTO_FLUSH(writer->writeByte('"'));
                if(partFile->getHttpFile() != nullptr){
                    AUTO_FLUSH(writer->writeString(partFile->getHttpFile()->getName()));
                }
                AUTO_FLUSH(writer->writeByte('"'));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                FORCE_FLUSH();
                
                FileInputStream stream = createFileInputStream(partFile->getHttpFile()->getFile());
                stream->open();
                ByteArray readBuff = createByteArray(1024*16);
                int index = 0;
                while(1) {
                    int count = stream->read(index,readBuff);
                    if(count == 0) {
                        break;
                    }
                    index += count;
                    flush(readBuff,count);
                }

                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                iterator->next();
            }
        }

        AUTO_FLUSH(writer->writeString(st(HttpText)::BoundaryBeginning));
        AUTO_FLUSH(writer->writeString(boundary));
        AUTO_FLUSH(writer->writeString(st(HttpText)::BoundaryBeginning));
        AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    } else if(encodedUrlMap != nullptr){
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
    } else {
        ByteArray body = p->getEntity()->getContent();
        if(body != nullptr && body->size() > 0) {
            AUTO_FLUSH(writer->writeByteArray(body));
        }
    }

    if(writer->getIndex() != 0) {
        FORCE_FLUSH();
    }

    //body
    return writer->getIndex();
}

String _HttpRequestWriter::generateMultiPartBoundary() {
    UUID uuid = createUUID();
    String boundary = uuid->generate();
    return boundary->replaceAll("-","");
}

int _HttpRequestWriter::flush(int size) {
    mTcpClient->doSend(mSendBuff,size);
}

int _HttpRequestWriter::flush(ByteArray data) {
    mTcpClient->doSend(data);
}

int _HttpRequestWriter::flush(ByteArray data,int length) {
    mTcpClient->doSend(data,length);
}

long _HttpRequestWriter::computeContentLength(HttpRequest req,String boundary) {
    HttpMultiPart multiPart = req->getEntity()->getMultiPart();
    HashMap<String,String> encodedUrlMap = req->getEntity()->getEncodedKeyValues();
    long length = 0;
    
    //multipart
    if(multiPart != nullptr) {
        length += st(HttpText)::LineEnd->size();

        ListIterator<HttpMultiPartContent> contentIterator = multiPart->contents->getIterator();
        while(contentIterator->hasValue()) {
            HttpMultiPartContent content = contentIterator->getValue();
            length += (boundary->size() + st(HttpText)::BoundaryBeginning->size() + st(HttpText)::LineEnd->size());
            int nameSize = 0;
            if(content->getName() != nullptr) {
                nameSize = content->getName()->size();
            }

            length += (st(HttpHeader)::ContentDisposition->size()
                    + 2 /*": "*/
                    + st(HttpContentType)::FormData->size()
                    + 2 /*"; "*/ 
                    + st(HttpText)::PartName->size() 
                    + 3 /*=""*/
                    + nameSize
                    + st(HttpText)::LineEnd->size());
            length += st(HttpText)::LineEnd->size();
            if(content->getValue() != nullptr) {
                length += content->getValue()->size();
            }
            length += st(HttpText)::LineEnd->size();
            contentIterator->next();
        }
        ListIterator<HttpMultiPartFile> fileIterator = multiPart->files->getIterator();
        while(fileIterator->hasValue()) {
            HttpMultiPartFile content = fileIterator->getValue();
            length += (boundary->size() + st(HttpText)::BoundaryBeginning->size() + st(HttpText)::LineEnd->size());
            int nameSize = 0;
            if(content->getHttpFile()->getName() != nullptr) {
                nameSize = content->getHttpFile()->getName()->size();
            }

            long filenamesize = 0;
            long filesize = 0;
            if(content->getHttpFile() != nullptr && content->getHttpFile()->getName()!= nullptr) {
                filenamesize = content->getHttpFile()->getName()->size();
                filesize = content->getHttpFile()->getFile()->length();
            }

            length += st(HttpHeader)::ContentDisposition->size()
                    + 2 /*": "*/
                    + st(HttpContentType)::FormData->size()
                    + 2 /*"; "*/ 
                    + st(HttpText)::PartName->size() 
                    + 5 /*=""; */
                    + nameSize
                    + st(HttpText)::PartFileName->size()
                    + 3 /*=""*/
                    + filenamesize
                    + st(HttpText)::LineEnd->size();
            length += st(HttpText)::LineEnd->size();
            length += filesize;
            length += st(HttpText)::LineEnd->size();
            fileIterator->next();
        }

        length += (boundary->size() + st(HttpText)::BoundaryBeginning->size()*2);
        return length;
    } else if(encodedUrlMap != nullptr) {
        MapIterator<String,String> iterator = encodedUrlMap->getIterator();
        while(iterator->hasValue()) {
            String key = iterator->getKey();
            String value = iterator->getValue();
            length += key->size() + value->size();
            iterator->next();
        }
        length += encodedUrlMap->size()*2 - 1; /*=&*/
        return length;
    }

    return 0;
}

}
