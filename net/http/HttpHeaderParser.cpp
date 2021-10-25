#include "HttpHeaderParser.hpp"
#include "HttpCookieParser.hpp"
#include "HttpMethodParser.hpp"
#include "HttpText.hpp"
#include "HttpHeaderLink.hpp"
#include "HttpMethodParser.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r) {
    mReader = r;
    mHeader = nullptr;
    mStatus = RequestLine;
    mParseLineStatus = LineParseStart;
    mCRLFIndex = 0;
}

void _HttpHeaderParser::changeToParseKeyValue() { mStatus = Header; }

bool _HttpHeaderParser::isLineEnd(byte &v) {
    if(v == '\r' && mCRLFIndex == 0) {
        mCRLFIndex = 1;
    } else if(v == '\n' && mCRLFIndex == 1) {
        mCRLFIndex = 0;
        return true;
    } else {
        mCRLFIndex = 0;
    }

    return false;
}

void _HttpHeaderParser::parseRequestLine(String line) {
    int pos = 0;
    printf("parseRequestLine,line size is %d \n",line->size());
    while (pos < line->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(line, pos,
                                                        createString(" "));
        printf("parseRequestLine,pos is %d,tokenStart s %d \n",pos,tokenStart);
        String directive =
                line->subString(tokenStart, pos - tokenStart)->trim();
        printf("directive is %s,%d,mParseLineStatus is %d \n",directive->toChars(),directive->size(),mParseLineStatus);
        pos++;

        if(directive->size() == 1) {
            continue;
        }
        printf("parseRequestLine trace,mParseLineStatus is %d \n",mParseLineStatus);

        switch(mParseLineStatus) {
            case LineParseStart: {
                int method = st(HttpMethodParser)::doParse(directive);
                
                if(method != -1) {
                    //this is a request
                    mHeader->setMethod(method);
                    mParseLineStatus = RequestUrl;
                } else {
                    //this is a response
                    HttpVersion version = createHttpVersion();
                    version->import(directive);
                    mHeader->setVersion(version);
                    mParseLineStatus = ResponseStatus;
                }
                printf("method is %d,mStatus is %d \n",method,mStatus);
                break;
            }

            case ResponseReason: {
                mHeader->setResponseReason(directive);
                return;    
            }

            case ResponseStatus: {
                mHeader->setResponseStatus(directive->toBasicInt());
                mParseLineStatus = ResponseReason;
                break;
            }

            case RequestUrl: {
                printf("requestUrl is %s \n",directive->toChars());
                HttpUrl url = createHttpUrl(directive);
                mHeader->setUrl(url);
                mParseLineStatus = RequsetVersion;
                break;
            }

            case RequsetVersion: {
                HttpVersion v = createHttpVersion();
                v->import(directive);
                mHeader->setVersion(v);

                mParseLineStatus = LineParseStart;
                return;
            }
        }
    }
}

void _HttpHeaderParser::parseHeader(String line) {
    int pos = 0;
    printf("parseHeader line is %s \n",line->toChars());
    while (pos < line->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(line, pos,
                                                        createString(":"));
        
        String directive =
                line->subString(tokenStart, pos - tokenStart)->trim();

        pos++;
        String content = line->subString(pos,line->size() - pos); //remove \r\n
        //printf("directive is %s,content is %s \n",directive->toChars(),content->toChars());
        mHeader->set(directive, content);
    }
}

HttpHeader _HttpHeaderParser::doParse() {
    byte v = 0;
    const byte *CRLF = (const byte *)st(HttpText)::CRLF->toChars();
    const byte *LF = (const byte *)st(HttpText)::LF->toChars();
    if(mHeader == nullptr) {
        mHeader = createHttpHeader();
    }

    while (mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
        switch (mStatus) {
            case RequestLine: {
                if(isLineEnd(v)) {
                    //start parse method..
                    String content = mReader->pop()->toString();
                    printf("content is %s \n",content->toChars());
                    parseRequestLine(content->subString(0,content->size() - 2)); //do not parse \r\n
                    mStatus = Header;
                }
                break;
            }

            case Header: {
                if(isLineEnd(v)) {
                    String content = mReader->pop()->toString();
                    if(content->size() == 2 && content->equals(st(HttpText)::CRLF)) {
                        //This is end!!!
                        auto result = mHeader;
                        mHeader = nullptr;
                        return result;
                    }

                    parseHeader(content->subString(0,content->size() - 2));
                }
                break;
            }
        }
    }

    return nullptr;
}

} // namespace obotcha