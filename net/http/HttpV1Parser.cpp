#include "HttpV1Parser.hpp"
#include "ArrayList.hpp"
#include "HttpHeaderParser.hpp"

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
    String str = createString(at,0,length);

    p->getHeader()->setValue(
        st(HttpHeaderParser)::parseHttpHeader(p->tempParseField),
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
}

void _HttpV1Parser::pushHttpData(ByteArray data) {
    printf("pushHttpData data is %s \n",data->toString()->toChars());
    for(int i = 0;i <data->size();i++) {
        printf("data[%d] is %x \n",i,data->at(i));
    }
    mBuff->push(data);
}

ArrayList<HttpPacket> _HttpV1Parser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    byte end[4] = {'\r','\n','\r','\n'};
    printf("end[0] is %x ",end[0]);
    printf("end[1] is %x ",end[1]);
    printf("end[2] is %x ",end[2]);
    printf("end[3] is %x \n",end[3]);
    mHeadEndCount = 0;
    while(1) {
        switch(mStatus) {
            case HttpV1ParseStatusIdle:{
                printf("status is HttpV1ParseStatusIdle \n");
                byte v = 0;
                while(mReader->readNext(v) != ByteRingArrayReadComplete) {
                    printf("Reader next is %x \n",v);
                    if(v == end[mHeadEndCount]) {
                        mHeadEndCount++;
                    } else {
                        mHeadEndCount = 0;
                    }

                    if(mHeadEndCount == 4) {
                        printf("headencount is %d \n",mHeadEndCount);
                        mStatus = HttpClientParseStatusHeadStart;
                        break;
                    }
                }

                

                if(mStatus != HttpClientParseStatusHeadStart) {
                    return nullptr;
                }
                
                continue;
            }
            
            case HttpClientParseStatusHeadStart: {
                printf("status is HttpClientParseStatusHeadStart \n");
                ByteArray head = mReader->pop();
                
                /*
                for(int i = 0;i < head->size();i++) {
                    printf("%x",head->at(i));
                } */

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
                mHttpPacket->dump();
                mStatus = HttpClientParseStatusBodyStart;
                continue;
            }

            case HttpClientParseStatusBodyStart: {
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
