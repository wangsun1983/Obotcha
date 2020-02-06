#include "HttpV1Parser.hpp"
#include "ArrayList.hpp"

namespace obotcha {

http_parser_settings _HttpV1Parser::settings = {
    .on_message_begin = _HttpV1Parser::on_message_begin,
    .on_url = _HttpV1Parser::on_url,
    .on_header_field = _HttpV1Parser::on_header_field,
    .on_header_value = _HttpV1Parser::on_header_value,
    .on_headers_complete = _HttpV1Parser::on_headers_complete,
    .on_body = _HttpV1Parser::on_body,
    .on_message_complete = _HttpV1Parser::on_message_complete,
    .on_reason = _HttpV1Parser::on_reason,
    .on_chunk_header = _HttpV1Parser::on_chunk_header,
    .on_chunk_complete = _HttpV1Parser::on_chunk_complete
};

int _HttpV1Parser::on_message_begin(http_parser *parser) {
    printf("on_message_begin \n");
    return 0;
}

int _HttpV1Parser::on_url(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    String myurl = createString(at,0,length);
    p->setUrl(myurl);
    printf("on_url is %s \n",myurl->toChars());
    return 0;
}

int _HttpV1Parser::on_header_field(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->tempParseField = createString(at,0,length);
    return 0;
}

int _HttpV1Parser::on_header_value(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    
    p->getHeader()->setValue(
        p->tempParseField,
        createString(at,0,length));
    return 0;
}

int _HttpV1Parser::on_headers_complete(http_parser*parser, const char *at, size_t length) {
    printf("on_headers_complete \n");
    return 0;
}

int _HttpV1Parser::on_body(http_parser*parser, const char *at, size_t length) {
    printf("on_body \n");
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setBody(createByteArray((byte *)at,(int)length));
    return 0;
}

int _HttpV1Parser::on_message_complete(http_parser *parser) {
    printf("on_message_complete \n");
    return 0;
}

int _HttpV1Parser::on_reason(http_parser*parser, const char *at, size_t length) {
    _HttpPacket *p = reinterpret_cast<_HttpPacket *>(parser->data);
    p->setReason(createString(at,0,length));
    return 0;
}

int _HttpV1Parser::on_chunk_header(http_parser*parser) {
    printf("on_chunk_header \n");
    return 0;
}

int _HttpV1Parser::on_chunk_complete(http_parser*parser) {
    printf("on_chunk_complete \n");
    return 0;
}

_HttpV1Parser::_HttpV1Parser() {
    mEnv = st(Enviroment)::getInstance();
    mBuff = createByteRingArray(mEnv->getInt(st(Enviroment)::gHttpBufferSize));
    mReader = createByteRingArrayReader(mBuff);
    mHeadEndCount = 0;
    mChunkEndCount = 0;
}

void _HttpV1Parser::pushHttpData(ByteArray data) {
    printf("pushHttpData data is %s \n",data->toString()->toChars());
    //for(int i = 0;i <data->size();i++) {
    //    printf("data[%d] is %x \n",i,data->at(i));
    //}
    mBuff->push(data);
}

HttpPacket _HttpV1Parser::parseEntireRequest(String request) {
    printf("request is %s \n",request->toChars());
    memset(&mParser,0,sizeof(http_parser));
    mParser.data = reinterpret_cast<void *>(this);
    HttpPacket packet = createHttpPacket();

    http_parser_init(&mParser, HTTP_REQUEST);
    http_parser_execute(&mParser,&settings, request->toChars(), request->size());
    //printf("parsed is %d,method is %d,version is %d.%d \n",parsed,mParser.method,mParser.http_major,mParser.http_minor);
    //printf("mParser.status_code is %d \n",mParser.status_code);
    packet->setMethod(mParser.method);
    //mPacket->setStatusCode(mParser.status_code);
    return packet;
}

HttpPacket _HttpV1Parser::parseEntireResponse(String response) {
    printf("parseResponse response is %s \n",response->toChars());
    memset(&mParser,0,sizeof(http_parser));
    mParser.data = reinterpret_cast<void *>(this);
    HttpPacket packet = createHttpPacket();

    http_parser_init(&mParser, HTTP_RESPONSE);
    http_parser_execute(&mParser,&settings, response->toChars(), response->size());
    //printf("parsed is %d,method is %d,version is %d.%d \n",parsed,mParser.method,mParser.http_major,mParser.http_minor);
    //printf("mParser.status_code is %d \n",mParser.status_code);
    packet->setMethod(mParser.method);
    packet->setStatusCode(mParser.status_code);
    return packet;
}

ArrayList<HttpPacket> _HttpV1Parser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    static byte end[4] = {'\r','\n','\r','\n'};
    static byte chunkEnd[5] = {'\r','\n','0','\r','\n'};

    while(1) {
        switch(mStatus) {
            case HttpV1ParseStatusIdle:{
                printf("status is HttpV1ParseStatusIdle \n");
                byte v = 0;
                while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                    //printf("Reader next is %x \n",v);
                    if(v == end[mHeadEndCount]) {
                        mHeadEndCount++;
                    } else {
                        mHeadEndCount = 0;
                    }

                    if(mHeadEndCount == 4) {
                        printf("headencount is %d \n",mHeadEndCount);
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
                printf("status is HttpClientParseStatusHeadStart \n");
                ByteArray head = mReader->pop();

                printf("mReader cursor is %d \n",mReader->getCursor());
                printf("head size is %d \n",head->size());
                printf("head is %s \n",head->toString()->toChars());
                memset(&mParser,0,sizeof(http_parser));
                mHttpPacket = createHttpPacket();
                mParser.data = reinterpret_cast<void *>(mHttpPacket.get_pointer());
                http_parser_init(&mParser, HTTP_REQUEST);
                http_parser_execute(&mParser,
                                    &settings, 
                                    (const char *)head->toValue(), 
                                    head->size());
                //mHttpPacket->dump();
                mStatus = HttpClientParseStatusBodyStart;
                continue;
            }

            case HttpClientParseStatusBodyStart: {
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String transferEncoding = mHttpPacket->getHeader()->getValue(st(HttpHeader)::TransferEncoding);
                
                if(transferEncoding != nullptr) {
                    byte v = 0;
                    while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                        printf("Reader next is %x \n",v);
                        if(v == end[mChunkEndCount]) {
                            mChunkEndCount++;
                        } else {
                            mChunkEndCount = 0;
                        }

                        if(mChunkEndCount == 5) {
                            mStatus = HttpV1ParseStatusIdle;
                            //this is end of content
                            ByteArray chunk = mReader->pop();
                            chunk->qucikShrink(chunk->size()-5);
                            mHttpPacket->setBody(chunk);
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
                        packets->add(mHttpPacket);
                        continue;
                    }
                } else {
                    //no contentlength,maybe it is only a html request
                    mStatus = HttpV1ParseStatusIdle;
                    packets->add(mHttpPacket);
                    continue;

                }
                printf("status is HttpClientParseStatusBodyStart \n");
                return packets;
            }

            break;
        }
    }

    return packets;
}

int _HttpV1Parser::getStatus() {
    return mStatus;
}

}
