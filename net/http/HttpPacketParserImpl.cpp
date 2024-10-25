#include "HttpPacketParserImpl.hpp"
#include "HttpMethod.hpp"
#include "HttpMime.hpp"
#include "ForEveryOne.hpp"
#include "Inspect.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpPacketParserImpl::_HttpPacketParserImpl(ByteRingArray ring):mBuff(ring) {
    mReader = ByteRingArrayReader::New(mBuff);
}

_HttpPacketParserImpl::_HttpPacketParserImpl():
                _HttpPacketParserImpl(ByteRingArray::New(st(HttpPacket::kHttpBufferSize))) {

}

void _HttpPacketParserImpl::reset() {
    mBuff->reset();
    mReader->reset();
    mStatus = Idle;
}

int _HttpPacketParserImpl::pushData(ByteArray data) {
    // write data
    try {
        mBuff->push(data);
    } catch (ArrayIndexOutOfBoundsException &) {
        LOG(ERROR) << "HttpPacketParserImpl error ,data overflow";
        return -1;
    }
    return 0;
}

void _HttpPacketParserImpl::switchToIdle() {
    mHttpHeaderParser = nullptr;
    mMultiPartParser = nullptr;
    mChunkParser = nullptr;
    mSavedContentBuff = nullptr;
    mStatus = Idle;
}

bool _HttpPacketParserImpl::isClosePacket() {
    auto connection = mHttpPacket->getHeader()->getConnection();
    return connection != nullptr && connection->get()->sameAs("close");
}

bool _HttpPacketParserImpl::isUpgradePacket() {
    return mHttpPacket->getHeader()->getUpgrade() != nullptr;
}

bool _HttpPacketParserImpl::isConnectPacket() {
    return mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Id::Connect;
}

bool _HttpPacketParserImpl::isResponsePacket() {
    return mHttpPacket->getHeader()->getType() == st(Http)::PacketType::Response;
}

ArrayList<HttpPacket> _HttpPacketParserImpl::doParse() {
    ArrayList<HttpPacket> packets = ArrayList<HttpPacket>::New();
    while(true) {
        switch (mStatus) {
            case Idle: {
                if (mHttpHeaderParser == nullptr) {
                    mHttpHeaderParser = HttpHeaderParser::New(mReader);
                    mHttpPacket = HttpPacket::New();
                }

                HttpHeader header = mHttpHeaderParser->doParse();
                Inspect(header == nullptr,packets)

                auto type = header->getResponseReason() == nullptr?
                            st(Http)::PacketType::Request:st(Http)::PacketType::Response;
                mHttpPacket->setType(type);
                mHttpPacket->setHeader(header);
                mStatus = BodyStart;
                continue;
            }

            case BodyStart: {
                auto contentlength = mHttpPacket->getHeader()->getContentLength();
                auto contenttype = mHttpPacket->getHeader()->getContentType();
                auto transferEncoding = mHttpPacket->getHeader()->getTransferEncoding();
                bool isTransferChuncked = false;

                //check whether there is a chunck transfer
                if(transferEncoding != nullptr) {
                    ArrayList<String> encodings = transferEncoding->get();    
                    ForEveryOne(s,encodings) {
                        if(s->equalsIgnoreCase(st(HttpHeader)::TransferChunked)) {
                            isTransferChuncked = true;
                            break;
                        }
                    }
                }

                if (isTransferChuncked) {
                    if (mChunkParser == nullptr) {
                        mChunkParser = HttpChunkParser::New(mReader);
                    }

                    if (HttpChunk chunk = mChunkParser->doParse();chunk != nullptr) {
                        mHttpPacket->getEntity()->setChunk(chunk);
                        packets->add(mHttpPacket);
                        switchToIdle();
                        continue;
                    }
                    return nullptr;
                }

                if (contentlength == nullptr || contentlength->get() <= 0) {
                    /*1. The client should wait for the server's EOF. That is, when
                    * neither content-length nor transfer-encoding is specified,
                    * the end of body is specified by the EOF.
                    */
                    if(mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Id::Pri) {
                        if(mPriContentParser == nullptr) {
                            mPriContentParser = HttpPriContentParser::New(mReader);
                        }

                        auto content = mPriContentParser->doParse();
                        if(content != nullptr) {
                            mHttpPacket->getEntity()->setContent(content);
                        } else {
                            continue;
                        }
                    } else if (isUpgradePacket() 
                            || isConnectPacket() 
                            || isClosePacket() 
                            || isResponsePacket()) {
                        size_t restLength = mReader->getReadableLength();
                        if (restLength != 0) {
                            mReader->move(restLength);
                            ByteArray content = mReader->pop();
                            mHttpPacket->getEntity()->setContent(content);
                        }
                    }

                    //no contentlength,maybe it is only a html request or link
                    //Link:
                    //https://tools.ietf.org/id/draft-snell-link-method-01.html
                    //A payload within a LINK request message has no defined semantics.
                    //LINK /images/my_dog.jpg HTTP/1.1
                    //Host: example.org
                    //Link: <http://example.com/profiles/joe>; rel="tag"
                    //Link: <http://example.com/profiles/sally>; rel="tag"
                    // \r\n

                    packets->add(mHttpPacket);
                    switchToIdle();
                    continue;
                }

                if (contenttype != nullptr && 
                    contenttype->getType()->containsIgnoreCase(st(HttpMime)::MultiPartFormData)) {
                    if (mMultiPartParser == nullptr) {
                        mMultiPartParser = HttpMultiPartParser::New(contenttype->getBoundary());
                    }

                    if (HttpMultiPart multipart = mMultiPartParser->parse(mReader);
                        multipart != nullptr) {
                        mHttpPacket->getEntity()->setMultiPart(multipart);
                        packets->add(mHttpPacket);
                        switchToIdle();
                        continue;
                    }
                    return packets;
                } else {
                    size_t saveBuffSize = (mSavedContentBuff == nullptr)?0:mSavedContentBuff->size();
                    size_t readableLength = mReader->getReadableLength();
                    if ((contentlength->get() - saveBuffSize) <= readableLength) {
                        // one packet get
                        mReader->move(contentlength->get() - saveBuffSize);
                        ByteArray content = mReader->pop();
                        if(saveBuffSize != 0) {
                            mSavedContentBuff->append(content);
                            content = mSavedContentBuff;
                        }
                        
                        mHttpPacket->getEntity()->setContent(content);
                        packets->add(mHttpPacket);
                        switchToIdle();
                        continue;
                    } else {
                        if(readableLength != 0) {
                            mReader->move(readableLength);
                            ByteArray content = mReader->pop();
                            st(ByteArray)::Combine(mSavedContentBuff,content);
                        }
                        return packets;
                    }
                }
            } break;

            default:
                LOG(ERROR)<<"HttpPacketParseImpl doParse unknow status:"<<mStatus;
            break;
        }
    }
}

} // namespace obotcha
