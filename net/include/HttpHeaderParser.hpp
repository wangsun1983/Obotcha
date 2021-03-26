#ifndef __OBOTCHA_HTTP_HEADER_PARSER_HPP__
#define __OBOTCHA_HTTP_HEADER_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpHeaderParser) {

public:
    enum ParseMode {
        Full,
        KeyValueOnly
    };
    _HttpHeaderParser(ByteRingArrayReader);

    void changeToParseKeyValue();

    HttpHeader doParse();

private:
    enum ParseStatus {
        Idle = 0,
        NextLine,
        Method,
        Url,
        State,
        Reason,
        Version,
        ContentKey,
        ContentValue,
        End
    };

    int mStatus;
    int mNextStatus;

    int parseParticularHeader(String key,String value);

    ByteRingArrayReader mReader;
    HttpHeader mHeader;
    int mCrlfCount;
    String mKey;
    String mPrevKey;
    String mValue;
};

}
#endif
