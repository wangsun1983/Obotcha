#include "HttpHeaderParser.hpp"
#include "HttpText.hpp"
#include "HttpMethodParser.hpp"
#include "HttpVersionParser.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r) {
    mReader = r;
    mHeader = createHttpHeader();
    mCrlfCount = 0;
}

HttpHeader _HttpHeaderParser::doParse() {
    byte v = 0;
    const byte *CRLF = (const byte *)st(HttpText)::CRLF->toChars();
    while(mReader->readNext(v) != ByteRingArrayReadComplete) {
        switch(mStatus) {
            case Idle:{
                if(v == ' ') {
                    ByteArray method = mReader->pop();
                    int methodid = st(HttpMethodParser)::doParse(method->toString()->trimAll());
                    mHeader->setMethod(methodid);
                    mStatus = Url;
                }
                continue;
            }

            case Url:{
                if(v == ' ') {
                    ByteArray urlcontent = mReader->pop();
                    mHeader->setUrl(urlcontent->toString()->trimAll());
                    mStatus = Version;
                }
                continue;
            }

            case Version:{
                if(v == ' ') {
                   ByteArray vercontent = mReader->pop();
                   mHeader->setVersion(st(HttpVersionParser)::doParse(vercontent->toString()->trimAll()));
                   mStatus = NextLine;
                   mNextStatus = ContentKey;
                }
                continue;
            }

            case NextLine:{
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                } else {
                    mCrlfCount = 0;
                }

                if(mCrlfCount == 2) {
                    mStatus = mNextStatus;
                    mNextStatus = -1;
                    mCrlfCount = 0;
                    mReader->pop();
                }
                continue;
            }

            case ContentKey: {
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                }else if(v == ':') {
                    mCrlfCount = 0;
                    ByteArray key = mReader->pop();
                    mKey = createString((const char *)key->toValue(),0,key->size() - 1);
                    mStatus = ContentValue;
                }

                if(mCrlfCount == 2) {
                    //end
                    return mHeader;
                }
                continue;
            }
            
            case ContentValue:{
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                } else {
                    mCrlfCount = 0;
                }

                if(mCrlfCount == 2) {
                    mCrlfCount = 0;
                    ByteArray value = mReader->pop();
                    mValue = createString((const char *)value->toValue(),0,value->size() - 2);
                    mHeader->setValue(mKey,mValue);
                    mStatus = ContentKey;
                    mNextStatus = -1;
                }
                continue;
            }
        }
    }

    return nullptr;
}

}