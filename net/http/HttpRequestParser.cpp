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

http_parser_settings _HttpRequestParser::settings = {
    .on_message_begin = _HttpRequestParser::on_message_begin,
    .on_url = _HttpRequestParser::on_url,
    .on_header_field = _HttpRequestParser::on_header_field,
    .on_header_value = _HttpRequestParser::on_header_value,
    .on_headers_complete = _HttpRequestParser::on_headers_complete,
    .on_body = _HttpRequestParser::on_body,
    .on_message_complete = _HttpRequestParser::on_message_complete,
    .on_reason = _HttpRequestParser::on_reason,
    .on_chunk_header = _HttpRequestParser::on_chunk_header,
    .on_chunk_complete = _HttpRequestParser::on_chunk_complete
};

int _HttpRequestParser::on_message_begin(http_parser *parser) {
    return 0;
}

int _HttpRequestParser::on_url(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    String myurl = createString(at,0,length);
    p->setUrl(myurl);
    return 0;
}

int _HttpRequestParser::on_header_field(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->tempParseField = createString(at,0,length)->toLowerCase();
    return 0;
}

int _HttpRequestParser::on_header_value(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    String value = createString(at,0,length);
    if(p->tempParseField->equalsIgnoreCase(st(HttpHeader)::Cookie) 
        || p->tempParseField->equalsIgnoreCase(st(HttpHeader)::SetCookie)) {
        p->getHeader()->addCookie(createHttpCookie(value));
        return 0;
    } else if(p->tempParseField->equalsIgnoreCase(st(HttpHeader)::CacheControl)) {
        p->getHeader()->setCacheControl(createHttpCacheControl(value));
        return 0;
    } else if(p->tempParseField->equalsIgnoreCase(st(HttpHeader)::ContentType)) {
        p->getHeader()->setContentType(value);
        return 0;
    }
    p->getHeader()->setValue(p->tempParseField,value);
    return 0;
}

int _HttpRequestParser::on_headers_complete(http_parser*parser, const char *at, size_t length) {
    return 0;
}

int _HttpRequestParser::on_body(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    HttpEntity entity = createHttpEntity();
    entity->setContent(createByteArray((byte *)at,(int)length));
    p->setEntity(entity);
    return 0;
}

int _HttpRequestParser::on_message_complete(http_parser *parser) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setMethod(parser->method);
    p->setStatus(parser->status_code);
    p->setVersion(createHttpVersion(parser->http_major,parser->http_minor));
    return 0;
}

int _HttpRequestParser::on_reason(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setReason(createString(at,0,length));
    return 0;
}

int _HttpRequestParser::on_chunk_header(http_parser*parser) {
    return 0;
}

int _HttpRequestParser::on_chunk_complete(http_parser*parser) {
    return 0;
}

_HttpRequestParser::_HttpRequestParser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(mEnv->getInt(st(Enviroment)::gHttpBufferSize,64*1024));
    mReader = createByteRingArrayReader(mBuff);
    mHeadEndCount = 0;
    mChunkEndCount = 0;
    mStatus = Idle;
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
    memset(&mParser,0,sizeof(http_parser));
    HttpPacket packet = createHttpPacket();
    mParser.data = reinterpret_cast<void *>(packet.get_pointer());
    http_parser_init(&mParser, HTTP_REQUEST);
    http_parser_execute(&mParser,&settings, request->toChars(), request->size());
    return packet;
}

ArrayList<HttpPacket> _HttpRequestParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte *end = (byte *)st(HttpText)::DoubleLineEnd->toChars();
    while(1) {
        switch(mStatus) {
            case Idle:{
                byte v = 0;
                while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                    if(v == end[mHeadEndCount]) {
                        mHeadEndCount++;
                    } else {
                        mHeadEndCount = 0;
                    }

                    if(mHeadEndCount == 4) {
                        mStatus = HeadStart;
                        mHeadEndCount = 0;
                        break;
                    }
                }

                if(mStatus != HeadStart) {
                    return packets;
                }
                
                continue;
            }
            
            case HeadStart: {
                ByteArray head = mReader->pop();
                memset(&mParser,0,sizeof(http_parser));
                mHttpPacket = createHttpPacket();
                mParser.data = reinterpret_cast<void *>(mHttpPacket.get_pointer());
                http_parser_init(&mParser, HTTP_REQUEST);
                http_parser_execute(&mParser,
                                    &settings, 
                                    (const char *)head->toValue(), 
                                    head->size());
                if(mHttpPacket->mUrl == nullptr || mHttpPacket->mUrl->size() == 0) {
                    //this is a null packet
                    mStatus = Idle;
                } else {
                    mStatus = BodyStart;
                }
                continue;
            }

            case BodyStart: {
                //check whether there is a multipart
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
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
                        return packets;
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
                        printf("BodyStart add packet \n");
                        continue;
                    }
                }
                return packets;
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
