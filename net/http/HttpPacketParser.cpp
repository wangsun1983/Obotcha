#include "HttpPacketParser.hpp"
#include "ArrayList.hpp"
#include "HttpCacheControl.hpp"
#include "HttpContentType.hpp"
#include "HttpInternalException.hpp"
#include "HttpText.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "HttpMime.hpp"

namespace obotcha {

_HttpPacketParser::_HttpPacketParser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(
        mEnv->getInt(st(Enviroment)::gHttpBufferSize, 64 * 1024));
    mReader = createByteRingArrayReader(mBuff);
    mBodyStartCount = 0;
    mStatus = Idle;
    mSubStatus = None;
}

void _HttpPacketParser::reset() {
    mBuff->reset();
    mReader->reset();
    mBodyStartCount = 0;
    mStatus = Idle;
    mSubStatus = None;
}

int _HttpPacketParser::pushHttpData(ByteArray data) {
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
        LOG(ERROR) << "HttpPacketParser error ,data overflow";
        return -1;
    }

    return 0;
}

HttpPacket _HttpPacketParser::parseEntireRequest(String request) {
    mBuff->reset();
    mBuff->push((byte *)request->toChars(), 0, request->size());
    ArrayList<HttpPacket> result = doParse();
    if (result == nullptr || result->size() != 1) {
        return nullptr;
    }

    return result->get(0);
}

ArrayList<HttpPacket> _HttpPacketParser::doParse() {
    // printf("doParse mStatus is %d\n",mStatus);
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();

    byte v = 0;
    while (1) {
        switch (mStatus) {
        case Idle: {
            // printf("HttpPacketParser idle \n");
            if (mHttpHeaderParser == nullptr) {
                mHttpHeaderParser = createHttpHeaderParser(mReader);
                mHttpPacket = createHttpPacket();
            }

            HttpHeader header = mHttpHeaderParser->doParse();
            
            if (header == nullptr) {
                if (mSubStatus == HeadKeyValueParse) {
                    packets->add(mHttpPacket);
                }
                return packets;
            }
            if (mSubStatus == HeadKeyValueParse) {
                mHttpPacket->getHeader()->addHttpHeader(header);
            } else {
                mHttpPacket->setHeader(header);
            }
            mStatus = BodyStart;
            continue;
        }

        case BodyStart: {
            // printf("HttpPacketParser BodyStart \n");
            // check whether there is a multipart
            auto contentlength = mHttpPacket->getHeader()->getContentLength();
            //String contenttype =
            //    mHttpPacket->getHeader()->get(st(HttpHeader)::ContentType);
            auto contenttype = mHttpPacket->getHeader()->getContentType();

            auto transferEncoding = mHttpPacket->getHeader()->getTransferEncoding();
            bool isTransferChuncked = false;

            if(transferEncoding != nullptr) {
                ArrayList<String> encodings = transferEncoding->get();    
                encodings->foreach([](String s) {
                    if(s->equalsIgnoreCase(st(HttpHeader)::TransferChunked)) {
                        return Global::Break;   
                    }
                    return Global::Continue;
                });
            }

            if (isTransferChuncked) {
                // this is a chunck parsesr
                // printf("HttpPacketParser BodyStart trace1\n");
                if (mSubStatus == HeadKeyValueParse) {
                    packets->add(mHttpPacket);
                    mChunkParser = nullptr;
                    return packets;
                }

                if (mChunkParser == nullptr) {
                    mChunkParser = createHttpChunkParser(mReader);
                }
                ByteArray data = mChunkParser->doParse();
                if (data != nullptr) {
                    mHttpPacket->getEntity()->setContent(data);
                    mChunkParser = nullptr;
                    mHttpHeaderParser->changeToParseKeyValue();
                }

                mSubStatus = HeadKeyValueParse;

                mStatus = Idle;
                continue;
            }
            if (contentlength == nullptr || contentlength->get() <= 0) {
                /*1. The client should wait for the server's EOF. That is, when
                 * neither content-length nor transfer-encoding is specified,
                 * the end of body is specified by the EOF.
                 */
                // printf("HttpPacketParser BodyStart trace2\n");
                auto con = mHttpPacket->getHeader()->getConnection();

                if (mHttpPacket->getHeader()->getUpgrade() != nullptr ||
                    mHttpPacket->getHeader()->getMethod() ==
                        st(HttpMethod)::Connect) {
                    int restLength = mReader->getReadableLength();
                    if (restLength != 0) {
                        mReader->move(restLength);
                        ByteArray content = mReader->pop();
                        mHttpPacket->getEntity()->setUpgrade(
                            content->toString());
                    }
                } else if (((con != nullptr) && con->get()->equals("close"))||
                           mHttpPacket->getHeader()->getType() ==
                               st(HttpHeader)::Response) {
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
                mMultiPartParser = nullptr;
                mChunkParser = nullptr;
                mStatus = Idle;
                continue;
            }

            if (contenttype != nullptr &&
                contenttype->getType()->indexOfIgnoreCase(
                    st(HttpMime)::MultiPartFormData) >= 0) {
                // printf("HttpPacketParser BodyStart trace3\n");
                if (mMultiPartParser == nullptr) {
                    try {
                        mMultiPartParser = createHttpMultiPartParser(
                            contenttype->getBoundary(), contentlength->get());
                    } catch (InitializeException &e) {
                        printf("HttpPacketParser BodyStart trace1_1\n");
                    }
                }

                if (mMultiPartParser != nullptr) {
                    // printf("HttpPacketParser BodyStart trace4\n");
                    HttpMultiPart multipart = mMultiPartParser->parse(mReader);
                    if (multipart != nullptr) {
                        printf("HttpPacketParser BodyStart trace4_1\n");
                        mHttpPacket->getEntity()->setMultiPart(multipart);
                        packets->add(mHttpPacket);
                        mMultiPartParser = nullptr;
                        mStatus = Idle;
                        continue;
                    }
                    return packets;
                }
            } else {
                // printf("HttpPacketParser BodyStart trace5\n");
                if (contentlength->get() <= mReader->getReadableLength()) {
                    // one packet get
                    // printf("HttpPacketParser BodyStart trace6\n");
                    mReader->move(contentlength->get());
                    ByteArray content = mReader->pop();
                    // check whether it is a X-URLEncoded
                    if (contenttype != nullptr &&
                        st(HttpMime)::XFormUrlEncoded->indexOfIgnoreCase(
                            contenttype->getType()) >= 0) {
                        //ArrayList<KeyValuePair<String, String>>
                            //xFormEncodedPair =
                            //    st(HttpXFormUrlEncodedParser)::parse(
                             //       content->toString());
                        mHttpPacket->getEntity()->setContent(content->toString()->toByteArray());
                    } else {
                        if (mHttpPacket->getHeader()->getMethod() ==
                            st(HttpMethod)::Connect) {
                            mHttpPacket->getEntity()->setUpgrade(
                                content->toString());
                        } else {
                            mHttpPacket->getEntity()->setContent(content);
                        }
                    }
                    // we should check whether it is a upgrade message
                    if (mHttpPacket->getHeader()->getUpgrade() != nullptr) {
                        int resetLength = mReader->getReadableLength();
                        if (resetLength > 0) {
                            mReader->move(resetLength);
                            ByteArray content = mReader->pop();
                            mHttpPacket->getEntity()->setUpgrade(
                                content->toString());
                        }
                    }

                    mStatus = Idle;
                    mMultiPartParser = nullptr;
                    packets->add(mHttpPacket);
                    continue;
                } else {
                    return packets;
                }
            }
        } break;
        }
    }
    return packets;
}

int _HttpPacketParser::getStatus() { return mStatus; }

} // namespace obotcha
