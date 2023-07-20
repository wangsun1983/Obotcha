#include "HttpHeaderParser.hpp"
#include "HttpCookieParser.hpp"
#include "HttpText.hpp"
#include "HttpHeaderLink.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpMethod.hpp"
#include "Definations.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r,int status) {
    mReader = r;
    mHeader = nullptr;
    mStatus = status;
    mParseLineStatus = LineParseStart;
    mEndDetector = createCRLFDetector();
}

void _HttpHeaderParser::parseRequestLine(String line) {
    int pos = 0;
    while (pos < line->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(line, pos,createString(" "));
        String directive = line->subString(tokenStart, pos - tokenStart)->trim();
        pos++;
        switch(mParseLineStatus) {
            case LineParseStart: {
                int method = st(HttpMethod)::toId(directive);
                if(method != -1) {
                    //this is a request
                    mHeader->setMethod(method);
                    mParseLineStatus = RequestUrl;
                } else {
                    //this is a response
                    HttpHeaderVersion version = createHttpHeaderVersion();
                    version->load(directive);
                    mHeader->setVersion(version);
                    mParseLineStatus = ResponseStatus;
                }
                break;
            }

            case ResponseReason: {
                mHeader->setResponseReason(directive);
                mParseLineStatus = LineParseStart;
                return;    
            }

            case ResponseStatus: {
                mHeader->setResponseStatus(directive->toBasicInt());
                mParseLineStatus = ResponseReason;
                break;
            }

            case RequestUrl: {
                mHeader->setUrl(createHttpUrl(directive));
                mParseLineStatus = RequsetVersion;
                break;
            }

            case RequsetVersion: {
                HttpHeaderVersion v = createHttpHeaderVersion();
                v->load(directive);
                mHeader->setVersion(v);
                mParseLineStatus = LineParseStart;
                return;
            }
        }
    }

    if(mParseLineStatus == RequsetVersion) {
        //http1.0_memo 
        //4.1 http message
        //HTTP-message   = Simple-Request            ; HTTP/0.9 messages
        //...
        //Simple-Request  = "GET" SP Request-URI CRLF
        //Simple-Response = [ Entity-Body ]
        auto v = mHeader->getVersion();
        v->setMajorVer(0);
        v->setMinorVer(9);
    }
}

void _HttpHeaderParser::parseHeader(String line) {
    int pos = 0;
    int tokenStart = pos;
    //remove all \r\n
    line = line->replaceAll("\r\n","");
    
    pos = st(HttpHeaderContentParser)::skipUntil(line, pos,
                                                    createString(":"));

    String directive = line->subString(tokenStart, pos - tokenStart)->trim();

    pos++;
    String content = line->subString(pos,line->size() - pos)->trim(); //remove \r\n
    mHeader->set(directive, content);
}

HttpHeader _HttpHeaderParser::doParse() {
    byte v = 0;
    if(mHeader == nullptr) {
        mHeader = createHttpHeader();
    }

    while (mReader->readNext(v) != NoContentRead) {
        switch (mStatus) {
            case RequestLine: {
                if(mEndDetector->isEnd(v)) {
                    //start parse method..
                    String content = mReader->pop()->toString();
                    if(content == nullptr || content->equals(st(HttpText)::CRLF)) {
                        //strage!!! first head contain \r\n 
                        continue;
                    }
                    parseRequestLine(content->subString(0,content->size() - 2)); //do not parse \r\n
                    mStatus = Header;
                }
                break;
            }

            case Header: {
                if(mEndDetector->isEnd(v)) {
                    String content = mReader->pop()->toString()->trim();
                    if(content->size() == 2 && content->equals(st(HttpText)::CRLF)) {
                        //This is end!!!
                        if(mPredictValue != nullptr) {
                            parseHeader(mPredictValue);
                        }
                        auto result = mHeader;
                        mHeader = nullptr;
                        mStatus = RequestLine;
                        return result;
                    }

                    // for some strage header contents which contains \r\n.....
                    // do not parse header value until we find next header.....
                    if(!content->contains(":")) { 
                        if(mPredictValue == nullptr) {
                            mPredictValue = content;
                        } else {
                            mPredictValue = mPredictValue->append(content);
                        }
                    } else {
                        if(mPredictValue != nullptr) {
                            parseHeader(mPredictValue);
                            mPredictValue = content;
                        } 

                        mPredictValue = content;
                    }
                }
                break;
            }
        }
    }
    return nullptr;
}

} // namespace obotcha