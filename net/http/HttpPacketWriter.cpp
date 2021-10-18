#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpPacketWriter.hpp"
#include "HttpText.hpp"
#include "HttpProtocol.hpp"
#include "HttpMime.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

_HttpPacketWriter::_HttpPacketWriter(OutputStream stream,int defaultSize) {
    mStream = stream;
    mDefaultSize = defaultSize;
    mBuff = createByteArray(defaultSize);
    mWriter = createByteArrayWriter(mBuff);
}

int _HttpPacketWriter::write(HttpPacket packet) {
    return _flush(packet,true);
}

ByteArray _HttpPacketWriter::data(HttpPacket packet) {
    _flush(packet,false);
    return createByteArray(mBuff);
}

/*
* \r\n
* contentxxxxxxxxx
*/
int _HttpPacketWriter::_computeContentLength(HttpPacket packet) {
    if(packet->getHeader()->getType() == st(HttpHeader)::Request) {
        auto multiPart = packet->getEntity()->getMultiPart();
        if(multiPart != nullptr) {
            return multiPart->getContentLength() + st(HttpText)::CRLF->size();
        }
    }

    if(packet->getEntity()->getContent() != nullptr) {
        return packet->getEntity()->getContent()->size();
    }

    return 0;
}

void _HttpPacketWriter::_updateHttpHeader(HttpPacket packet) {
    HttpHeader header = packet->getHeader();

    switch(packet->getProtocol()) {
        case st(HttpProtocol)::HttpRequest: {
            auto multiPart = packet->getEntity()->getMultiPart();
            if(multiPart != nullptr) {
                HttpContentType contentType = createHttpContentType();
                contentType->setBoundary(multiPart->getBoundary());
                contentType->setType(st(HttpMime)::MultiPartFormData);
                header->setContentType(contentType);
            }
            break;
        }

        case st(HttpProtocol)::HttpResponse: {
            if(packet->getEntity()->getChunkFile() != nullptr) {
                header->set(st(HttpHeader)::TransferEncoding,
                    st(HttpHeader)::TransferChunked);
                return;
            }
            break;
        }
    }

    header->setContentLength(_computeContentLength(packet));
}

int _HttpPacketWriter::_flush(HttpPacket packet,bool send) {
    //update content length
    auto header = packet->getHeader();
    
    _updateHttpHeader(packet);

    //start flush
    String headString = header->toString(packet->getProtocol())->append(st(HttpText)::CRLF,// change line
                                                                        st(HttpText)::CRLF // blank line
                                                                        );
    if(_write(headString->toByteArray(),send) != 0) {
        return -1;
    }
    
    //start send content
    switch(packet->getProtocol()) {
        case st(HttpProtocol)::HttpRequest:
            _flushRequest(packet,send);
        break;

        case st(HttpProtocol)::HttpResponse:
            _flushResponse(packet,send);
        break;
    }

    return 0;
}

int _HttpPacketWriter::_flushRequest(HttpPacket packet,bool send) {
    //http multipart
    HttpMultiPart multiPart = packet->getEntity()->getMultiPart();

    if (multiPart != nullptr) {
        if (multiPart->contents->size() > 0) {
            ListIterator<KeyValuePair<String, String>> iterator =
                multiPart->contents->getIterator();
            while (iterator->hasValue()) {
                KeyValuePair<String, String> content = iterator->getValue();
                String v = st(HttpText)::BoundaryBeginning
                            ->append(multiPart->getBoundary(),st(HttpText)::CRLF,
                                    st(HttpHeader)::ContentDisposition,
                                    createString(": "),
                                    st(HttpMime)::FormData,
                                    createString("; "),
                                    st(HttpText)::MultiPartName,
                                    createString("=\""),
                                    content->getKey(),
                                    createString("\""),
                                    st(HttpText)::CRLF,
                                    st(HttpText)::CRLF,
                                    content->getValue(),
                                    st(HttpText)::CRLF);
                _write(v->toByteArray(),send);
                iterator->next();
            }
        }
        
        if (multiPart->files->size() > 0) {
            ListIterator<HttpMultiPartFile> iterator = multiPart->files->getIterator();

            while (iterator->hasValue()) {
                HttpMultiPartFile partFile = iterator->getValue();
                String contentDisposition =  st(HttpText)::BoundaryBeginning
                                            ->append(multiPart->getBoundary(),
                                                    st(HttpText)::CRLF,
                                                    st(HttpHeader)::ContentDisposition,
                                                    createString(": "),
                                                    st(HttpMime)::FormData,
                                                    createString("; "),
                                                    st(HttpText)::MultiPartName,
                                                    createString("="),
                                                    createString("\""),
                                                    partFile->getKey(),
                                                    createString("\";"),
                                                    st(HttpText)::MultiPartFileName,
                                                    createString("=\""),
                                                    partFile->getFile()->getName(),
                                                    createString("\""),
                                                    st(HttpText)::CRLF,
                                                    st(HttpText)::CRLF);
                _write(contentDisposition->toByteArray(),send);

                FileInputStream stream =
                    createFileInputStream(partFile->getFile());
                stream->open();
                ByteArray readBuff = createByteArray(mDefaultSize);
                //int index = 0;
                int count = 1;
                while (count > 0) {
                    count = stream->readTo(readBuff);
                    readBuff->quickShrink(count);
                    _write(readBuff,send);
                    readBuff->quickRestore();
                }

                _write(st(HttpText)::CRLF->toByteArray(),send);
                iterator->next();
            }
        }
        
        String finish = st(HttpText)::BoundaryBeginning ->append(multiPart->getBoundary(),
                                                        st(HttpText)::BoundaryBeginning,
                                                        st(HttpText)::CRLF);
        _write(finish->toByteArray(),send);
    } else {
        ByteArray body = packet->getEntity()->getContent();
        _write(body,send);
    }

    int index = mWriter->getIndex();
    if(index != 0) {
        mStream->write(mBuff, 0, index);
    }

    return 0;
}

int _HttpPacketWriter::_flushResponse(HttpPacket packet,bool send) {
    File file = packet->getEntity()->getChunkFile();
    if (file != nullptr) {
        FileInputStream stream = createFileInputStream(file);
        stream->open();
        long filesize = file->length();
        ByteArray readBuff = createByteArray(mDefaultSize);
        while (filesize != 0) {
            int readlength = mDefaultSize;
            if(filesize < mDefaultSize) {
                readlength = filesize;
            }
            String chunkLength = createInteger(readlength)
                                ->toHexString()
                                ->append(st(HttpText)::CRLF);
            _write(chunkLength->toByteArray(),send);

            int len = stream->read(readBuff);
            readBuff->quickShrink(len);
            _write(readBuff,send);
            readBuff->quickRestore();
            
            String end = nullptr;
            if (filesize == 0) {
                end = st(HttpText)::CRLF->append(createString("0"),st(HttpText)::HttpEnd);
            } else {
                end = st(HttpText)::CRLF;
            }

            _write(end->toByteArray(),send);
        }
    } else {
        auto content = packet->getEntity()->getContent();
        if(content != nullptr && content->size() != 0) {
            _write(packet->getEntity()->getContent(),send);
            //_write(st(HttpText)::CRLF->toByteArray(),send);
        }
    }

    //flush end
    int index = mWriter->getIndex();
    printf("index is %d \n",index);
    if(index != 0) {
        int ret = mStream->write(mBuff, 0, index);
        printf("stream write ret is %d \n",ret);
    }

    return 0;
}

int _HttpPacketWriter::_write(ByteArray data,bool send) {
    int length = data->size();
    int start = 0;
    while(length != 0) {
        int remiderSize = mWriter->getReminderSize();
        if(length > remiderSize) {
            mWriter->writeByteArray(data,start,remiderSize);
            length = length - remiderSize;
            start += remiderSize;
            if(send) {
                mStream->write(mBuff);
                mWriter->reset();
            } else {
                //TODO Log!!!
                return -1;
            }
        } else {
            mWriter->writeByteArray(data,start,data->size() - start);
            length = length - (data->size() - start);
            printf("length is %d \n",length);
        }
    }

    return 0;
}

} // namespace obotcha
