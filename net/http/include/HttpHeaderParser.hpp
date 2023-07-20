#ifndef __OBOTCHA_HTTP_HEADER_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_PARSER_HPP__

#include "Object.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpHeader.hpp"
#include "CRLFDetector.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderParser) {

public:
    enum ParseLineStatus {
        LineParseStart = 0, //ResponseStatus or RequestMethod
        ResponseReason,
        ResponseStatus,
        RequestUrl,
        RequsetVersion,
        ParseLineMax
    };

    enum ParseStatus {
        RequestLine = 0, //or response stats line
        Header,
        End
    };
    
    explicit _HttpHeaderParser(ByteRingArrayReader,int status = RequestLine);
    HttpHeader doParse();

private:
    int mStatus;
    int mParseLineStatus;
    ByteRingArrayReader mReader;
    HttpHeader mHeader;
    String mKey;
    String mPrevKey;
    String mValue;
    String mPredictValue;
    CRLFDetector mEndDetector;

    void parseRequestLine(String);
    void parseHeader(String);
};

}
#endif
