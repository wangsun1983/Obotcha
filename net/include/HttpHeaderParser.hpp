#ifndef __OBOTCHA_HTTP_HEADER_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpHeader.hpp"

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
    _HttpHeaderParser(ByteRingArrayReader);

    void changeToParseKeyValue();

    HttpHeader doParse();

private:
    enum ParseStatus {
        RequestLine = 0, //or response stats line
        Header,
        End
    };

    int mStatus;
    int mParseLineStatus;

    ByteRingArrayReader mReader;
    HttpHeader mHeader;
    int mCRLFIndex;
    String mKey;
    String mPrevKey;
    String mValue;

    String mPredictValue;

    bool isLineEnd(byte &v);
    void parseRequestLine(String);
    void parseHeader(String);
};

}
#endif
