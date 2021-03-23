#include "HttpRequestParser.hpp"
#include "ArrayList.hpp"
#include "HttpContentType.hpp"
#include "InitializeException.hpp"
#include "HttpInternalException.hpp"
#include "HttpCacheControl.hpp"
#include "HttpText.hpp"
#include "Log.hpp"
#include "HttpXFormUrlEncodedParser.hpp"

namespace obotcha {

_HttpRequestParser::_HttpRequestParser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(mEnv->getInt(st(Enviroment)::gHttpBufferSize,64*1024));
    mReader = createByteRingArrayReader(mBuff);
    mBodyStartCount = 0;
    mStatus = Idle;
    mSubStatus = None;
}

int _HttpRequestParser::pushHttpData(ByteArray data) {
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
        LOG(ERROR)<<"HttpRequestParser error ,data overflow";
        return -1;
    }

    return 0;
}

HttpPacket _HttpRequestParser::parseEntireRequest(String request) {
    mBuff->reset();
    mBuff->push((byte *)request->toChars(),0,request->size());
    ArrayList<HttpPacket> result = doParse();
    if(result == nullptr || result->size() != 1) {
        return nullptr;
    }

    return result->get(0);
}

ArrayList<HttpPacket> _HttpRequestParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte *end = (byte *)st(HttpText)::HttpEnd->toChars();
    static byte *CRLF = (byte *)st(HttpText)::CRLF->toChars();
    byte v = 0;
    while(1) {
        switch(mStatus) {
            case Idle:{
                if(mHttpHeaderParser == nullptr) {
                    switch(mSubStatus) {
                        case None:
                        mHttpHeaderParser = createHttpHeaderParser(mReader);
                        mHttpPacket = createHttpPacket();
                        break;

                        case HeadKeyValueParse:
                        printf("HeadKeyValueParse trace1 \n");
                        mHttpHeaderParser = createHttpHeaderParser(mReader,st(HttpHeaderParser)::KeyValueOnly);
                        break;
                    }
                }
                printf("HeadKeyValueParse trace1 _1\n");
                HttpHeader header = mHttpHeaderParser->doParse();
                if(header == nullptr) {
                    return packets;
                }
                printf("HeadKeyValueParse trace1 _2\n");
                if(mSubStatus == HeadKeyValueParse) {
                    printf("HeadKeyValueParse trace1 _3\n");
                    mHttpPacket->getHeader()->addHttpHeader(header);
                } else {
                    printf("HeadKeyValueParse trace2 \n");
                    mHttpPacket->setHeader(header);
                }
                
                mStatus = BodyStart;
                mHttpHeaderParser = nullptr;
                continue;
            }

            case BodyStart: {
                //check whether there is a multipart
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
                String encodingtype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::TransferEncoding);
                
                if(encodingtype != nullptr && encodingtype->equalsIgnoreCase(st(HttpHeader)::TransferChunked)) {
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
                        //packets->add(mHttpPacket);
                        mChunkParser = nullptr;
                        mStatus = Idle;
                        mSubStatus = HeadKeyValueParse;
                    }
                    continue;
                }

                if(contentlength == nullptr) {
                    //no contentlength,maybe it is only a html request
                    packets->add(mHttpPacket);
                    mMultiPartParser = nullptr;
                    mStatus = Idle;
                    continue;
                }
                
                if(contenttype != nullptr && contenttype->indexOfIgnoreCase(st(HttpContentType)::MultiPartFormData) >= 0) {
                    if(mMultiPartParser == nullptr) {
                        try {
                            mMultiPartParser = createHttpMultiPartParser(contenttype,contentlength->toBasicInt());
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
                    int length = contentlength->toBasicInt();
                    if(length <= mReader->getReadableLength()) {
                        //one packet get
                        mReader->move(length);
                        ByteArray content = mReader->pop();
                        //check whether it is a X-URLEncoded
                        if(st(HttpContentType)::XFormUrlEncoded->indexOfIgnoreCase(contenttype) >= 0) {
                            ArrayList<KeyValuePair<String,String>> xFormEncodedPair = st(HttpXFormUrlEncodedParser)::parse(content->toString());
                            mHttpPacket->getEntity()->setEncodedKeyValues(xFormEncodedPair);
                        } else {
                            mHttpPacket->getEntity()->setContent(content);
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

int _HttpRequestParser::getStatus() {
    return mStatus;
}

}
