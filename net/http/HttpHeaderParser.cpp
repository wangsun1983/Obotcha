#include "HttpHeaderParser.hpp"
#include "HttpCookieParser.hpp"
#include "HttpText.hpp"
#include "HttpHeaderLink.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpMethod.hpp"
#include "Definations.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r,ParseStatus status):mStatus(status),mReader(r) {
}

void _HttpHeaderParser::parseRequestLine(String line) {
    int pos = 0;
    while (pos < line->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(line, pos,createString(" "));
        String directive = line->subString(tokenStart, pos - tokenStart)->trim();
        pos++;
        switch(mParseLineStatus) {
            case ParseLineStatus::LineParseStart: {
                if(auto method = st(HttpMethod)::toId(directive);
                    method != st(HttpMethod)::Id::Err) {
                    //this is a request
                    mHeader->setMethod(method);
                    mParseLineStatus = ParseLineStatus::RequestUrl;
                } else {
                    //this is a response
                    HttpHeaderVersion version = createHttpHeaderVersion();
                    version->load(directive);
                    mHeader->setVersion(version);
                    mParseLineStatus = ParseLineStatus::ResponseStatus;
                }
                break;
            }

            case ParseLineStatus::ResponseReason: {
                mHeader->setResponseReason(directive);
                mParseLineStatus = ParseLineStatus::LineParseStart;
                return;    
            }

            case ParseLineStatus::ResponseStatus: {
                mHeader->setResponseStatus(directive->toBasicInt());
                mParseLineStatus = ParseLineStatus::ResponseReason;
                break;
            }

            case ParseLineStatus::RequestUrl: {
                mHeader->setUrl(createHttpUrl(directive));
                mParseLineStatus = ParseLineStatus::RequsetVersion;
                break;
            }

            case ParseLineStatus::RequsetVersion: {
                HttpHeaderVersion v = createHttpHeaderVersion();
                v->load(directive);
                mHeader->setVersion(v);
                mParseLineStatus = ParseLineStatus::LineParseStart;
                return;
            }

            default:
                LOG(ERROR)<<"HttpHeaderParser parseRequestLine unknow status:"<<static_cast<int>(mParseLineStatus);
            break;
        }
    }

    if(mParseLineStatus == ParseLineStatus::RequsetVersion) {
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

    while (mReader->readNext(v) != st(Defination)::NoContentRead) {
        switch (mStatus) {
            case ParseStatus::RequestLine: {
                if(mEndDetector->isEnd(v)) {
                    //start parse method..
                    String content = mReader->pop()->toString();
                    if(content == nullptr || content->equals(st(HttpText)::CRLF)) {
                        //strage!!! first head contain \r\n 
                        continue;
                    }
                    parseRequestLine(content->subString(0,content->size() - 2)); //do not parse \r\n
                    mStatus = ParseStatus::Header;
                }  
            } break;

            case ParseStatus::Header: {
                if(mEndDetector->isEnd(v)) {
                    String content = mReader->pop()->toString()->trim();
                    if(content->size() == 2 && content->equals(st(HttpText)::CRLF)) {
                        //This is end!!!
                        if(mPredictValue != nullptr) {
                            parseHeader(mPredictValue);
                        }
                        auto result = mHeader;
                        mHeader = nullptr;
                        mStatus = ParseStatus::RequestLine;
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
            } break;

            default:
                LOG(ERROR)<<"HttpHeaderParser doParse,unknow status:"<<static_cast<int>(mStatus);
            break;
        }
    }
    return nullptr;
}

} // namespace obotcha