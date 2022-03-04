#include "HttpPacketParserImpl.hpp"
#include "ArrayList.hpp"
#include "HttpHeaderCacheControl.hpp"
#include "HttpHeaderContentType.hpp"
#include "HttpInternalException.hpp"
#include "HttpText.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "HttpMime.hpp"

namespace obotcha {

_HttpPacketParserImpl::_HttpPacketParserImpl(ByteRingArray ring) {
    mBuff = ring;
    mReader = createByteRingArrayReader(mBuff);
    mStatus = Idle;
}

_HttpPacketParserImpl::_HttpPacketParserImpl():
                _HttpPacketParserImpl(createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 64 * 1024))) {

}

void _HttpPacketParserImpl::reset() {
    mBuff->reset();
    mReader->reset();
    mStatus = Idle;
}

int _HttpPacketParserImpl::pushData(ByteArray data) {
    // write data
#ifdef DUMP_HTTP_DATE
    File dumpfile = createFile("data.dt");
    // dumpfile->removeAll();
    dumpfile->createNewFile();
    FileOutputStream stream = createFileOutputStream(dumpfile);
    stream->open();
    stream->write(data);
    stream->flush();
#endif

    try {
        mBuff->push(data);
    } catch (ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR) << "HttpPacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _HttpPacketParserImpl::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    while (1) {
        switch (mStatus) {
            case Idle: {
                if (mHttpHeaderParser == nullptr) {
                    mHttpHeaderParser = createHttpHeaderParser(mReader);
                    mHttpPacket = createHttpPacket();
                }
                HttpHeader header = mHttpHeaderParser->doParse();
                if (header == nullptr) {
                    return packets;
                }

                if(header->getResponseReason() != nullptr) {
                    mHttpPacket->setType(st(HttpPacket)::Response);
                } else {
                    mHttpPacket->setType(st(HttpPacket)::Request);
                }

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
                    encodings->foreach([&isTransferChuncked](String s) {
                        if(s->equalsIgnoreCase(st(HttpHeader)::TransferChunked)) {
                            isTransferChuncked = true;
                            return Global::Break;   
                        }
                        return Global::Continue;
                    });
                }
                if (isTransferChuncked) {
                    if (mChunkParser == nullptr) {
                        mChunkParser = createHttpChunkParser(mReader);
                    }

                    ByteArray data = mChunkParser->doParse();
                    if (data != nullptr) {
                        mHttpPacket->getEntity()->setChunk(data);
                        packets->add(mHttpPacket);
                        mHttpHeaderParser = nullptr;
                        mMultiPartParser = nullptr;
                        mChunkParser = nullptr;
                        mStatus = Idle;
                        continue;
                    }
                    return nullptr;
                }

                if (contentlength == nullptr || contentlength->get() <= 0) {
                    /*1. The client should wait for the server's EOF. That is, when
                    * neither content-length nor transfer-encoding is specified,
                    * the end of body is specified by the EOF.
                    */
                    auto con = mHttpPacket->getHeader()->getConnection();
                    if(mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Pri) {
                        //TODO
                        if(mPriContentParser == nullptr) {
                            mPriContentParser = createHttpPriContentParser(mReader);
                        }

                        auto content = mPriContentParser->doParse();
                        if(content != nullptr) {
                            mHttpPacket->getEntity()->setContent(content);
                        } else {
                            continue;
                        }
                    } else if (mHttpPacket->getHeader()->getUpgrade() != nullptr ||
                        mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Connect) {
                        int restLength = mReader->getReadableLength();
                        if (restLength != 0) {
                            mReader->move(restLength);
                            ByteArray content = mReader->pop();
                            //mHttpPacket->getEntity()->setUpgradeContent(content->toString());
                            mHttpPacket->getEntity()->setContent(content);
                        }
                    } else if (((con != nullptr) && con->get()->equals("close"))||
                            mHttpPacket->getHeader()->getType() == st(HttpHeader)::Response) {
                        // connection:close,pop all data && close connection
                        int restLength = mReader->getReadableLength();
                        if (restLength != 0) {
                            mReader->move(restLength);
                            ByteArray content = mReader->pop();
                            mHttpPacket->getEntity()->setContent(content);
                        }
                    }

                    // no contentlength,maybe it is only a html request
                    packets->add(mHttpPacket);
                    mHttpHeaderParser = nullptr;
                    mMultiPartParser = nullptr;
                    mChunkParser = nullptr;
                    //isChunkedWTrailingHeaders = false;
                    mStatus = Idle;
                    continue;
                }

                if (contenttype != nullptr && 
                    contenttype->getType()->containsIgnoreCase(st(HttpMime)::MultiPartFormData)) {
                    if (mMultiPartParser == nullptr) {
                        mMultiPartParser = createHttpMultiPartParser(contenttype->getBoundary());
                    }

                    HttpMultiPart multipart = mMultiPartParser->parse(mReader);
                    if (multipart != nullptr) {
                        mHttpPacket->getEntity()->setMultiPart(multipart);
                        packets->add(mHttpPacket);
                        mHttpHeaderParser = nullptr;
                        mMultiPartParser = nullptr;
                        mChunkParser = nullptr;
                        mStatus = Idle;
                        continue;
                    }
                    return packets;
                } else {
                    int saveBuffSize = (mSavedContentBuff == nullptr)?0:mSavedContentBuff->size();
                    
                    if ((contentlength->get() - saveBuffSize) <= mReader->getReadableLength()) {
                        // one packet get
                        mReader->move(contentlength->get() - saveBuffSize);
                        ByteArray content = mReader->pop();
                        if(saveBuffSize != 0) {
                            mSavedContentBuff->append(content);
                            content = mSavedContentBuff;
                        }
                        // check whether it is a X-URLEncoded
                        if (mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Connect) {
                            //mHttpPacket->getEntity()->setUpgradeContent(content->toString());
                            mHttpPacket->getEntity()->setContent(content);
                        } else {
                            mHttpPacket->getEntity()->setContent(content);
                        }

                        mSavedContentBuff = nullptr;

                        // we should check whether it is a upgrade message
                        //Test Case UPGRADE_POST_REQUEST
                        if (mHttpPacket->getHeader()->getUpgrade() != nullptr) {
                            int resetLength = mReader->getReadableLength();
                            if (resetLength > 0) {
                                mReader->move(resetLength);
                                ByteArray content = mReader->pop();
                                //mHttpPacket->getEntity()->setUpgradeContent(content->toString());
                                mHttpPacket->getEntity()->setContent(content);
                            }
                        }

                        mStatus = Idle;
                        packets->add(mHttpPacket);
                        mHttpHeaderParser = nullptr;
                        mMultiPartParser = nullptr;
                        mChunkParser = nullptr;
                        continue;
                    } else {
                        int length = mReader->getReadableLength();
                        if(length != 0) {
                            mReader->move(length);
                            ByteArray content = mReader->pop();
                            if(saveBuffSize == 0) {
                                mSavedContentBuff = content;
                            } else {
                                mSavedContentBuff->append(content);
                            }
                        }
                        return packets;
                    }
                }
            } 
            break;
        }
    }
    return packets;
}


} // namespace obotcha
