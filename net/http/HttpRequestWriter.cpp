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

namespace obotcha {

#define AUTO_FLUSH(X) \
while(X == -1) {\
    flush(writer->getIndex() + 1);\
    mSendBuff->clear();\
    writer = createByteArrayWriter(mSendBuff);\
}

#define FORCE_FLUSH() \
{\
    flush(writer->getIndex() + 1);\
    mSendBuff->clear();\
    writer = createByteArrayWriter(mSendBuff);\
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
    //TODO
    return nullptr;
}

int _HttpRequestWriter::write(HttpRequest p) {
    mSendBuff->clear();
    ByteArrayWriter writer = createByteArrayWriter(mSendBuff);
    
    //1.create head
    String contentType = p->getHeader(st(HttpHeader)::ContentType);
    String boundary = st(HttpText)::BoundarySeperator->append(generateMultiPartBoundary());
    contentType = contentType->append(st(HttpContentType)::MultiPartFormData,";","boundary=",boundary);
    p->setHeader(st(HttpHeader)::ContentType,contentType);

    AUTO_FLUSH(writer->writeString(st(HttpMethod)::toString(p->getMethod())));
    AUTO_FLUSH(writer->writeString(st(HttpText)::ContentSpace));
    AUTO_FLUSH(writer->writeString(p->getUrl()->toString()));
    AUTO_FLUSH(writer->writeString(st(HttpText)::ContentSpace));
    AUTO_FLUSH(writer->writeString(p->mPacket->getVersion()->toString()));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    AUTO_FLUSH(writer->writeString(p->mPacket->getHeader()->toString()));
    AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
    
    //2. multipart
    HttpMultiPart multiPart = p->mPacket->getMultiPart();

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
                if(partFile->getName() != nullptr){
                    AUTO_FLUSH(writer->writeString(partFile->getName()));
                }
                
                AUTO_FLUSH(writer->writeByte('"'));
                AUTO_FLUSH(writer->writeString("; "));
                AUTO_FLUSH(writer->writeString(st(HttpText)::PartFileName));
                AUTO_FLUSH(writer->writeString(createString("=")));
                AUTO_FLUSH(writer->writeByte('"'));
                if(partFile->getFile() != nullptr){
                    AUTO_FLUSH(writer->writeString(partFile->getFile()->getName()));
                }
                AUTO_FLUSH(writer->writeByte('"'));
                FORCE_FLUSH();
                
                FileInputStream stream = createFileInputStream(partFile->getFile());
                ByteArray readBuff = createByteArray(1024*16);
                while(stream->read(readBuff) >= 0) {
                    flush(readBuff);
                }

                AUTO_FLUSH(writer->writeString(st(HttpText)::LineEnd));
                iterator->next();
            }
        }

        AUTO_FLUSH(writer->writeString(st(HttpText)::BoundaryBeginning));
        AUTO_FLUSH(writer->writeString(boundary));
    }

    if(writer->getIndex() != 0) {
        FORCE_FLUSH();
    }
    //body
    return 0;
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

}
