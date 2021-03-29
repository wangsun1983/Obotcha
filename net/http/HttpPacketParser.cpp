#include "HttpPacketParser.hpp"
#include "ArrayList.hpp"
#include "HttpContentType.hpp"
#include "InitializeException.hpp"
#include "HttpInternalException.hpp"
#include "HttpCacheControl.hpp"
#include "HttpText.hpp"
#include "Log.hpp"
#include "HttpXFormUrlEncodedParser.hpp"

namespace obotcha {

_HttpPacketParser::_HttpPacketParser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(mEnv->getInt(st(Enviroment)::gHttpBufferSize,64*1024));
    mReader = createByteRingArrayReader(mBuff);
    mBodyStartCount = 0;
    mStatus = Idle;
    mSubStatus = None;
}

int _HttpPacketParser::pushHttpData(ByteArray data) {
    //write data
#ifdef DUMP_HTTP_DATE
    File dumpfile = createFile("data.dt");
    //dumpfile->removeAll();
    dumpfile->createNewFile();
    FileOutputStream stream = createFileOutputStream(dumpfile);
    stream->open();
    stream->write(data);
    stream->flush();
#endif

    try {
        mBuff->push(data);
    } catch(ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR)<<"HttpPacketParser error ,data overflow";
        return -1;
    }

    return 0;
}

HttpPacket _HttpPacketParser::parseEntireRequest(String request) {
    mBuff->reset();
    mBuff->push((byte *)request->toChars(),0,request->size());
    ArrayList<HttpPacket> result = doParse();
    if(result == nullptr || result->size() != 1) {
        return nullptr;
    }

    return result->get(0);
}

ArrayList<HttpPacket> _HttpPacketParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte *end = (byte *)st(HttpText)::HttpEnd->toChars();
    static byte *CRLF = (byte *)st(HttpText)::CRLF->toChars();
    byte v = 0;
    while(1) {
        switch(mStatus) {
            case Idle:{
                if(mHttpHeaderParser == nullptr) {
                    mHttpHeaderParser = createHttpHeaderParser(mReader);
                    mHttpPacket = createHttpPacket();
                }
                
                HttpHeader header = mHttpHeaderParser->doParse();
                if(header == nullptr) {
                    if(mSubStatus == HeadKeyValueParse) {
                        packets->add(mHttpPacket);
                    }
                    return packets;
                }

                if(mSubStatus == HeadKeyValueParse) {
                    mHttpPacket->getHeader()->addHttpHeader(header);
                } else {
                    mHttpPacket->setHeader(header);
                }
                
                mStatus = BodyStart;
                //mHttpHeaderParser = nullptr;
                continue;
            }

            case BodyStart: {
                //check whether there is a multipart
                int contentlength = mHttpPacket->getHeader()->getContentLength();
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
                String encodingtype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::TransferEncoding);
                if(encodingtype != nullptr && encodingtype->indexOfIgnoreCase(st(HttpHeader)::TransferChunked) >= 0) {
                    //this is a chunck parsesr
                    if(mSubStatus == HeadKeyValueParse) {
                        packets->add(mHttpPacket);
                        mChunkParser = nullptr;
                        return packets;
                    }

                    if(mChunkParser == nullptr) {
                        mChunkParser = createHttpChunkParser(mReader);
                    }
                    ByteArray data = mChunkParser->doParse();
                    if(data != nullptr) {
                        mHttpPacket->getEntity()->setContent(data);
                        mChunkParser = nullptr;
                        mHttpHeaderParser->changeToParseKeyValue();
                    }
                    mSubStatus = HeadKeyValueParse;

                    mStatus = Idle;
                    continue;
                }
                if(contentlength <= 0) {
                    if(!mHttpPacket->getHeader()->isConnected()) {
                        //connection:close,pop all data && close connection
                        int restLength = mReader->getReadableLength();
                        if(restLength != 0) {
                            mReader->move(restLength);
                            ByteArray content = mReader->pop();
                            mHttpPacket->getEntity()->setContent(content);
                        }
                    } else if(mHttpPacket->getHeader()->getValue(st(HttpHeader)::Upgrade) != nullptr
                            ||mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Connect) {
                        int restLength = mReader->getReadableLength();
                        if(restLength != 0) {
                            mReader->move(restLength);
                            ByteArray content = mReader->pop();
                            mHttpPacket->getEntity()->setUpgrade(content->toString());
                            //printf("upgrade is %s \n",content->toValue());
                        }
                    }
                    //no contentlength,maybe it is only a html request
                    packets->add(mHttpPacket);
                    mMultiPartParser = nullptr;
                    mChunkParser = nullptr;
                    mStatus = Idle;
                    continue;
                }
                
                if(contenttype != nullptr && contenttype->indexOfIgnoreCase(st(HttpContentType)::MultiPartFormData) >= 0) {
                    if(mMultiPartParser == nullptr) {
                        try {
                            mMultiPartParser = createHttpMultiPartParser(contenttype,contentlength);
                        } catch(InitializeException &e){}
                    }

                    if(mMultiPartParser != nullptr) {
                        HttpMultiPart multipart = mMultiPartParser->parse(mReader);
                        if(multipart != nullptr) {
                            mHttpPacket->getEntity()->setMultiPart(multipart);
                            packets->add(mHttpPacket);
                            mMultiPartParser = nullptr;
                            mStatus = Idle;
                        }
                        continue;
                    }
                } else {
                    if(contentlength <= mReader->getReadableLength()) {
                        //one packet get
                        mReader->move(contentlength);
                        ByteArray content = mReader->pop();
                        //check whether it is a X-URLEncoded
                        if(st(HttpContentType)::XFormUrlEncoded->indexOfIgnoreCase(contenttype) >= 0) {
                            ArrayList<KeyValuePair<String,String>> xFormEncodedPair = st(HttpXFormUrlEncodedParser)::parse(content->toString());
                            mHttpPacket->getEntity()->setEncodedKeyValues(xFormEncodedPair);
                        } else {
                            if(mHttpPacket->getHeader()->getMethod() == st(HttpMethod)::Connect) {
                                mHttpPacket->getEntity()->setUpgrade(content->toString());
                            } else {
                                mHttpPacket->getEntity()->setContent(content);
                            }
                        }

                        //we should check whether it is a upgrade message
                        if(mHttpPacket->getHeader()->getValue(st(HttpHeader)::Upgrade) != nullptr) {
                            int resetLength = mReader->getReadableLength();
                            if(resetLength > 0) {
                                mReader->move(resetLength);
                                ByteArray content = mReader->pop();
                                mHttpPacket->getEntity()->setUpgrade(content->toString());
                            }
                        }

                        mStatus = Idle;
                        mMultiPartParser = nullptr;
                        packets->add(mHttpPacket);
                        continue;
                    }
                }
            }
            break;
        }
    }
    return packets;
}

int _HttpPacketParser::getStatus() {
    return mStatus;
}

}
