#include <stdio.h>
#include <string.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpParser.hpp"
#include "HttpHeaderParser.hpp"

namespace obotcha {

http_parser_settings _HttpParser::settings = {
    .on_message_begin = _HttpParser::on_message_begin,
    .on_url = _HttpParser::on_url,
    .on_header_field = _HttpParser::on_header_field,
    .on_header_value = _HttpParser::on_header_value,
    .on_headers_complete = _HttpParser::on_headers_complete,
    .on_body = _HttpParser::on_body,
    .on_message_complete = _HttpParser::on_message_complete,
    .on_reason = _HttpParser::on_reason,
    .on_chunk_header = _HttpParser::on_chunk_header,
    .on_chunk_complete = _HttpParser::on_chunk_complete
};


_HttpParser::_HttpParser() {
    memset(&mParser,0,sizeof(http_parser));
    mRequest = createHttpRequest();
}

HttpRequest _HttpParser::parseRequest(String request) {
    printf("request is %s \n",request->toChars());
    memset(&mParser,0,sizeof(http_parser));
    mParser.data = reinterpret_cast<void *>(this);
    mRequest = createHttpRequest();

    http_parser_init(&mParser, HTTP_REQUEST);
    int parsed = http_parser_execute(&mParser,&settings, request->toChars(), request->size());
    printf("parsed is %d,method is %d,version is %d.%d \n",parsed,mParser.method,mParser.http_major,mParser.http_minor);
    mRequest->setMethod(mParser.method);

    return mRequest;
}


int _HttpParser::on_message_begin(http_parser *parser) {
    printf("on_message_begin \n");
    return 0;
}

int _HttpParser::on_url(http_parser*parser, const char *at, size_t length) {
    _HttpParser *p = reinterpret_cast<_HttpParser *>(parser->data);
    String myurl = createString(at,0,length);
    p->mRequest->setUrl(myurl);
    printf("on_url is %s \n",myurl->toChars());
    return 0;
}

int _HttpParser::on_header_field(http_parser*parser, const char *at, size_t length) {
    _HttpParser *p = reinterpret_cast<_HttpParser *>(parser->data);
    p->mHeaderName = createString(at,0,length);
    return 0;
}

int _HttpParser::on_header_value(http_parser*parser, const char *at, size_t length) {
    _HttpParser *p = reinterpret_cast<_HttpParser *>(parser->data);
    String str = createString(at,0,length);
    printf("parse value is %s",str->toChars());
    printf("parse name is %s",p->mHeaderName->toChars());

    p->mRequest->getHeader()->setValue(st(HttpHeaderParser)::parseHttpHeader(p->mHeaderName),createString(at,0,length));
    return 0;
}

int _HttpParser::on_headers_complete(http_parser*parser, const char *at, size_t length) {
    printf("on_headers_complete \n");
    return 0;
}

int _HttpParser::on_body(http_parser*parser, const char *at, size_t length) {
    printf("on_body \n");
    _HttpParser *p = reinterpret_cast<_HttpParser *>(parser->data);
    p->mRequest->setBody(createByteArray(at,(int)length));
    return 0;
}

int _HttpParser::on_message_complete(http_parser *parser) {
    printf("on_message_complete \n");
    return 0;
}

int _HttpParser::on_reason(http_parser*parser, const char *at, size_t length) {
    _HttpParser *p = reinterpret_cast<_HttpParser *>(parser->data);
    p->mRequest->setReason(createString(at,0,length));
    return 0;
}

int _HttpParser::on_chunk_header(http_parser*parser) {
    printf("on_chunk_header \n");
    return 0;
}

int _HttpParser::on_chunk_complete(http_parser*parser) {
    printf("on_chunk_complete \n");
    return 0;
}

void _HttpParser::setUrl(String url) {
    mUrl = url;
}

String _HttpParser::getUrl() {
    return mUrl;
}

}
