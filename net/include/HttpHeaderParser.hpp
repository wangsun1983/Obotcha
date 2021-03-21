#ifndef __OBOTCHA_HTTP_HEADER_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpHeaderParser) {

public:
    _HttpHeaderParser(ByteRingArrayReader);
    HttpHeader doParse();

private:
    enum ParseStatus {
        Idle = 0,
        NextLine,
        Method,
        Url,
        Version,
        ContentKey,
        ContentValue,
        End
    };

    int mStatus;
    int mNextStatus;

    ByteRingArrayReader mReader;
    HttpHeader mHeader;
    int mCrlfCount;
    String mKey;
    String mValue;
};

}
#endif
