#include "HttpV1RequestParser.hpp"
#include "ArrayList.hpp"
#include "HttpContentType.hpp"

namespace obotcha {

http_parser_settings _HttpV1RequestParser::settings = {
    .on_message_begin = _HttpV1RequestParser::on_message_begin,
    .on_url = _HttpV1RequestParser::on_url,
    .on_header_field = _HttpV1RequestParser::on_header_field,
    .on_header_value = _HttpV1RequestParser::on_header_value,
    .on_headers_complete = _HttpV1RequestParser::on_headers_complete,
    .on_body = _HttpV1RequestParser::on_body,
    .on_message_complete = _HttpV1RequestParser::on_message_complete,
    .on_reason = _HttpV1RequestParser::on_reason,
    .on_chunk_header = _HttpV1RequestParser::on_chunk_header,
    .on_chunk_complete = _HttpV1RequestParser::on_chunk_complete
};

int _HttpV1RequestParser::on_message_begin(http_parser *parser) {
    return 0;
}

int _HttpV1RequestParser::on_url(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    String myurl = createString(at,0,length);
    p->setUrl(myurl);
    return 0;
}

int _HttpV1RequestParser::on_header_field(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->tempParseField = createString(at,0,length);
    return 0;
}

int _HttpV1RequestParser::on_header_value(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    String value = createString(at,0,length);
    if(p->tempParseField->equalsIgnoreCase("Cookie") 
        || p->tempParseField->equalsIgnoreCase("Set-Cookie")) {
        HttpCookie cookie = st(HttpCookieParser)::parseCookie(value);
        p->addCookie(cookie);
        return 0;
    }
    p->getHeader()->setValue(p->tempParseField,value);
    return 0;
}

int _HttpV1RequestParser::on_headers_complete(http_parser*parser, const char *at, size_t length) {
    return 0;
}

int _HttpV1RequestParser::on_body(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setBody(createByteArray((byte *)at,(int)length));
    return 0;
}

int _HttpV1RequestParser::on_message_complete(http_parser *parser) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setMethod(parser->method);
    p->setStatusCode(parser->status_code);
    p->setMajorVersion(parser->http_major);
    p->setMinorVersion(parser->http_minor);
    return 0;
}

int _HttpV1RequestParser::on_reason(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setReason(createString(at,0,length));
    return 0;
}

int _HttpV1RequestParser::on_chunk_header(http_parser*parser) {
    return 0;
}

int _HttpV1RequestParser::on_chunk_complete(http_parser*parser) {
    return 0;
}

_HttpV1RequestParser::_HttpV1RequestParser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(mEnv->getInt(st(Enviroment)::gHttpBufferSize,64*1024));
    mReader = createByteRingArrayReader(mBuff);
    mHeadEndCount = 0;
    mChunkEndCount = 0;
    mStatus = HttpV1ParseStatusIdle;
}

void _HttpV1RequestParser::pushHttpData(ByteArray data) {
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
    mBuff->push(data);
}

HttpPacket _HttpV1RequestParser::parseEntireRequest(String request) {
    memset(&mParser,0,sizeof(http_parser));
    HttpPacket packet = createHttpPacket();
    mParser.data = reinterpret_cast<void *>(packet.get_pointer());
    http_parser_init(&mParser, HTTP_REQUEST);
    http_parser_execute(&mParser,&settings, request->toChars(), request->size());
    return packet;
}

HttpPacket _HttpV1RequestParser::parseEntireResponse(String response) {
    memset(&mParser,0,sizeof(http_parser));
    HttpPacket packet = createHttpPacket();
    mParser.data = reinterpret_cast<void *>(packet.get_pointer());

    http_parser_init(&mParser, HTTP_RESPONSE);
    http_parser_execute(&mParser,&settings, response->toChars(), response->size());
    packet->setMethod(mParser.method);
    packet->setStatusCode(mParser.status_code);
    return packet;
}

ArrayList<HttpPacket> _HttpV1RequestParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte end[4] = {'\r','\n','\r','\n'};
    static byte chunkEnd[5] = {'\r','\n','0','\r','\n'};
    while(1) {
        switch(mStatus) {
            case HttpV1ParseStatusIdle:{
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
                    mStatus = HttpV1ParseStatusIdle;
                } else {
                    mStatus = HttpClientParseStatusBodyStart;
                }
                continue;
            }

            case HttpClientParseStatusBodyStart: {
                //check whether there is a multipart
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
                if(contenttype != nullptr && contenttype->indexOfIgnoreCase(st(HttpContentType)::MultiPareFormData) != -1) {
                    if(mMultiPartParser == nullptr || !contenttype->equalsIgnoreCase(mMultiPartParser->getHeaderBoundary())) {
                        mMultiPartParser = createHttpMultiPartParser(contenttype,contentlength->toBasicInt());
                    }

                    HttpMultiPart multipart = mMultiPartParser->parse(mReader);
                    if(multipart != nullptr) {
                        mHttpPacket->setMultiPart(multipart);
                        printf("add packet trace4 \n");
                        packets->add(mHttpPacket);
                        mStatus = HttpV1ParseStatusIdle;
                    }
                    return packets;
                }
                String transferEncoding = mHttpPacket->getHeader()->getValue(st(HttpHeader)::TransferEncoding);
                
                if(transferEncoding != nullptr) {
                    byte v = 0;
                    while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                        if(v == end[mChunkEndCount]) {
                            mChunkEndCount++;
                        } else {
                            mChunkEndCount = 0;
                        }

                        if(mChunkEndCount == 5) {
                            mStatus = HttpV1ParseStatusIdle;
                            //this is end of content
                            ByteArray chunk = mReader->pop();
                            chunk->quickShrink(chunk->size()-5);
                            mHttpPacket->setBody(chunk);
                            printf("add packet trace1 \n");
                            packets->add(mHttpPacket);
                            mChunkEndCount = 0;
                            break;
                        }
                    }

                    if(mStatus == HttpV1ParseStatusIdle) {
                        continue;
                    }

                    return packets;
                }
                
                if(contentlength != nullptr) {
                    int length = contentlength->toBasicInt();
                    if(length <= mReader->getReadableLength()) {
                        mReader->move(length);
                        mHttpPacket->setBody(mReader->pop());
                        mStatus = HttpV1ParseStatusIdle;
                        printf("add packet trace2 \n");
                        packets->add(mHttpPacket);
                        continue;
                    }
                } else {
                    //no contentlength,maybe it is only a html request
                    mStatus = HttpV1ParseStatusIdle;
                    printf("add packet trace3 \n");
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

int _HttpV1RequestParser::getStatus() {
    return mStatus;
}

}