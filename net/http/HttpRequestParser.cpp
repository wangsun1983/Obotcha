#include "HttpRequestParser.hpp"
#include "ArrayList.hpp"
#include "HttpContentType.hpp"
#include "InitializeException.hpp"
#include "HttpCacheControl.hpp"

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
    p->tempParseField = createString(at,0,length);
    return 0;
}

int _HttpRequestParser::on_header_value(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    String value = createString(at,0,length);
    if(p->tempParseField->equalsIgnoreCase(st(HttpHeader)::Cookie) 
        || p->tempParseField->equalsIgnoreCase(st(HttpHeader)::SetCookie)) {
        p->getHeader()->addCookie(createHttpCookie(value));
        return 0;
    } else if(p->tempParseField->equals(st(HttpHeader)::CacheControl)) {
        p->getHeader()->setCacheControl(value);
        return 0;
    } else if(p->tempParseField->equals(st(HttpHeader)::ContentType)) {
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
    p->setBody(createByteArray((byte *)at,(int)length));
    return 0;
}

int _HttpRequestParser::on_message_complete(http_parser *parser) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setMethod(parser->method);
    p->setStatusCode(parser->status_code);
    p->setMajorVersion(parser->http_major);
    p->setMinorVersion(parser->http_minor);
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
    mStatus = HttpParseStatusIdle;
}

void _HttpRequestParser::pushHttpData(ByteArray data) {
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
    //TODO
    //printf("mBuffSize is %ld,data size is %ld \n",mBuff->getSize(),data->size());
    try {
        mBuff->push(data);
    } catch(ArrayIndexOutOfBoundsException) {
        //TODO
    }
}

HttpPacket _HttpRequestParser::parseEntireRequest(String request) {
    memset(&mParser,0,sizeof(http_parser));
    HttpPacket packet = createHttpPacket();
    mParser.data = reinterpret_cast<void *>(packet.get_pointer());
    http_parser_init(&mParser, HTTP_REQUEST);
    http_parser_execute(&mParser,&settings, request->toChars(), request->size());
    return packet;
}

HttpPacket _HttpRequestParser::parseEntireResponse(String response) {
    memset(&mParser,0,sizeof(http_parser));
    HttpPacket packet = createHttpPacket();
    mParser.data = reinterpret_cast<void *>(packet.get_pointer());

    http_parser_init(&mParser, HTTP_RESPONSE);
    http_parser_execute(&mParser,&settings, response->toChars(), response->size());
    packet->setMethod(mParser.method);
    packet->setStatusCode(mParser.status_code);
    return packet;
}

ArrayList<HttpPacket> _HttpRequestParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte end[4] = {'\r','\n','\r','\n'};
    //static byte chunkEnd[5] = {'\r','\n','0','\r','\n'};
    while(1) {
        switch(mStatus) {
            case HttpParseStatusIdle:{
                printf("parser HttpParseStatusIdle\n");
                byte v = 0;
                while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                    if(v == end[mHeadEndCount]) {
                        mHeadEndCount++;
                    } else {
                        mHeadEndCount = 0;
                    }

                    if(mHeadEndCount == 4) {
                        mStatus = HttpClientParseStatusHeadStart;
                        mHeadEndCount = 0;
                        break;
                    }
                }

                if(mStatus != HttpClientParseStatusHeadStart) {
                    return packets;
                }
                
                continue;
            }
            
            case HttpClientParseStatusHeadStart: {
                printf("parser HttpClientParseStatusHeadStart\n");
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
                    mStatus = HttpParseStatusIdle;
                } else {
                    mStatus = HttpClientParseStatusBodyStart;
                }
                continue;
            }

            case HttpClientParseStatusBodyStart: {
                printf("parser HttpClientParseStatusBodyStart\n");
                //check whether there is a multipart
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
                if(contentlength == nullptr) {
                    packets->add(mHttpPacket);
                    mMultiPartParser = nullptr;
                    mStatus = HttpParseStatusIdle;
                    continue;
                }
                
                if(contenttype != nullptr && contenttype->indexOfIgnoreCase(st(HttpContentType)::MultiPartFormData) != -1) {
                    printf("parser HttpClientParseStatusBodyStart trace1\n");
                    if(mMultiPartParser == nullptr) {
                        try {
                            mMultiPartParser = createHttpMultiPartParser(contenttype,contentlength->toBasicInt());
                        } catch(InitializeException e){}
                    }

                    if(mMultiPartParser != nullptr) {
                        HttpMultiPart multipart = mMultiPartParser->parse(mReader);
                        if(multipart != nullptr) {
                            mHttpPacket->setMultiPart(multipart);
                            printf("add packet trace4 \n");
                            packets->add(mHttpPacket);
                            mMultiPartParser = nullptr;
                            mStatus = HttpParseStatusIdle;
                        }
                        return packets;
                    }
                } else if(contentlength != nullptr) {
                    int length = contentlength->toBasicInt();
                    if(length <= mReader->getReadableLength()) {
                        mReader->move(length);
                        mHttpPacket->setBody(mReader->pop());
                        mStatus = HttpParseStatusIdle;
                        printf("add packet trace2 \n");
                        mMultiPartParser = nullptr;
                        packets->add(mHttpPacket);
                        continue;
                    }
                } else {
                    //no contentlength,maybe it is only a html request
                    mStatus = HttpParseStatusIdle;
                    printf("add packet trace3 \n");
                    mMultiPartParser = nullptr;
                    packets->add(mHttpPacket);
                    continue;
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
