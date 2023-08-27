#ifndef __OBOTCHA_HTTP_HEADER_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_PARSER_HPP__

#include "Object.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpHeader.hpp"
#include "CRLFDetector.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderParser) {

public:
    enum class ParseLineStatus {
        LineParseStart = 0, //ResponseStatus or RequestMethod
        ResponseReason,
        ResponseStatus,
        RequestUrl,
        RequsetVersion,
        ParseLineMax
    };

    enum class ParseStatus {
        RequestLine = 0, //or response stats line
        Header,
        End
    };
    
    explicit _HttpHeaderParser(ByteRingArrayReader,ParseStatus status = ParseStatus::RequestLine);
    HttpHeader doParse();

private:
    ParseStatus mStatus;
    ParseLineStatus mParseLineStatus = ParseLineStatus::LineParseStart;
    ByteRingArrayReader mReader;
    HttpHeader mHeader = nullptr;
    String mKey;
    String mPrevKey;
    String mValue;
    String mPredictValue;
    CRLFDetector mEndDetector = createCRLFDetector();

    void parseRequestLine(String);
    void parseHeader(String);
};

}
#endif
