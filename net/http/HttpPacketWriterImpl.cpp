#include "HttpPacketWriterImpl.hpp"
#include "HttpText.hpp"
#include "HttpMime.hpp"
#include "FileInputStream.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpPacketWriterImpl::_HttpPacketWriterImpl(OutputStream stream,
                                             int defaultSize):mStream(stream) {
    mBuff = createByteArray(defaultSize);
    mWriter = createByteArrayWriter(mBuff);
}

long _HttpPacketWriterImpl::write(HttpPacket packet) {
    return flush(packet,true);
}

ByteArray _HttpPacketWriterImpl::data(HttpPacket packet) {
    flush(packet,false);
    return createByteArray(mBuff);
}

long _HttpPacketWriterImpl::computeContentLength(HttpPacket packet) const {
    auto multiPart = packet->getEntity()->getMultiPart();
    if(multiPart != nullptr) {
        return multiPart->getContentLength();
    }

    if(packet->getEntity()->getContent() != nullptr) {
        return packet->getEntity()->getContent()->size();
    }

    return 0;
}

void _HttpPacketWriterImpl::updateHttpHeader(HttpPacket packet) const {
    HttpHeader header = packet->getHeader();
    bool isNeedUpdateContentLength = true;

    switch(packet->getType()) {
        case st(Http)::PacketType::Request: {
            auto multiPart = packet->getEntity()->getMultiPart();
            if(multiPart != nullptr) {
                HttpHeaderContentType contentType = createHttpHeaderContentType();
                contentType->setBoundary(multiPart->getBoundary());
                contentType->setType(st(HttpMime)::MultiPartFormData);
                header->setContentType(contentType);
            }
        } break;

        case st(Http)::PacketType::Response: {
            if (packet->getEntity()->getChunk() != nullptr) {
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
        } break;

        default:
            LOG(ERROR)<<"HttpPacketWriterImpl updateHttpHeader unknow type";
        break;
    }

    if(isNeedUpdateContentLength) {
        header->setContentLength(createHttpHeaderContentLength(computeContentLength(packet)));
    }
}

long _HttpPacketWriterImpl::flush(HttpPacket packet,bool send) {
    //update content length
    auto header = packet->getHeader();
    updateHttpHeader(packet);

    //start flush
    String headString = header->toString(packet->getType())->append(st(HttpText)::CRLF,      // change line
                                                                        st(HttpText)::CRLF); // blank line
    if(write(headString->toByteArray(),send) != 0) {
        return -1;
    }

    //start send content
    HttpMultiPart multiPart = packet->getEntity()->getMultiPart();
    HttpChunk chunk = packet->getEntity()->getChunk();
    if(packet->getType() == st(Http)::PacketType::Request && multiPart != nullptr) {
        multiPart->onCompose([this,send](ByteArray data) {
            write(data,send);
        });
    } else if (packet->getType() == st(Http)::PacketType::Response && chunk != nullptr) {
        chunk->onCompose([this,send](ByteArray data) {
            write(data,send);
        });
    } else {
        ByteArray content = packet->getEntity()->getContent();
        if(content != nullptr && content->size() != 0) {
            write(content,send);
        }
    }

    //finish write,flush all data
    if(send) {
        int index = mWriter->getIndex();
        if(index != 0) {
            mStream->write(mBuff, 0, index);
        }
    }

    mWriter->reset();
    return 0;
}

int _HttpPacketWriterImpl::write(ByteArray data,bool send) {
    int length = data->size();
    int start = 0;
    while(length != 0) {
        int writeSize = std::min(mWriter->getReminderSize(),length);
        mWriter->write(data,start,writeSize);
        length = length - writeSize;
        start += writeSize;
        if(mWriter->getReminderSize() <= 0 && send) {
            mStream->write(mBuff);
            mWriter->reset();
        }
    }
    return 0;
}

} // namespace obotcha
