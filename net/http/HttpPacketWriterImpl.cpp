#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpPacketWriterImpl.hpp"
#include "HttpText.hpp"
#include "HttpMime.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

_HttpPacketWriterImpl::_HttpPacketWriterImpl(OutputStream stream,int defaultSize) {
    mStream = stream;
    mDefaultSize = defaultSize;
    mBuff = createByteArray(defaultSize);
    mWriter = createByteArrayWriter(mBuff);
}

int _HttpPacketWriterImpl::write(HttpPacket packet) {
    return _flush(packet,true);
}

ByteArray _HttpPacketWriterImpl::data(HttpPacket packet) {
    _flush(packet,false);
    return createByteArray(mBuff);
}

int _HttpPacketWriterImpl::_computeContentLength(HttpPacket packet) {
    if(packet->getHeader()->getType() == st(HttpHeader)::Request) {
        auto multiPart = packet->getEntity()->getMultiPart();
        if(multiPart != nullptr) {
            return multiPart->getContentLength();
        }
    }

    if(packet->getEntity()->getContent() != nullptr) {
        return packet->getEntity()->getContent()->size();
    }

    return 0;
}

void _HttpPacketWriterImpl::_updateHttpHeader(HttpPacket packet) {
    HttpHeader header = packet->getHeader();
    bool isNeedUpdateContentLength = true;

    switch(packet->getType()) {
        case st(HttpPacket)::Request: {
            auto multiPart = packet->getEntity()->getMultiPart();
            if(multiPart != nullptr) {
                HttpHeaderContentType contentType = createHttpHeaderContentType();
                contentType->setBoundary(multiPart->getBoundary());
                contentType->setType(st(HttpMime)::MultiPartFormData);
                header->setContentType(contentType);
            }
            break;
        }

        case st(HttpPacket)::Response: {
            HttpChunk chunk = packet->getEntity()->getChunk();
            if (chunk != nullptr) {
                auto encodings = header->getTransferEncoding();
                if(encodings == nullptr) {
                    encodings = createHttpHeaderTransferEncoding();
                    header->setTransferEncoding(encodings);
                }

                if(!encodings->get()->contains(st(HttpHeader)::TransferChunked)){
                    encodings->add(st(HttpHeader)::TransferChunked);
                }

                isNeedUpdateContentLength = false;
            }
            break;
        }
    }

    if(isNeedUpdateContentLength) {
        header->setContentLength(createHttpHeaderContentLength(_computeContentLength(packet)));
    }
}

int _HttpPacketWriterImpl::_flush(HttpPacket packet,bool send) {
    //update content length
    auto header = packet->getHeader();
    _updateHttpHeader(packet);
    //start flush
    String headString = header->toString(packet->getType())->append(st(HttpText)::CRLF,// change line
                                                                        st(HttpText)::CRLF // blank line
                                                                        );
    if(_write(headString->toByteArray(),send) != 0) {
        return -1;
    }

    //start send content
    switch(packet->getType()) {
        case st(HttpPacket)::Request:
            _flushRequest(packet,send);
        break;

        case st(HttpPacket)::Response:
            _flushResponse(packet,send);
        break;
    }

    return 0;
}

int _HttpPacketWriterImpl::_flushRequest(HttpPacket packet,bool send) {
    HttpMultiPart multiPart = packet->getEntity()->getMultiPart();

    if (multiPart != nullptr) {
        multiPart->onCompose([this,send](ByteArray data) {
            this->_write(data,send);
        });

    } else {
        ByteArray body = packet->getEntity()->getContent();
        if(body != nullptr && body->size() != 0) {
            _write(body,send);
        }
    }

    return _finishWrite();
}

int _HttpPacketWriterImpl::_flushResponse(HttpPacket packet,bool send) {
    HttpChunk chunk = packet->getEntity()->getChunk();
    if (chunk != nullptr) {
        chunk->onCompose([this,send](ByteArray data) {
            _write(data,send);
        });
    } else {
        auto content = packet->getEntity()->getContent();
        if(content != nullptr && content->size() != 0) {
            _write(packet->getEntity()->getContent(),send);
        }
    }
    return _finishWrite();
}

int _HttpPacketWriterImpl::_write(ByteArray data,bool send) {
    int length = data->size();
    int start = 0;
    while(length != 0) {
        int remiderSize = mWriter->getReminderSize();
        printf("remiderSize is %d,length is %d \n",remiderSize,length);
        if(length > remiderSize) {
            mWriter->write(data,start,remiderSize);
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
            mWriter->write(data,start,data->size() - start);
            length = length - (data->size() - start);
        }
    }
    return 0;
}

int _HttpPacketWriterImpl::_finishWrite() {
    int index = mWriter->getIndex();
    if(index != 0) {
        mStream->write(mBuff, 0, index);
        mWriter->reset();
    }

    return 0;
}

} // namespace obotcha
