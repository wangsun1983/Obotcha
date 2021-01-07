#include "HttpV1ResponseParser.hpp"
#include "ArrayList.hpp"
#include "HttpContentType.hpp"

namespace obotcha {

http_parser_settings _HttpV1ResponseParser::settings = {
    .on_message_begin = _HttpV1ResponseParser::on_message_begin,
    .on_url = _HttpV1ResponseParser::on_url,
    .on_header_field = _HttpV1ResponseParser::on_header_field,
    .on_header_value = _HttpV1ResponseParser::on_header_value,
    .on_headers_complete = _HttpV1ResponseParser::on_headers_complete,
    .on_body = _HttpV1ResponseParser::on_body,
    .on_message_complete = _HttpV1ResponseParser::on_message_complete,
    .on_reason = _HttpV1ResponseParser::on_reason,
    .on_chunk_header = _HttpV1ResponseParser::on_chunk_header,
    .on_chunk_complete = _HttpV1ResponseParser::on_chunk_complete
};

int _HttpV1ResponseParser::on_message_begin(http_parser *parser) {
    return 0;
}

int _HttpV1ResponseParser::on_url(http_parser*parser, const char *at, size_t length) {
    return 0;
}

int _HttpV1ResponseParser::on_header_field(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->tempParseField = createString(at,0,length);
    return 0;
}

int _HttpV1ResponseParser::on_header_value(http_parser*parser, const char *at, size_t length) {
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

int _HttpV1ResponseParser::on_headers_complete(http_parser*parser, const char *at, size_t length) {
    return 0;
}

int _HttpV1ResponseParser::on_body(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setBody(createByteArray((byte *)at,(int)length));
    return 0;
}

int _HttpV1ResponseParser::on_message_complete(http_parser *parser) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setMethod(parser->method);
    p->setStatusCode(parser->status_code);
    p->setMajorVersion(parser->http_major);
    p->setMinorVersion(parser->http_minor);
    return 0;
}

int _HttpV1ResponseParser::on_reason(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setReason(createString(at,0,length));
    return 0;
}

int _HttpV1ResponseParser::on_chunk_header(http_parser*parser) {
    return 0;
}

int _HttpV1ResponseParser::on_chunk_complete(http_parser*parser) {
    return 0;
}

_HttpV1ResponseParser::_HttpV1ResponseParser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(mEnv->getInt(st(Enviroment)::gHttpBufferSize,64*1024));
    mReader = createByteRingArrayReader(mBuff);
    mHeadEndCount = 0;
    mChunkEndCount = 0;
    mStatus = HttpV1ParseStatusIdle;
    mChunkSize = -1;
}

void _HttpV1ResponseParser::pushHttpData(ByteArray data) {
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

ArrayList<HttpPacket> _HttpV1ResponseParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte end[4] = {'\r','\n','\r','\n'};
    static byte chunksizeEnd[2] = {'\r','\n'};
    static byte chunkEnd[5] = {'\r','\n','0','\r','\n'};
    byte v = 0;
    while(1) {
        switch(mStatus) {
            case HttpV1ParseStatusIdle:{
                printf("HttpV1ParseStatusIdle trace2\n");
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
                printf("HttpClientParseStatusHeadStart trace2\n");
                ByteArray head = mReader->pop();
                memset(&mParser,0,sizeof(http_parser));
                mHttpPacket = createHttpPacket();
                mParser.data = reinterpret_cast<void *>(mHttpPacket.get_pointer());
                http_parser_init(&mParser, HTTP_RESPONSE);
                http_parser_execute(&mParser,
                                    &settings, 
                                    (const char *)head->toValue(), 
                                    head->size());
                mStatus = HttpClientParseStatusBodyStart;

                continue;
            }

            case HttpClientParseStatusBodyStart: {
                printf("HttpClientParseStatusBodyStart start\n");
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
                
                String transferEncoding = mHttpPacket->getHeader()->getValue(st(HttpHeader)::TransferEncoding);
                //TODO
                if(transferEncoding != nullptr && transferEncoding->endsWithIgnoreCase(st(HttpHeader)::TransferChunked)) {
                    printf("HttpClientParseStatusBodyStart trace0,mChunkSize is %d\n",mChunkSize);
                    if(mChunkSize == -1) {
                        //read chunksize
                        while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                            //printf("v is %c \n",v);
                            if(v == chunksizeEnd[mChunkEndCount]) {
                                mChunkEndCount++;
                            } else {
                                mChunkEndCount = 0;
                            }

                            if(mChunkEndCount == 2) {
                                mChunkEndCount = 0;
                                ByteArray dd = mReader->pop();
                                for(int i = 0;i<dd->size();i++) {
                                    printf("dd[%d] is %c \n",i,dd->at(i));
                                }
                                String chunklength = dd->toString();

                                chunklength = chunklength->subString(0,chunklength->size() - 2);
                                printf("chunklength str is %s \n",chunklength->toChars());
                                mChunkSize = chunklength->toHexInt();
                                printf("mChunkSize is %d \n",mChunkSize);
                                break;
                            }
                        }
                        printf("HttpClientParseStatusBodyStart trace1\n");

                        if(mChunkSize == -1) {
                            //last trunk
                            printf("HttpClientParseStatusBodyStart last trunk\n");
                            packets->add(mHttpPacket);
                            return packets;
                        }
                    }
                    int readablelength = mReader->getReadableLength();
                    //if(mReader->getReadableLength() >= mChunkSize) {
                    ByteArray body = mHttpPacket->getBody();
                    mReader->move(readablelength);
                    if(body == nullptr) {
                        body = mReader->pop();
                    } else {
                        body->append(mReader->pop());
                    }
                    printf("HttpClientParseStatusBodyStart trace2\n");
                    mHttpPacket->setBody(body);
                    printf("mReader readable length is %d,mChunkSize is %d \n",readablelength,mChunkSize);
                    if(readablelength < mChunkSize) {
                        mChunkSize -= readablelength;
                        printf("HttpClientParseStatusBodyStart trace2_1,mChunkSize is %d\n",mChunkSize);
                        return packets;
                    }
                    mChunkSize = -1;
                    mStatus = HttpV1ParseStatusIdle;
                    continue;
                }
            }
            break;
        }
    }
    return packets;
}

int _HttpV1ResponseParser::getStatus() {
    return mStatus;
}

}
