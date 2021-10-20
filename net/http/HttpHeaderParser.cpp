#include "HttpHeaderParser.hpp"
#include "HttpCookieParser.hpp"
#include "HttpMethodParser.hpp"
#include "HttpText.hpp"
#include "HttpHeaderLink.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r) {
    mReader = r;
    mHeader = createHttpHeader();
    mCrlfCount = 0;
    mStatus = Idle;
    // mPrevKey = nullptr;
}

void _HttpHeaderParser::changeToParseKeyValue() { mStatus = ContentKey; }

HttpHeader _HttpHeaderParser::doParse() {
    byte v = 0;
    const byte *CRLF = (const byte *)st(HttpText)::CRLF->toChars();
    const byte *LF = (const byte *)st(HttpText)::LF->toChars();

    while (mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
        switch (mStatus) {
        case Idle: {
            if (v == 0x20) { //' '
                ByteArray method = mReader->pop();
                String tag = method->toString()->trimAll();
                int methodid = st(HttpMethodParser)::doParse(tag);
                if (methodid != -1) {
                    mHeader->setMethod(methodid);
                    mStatus = Url;
                } else {
                    // this may be a response
                    mHeader->setType(st(HttpHeader)::Response);
                    HttpVersion ver = createHttpVersion();
                    ver->import(tag);
                    //HttpVersion ver = st(HttpVersionParser)::doParse(tag);
                    if (ver != nullptr) {
                        mHeader->setVersion(ver);
                        mStatus = State;
                    } else {
                        // TODO
                    }
                }
            }
            continue;
        }

        case State: {
            if (v == CRLF[mCrlfCount]) {
                mCrlfCount++;
            } else if (v == LF[0]) {
                mCrlfCount = 1;
            } else {
                mCrlfCount = 0;
            }

            if (v == LF[0] || mCrlfCount == 2) {
                ByteArray state = mReader->pop();
                String state_str = createString((const char *)state->toValue(),
                                                0, state->size() - mCrlfCount);
                mHeader->setResponseStatus(state_str->toBasicInt());
                mCrlfCount = 0;
                mStatus = ContentKey;
            } else if (v == 0x20) { // ' '
                ByteArray state = mReader->pop();
                //String state_str = createString((const char *)state->toValue(),
                //                                0, state->size() - 1);
                String state_str = state->toString();
                int status = state_str->toBasicInt();
                mHeader->setResponseStatus(status);
                mStatus = Reason;
            }
            continue;
        }

        case Url: {
            if (v == 0x20) { // ' '
                ByteArray urlcontent = mReader->pop();
                String url_str = urlcontent->toString()->subString(0,urlcontent->size() - 1);
                    //createString((const char *)urlcontent->toValue(),0,
                    //             urlcontent->size() - 1);
                printf("parse url is %s \n",url_str->toChars());
                HttpUrl url = createHttpUrl(url_str);
                mHeader->setUrl(url);
                mStatus = Version;
            }
            continue;
        }

        case Reason: {
            if (v == CRLF[mCrlfCount]) {
                mCrlfCount++;
            } else if (v == LF[0]) {
                mCrlfCount = 1;
            } else {
                mCrlfCount = 0;
            }

            if (v == LF[0] || mCrlfCount == 2) {
                ByteArray reason = mReader->pop();
                if (reason->size() == mCrlfCount) {
                    mHeader->setResponseReason(createString(""));
                } else {
                    mHeader->setResponseReason(
                        createString((const char *)reason->toString()->toChars(), 0,
                                     reason->size() - mCrlfCount));
                }
                mCrlfCount = 0;
                mStatus = ContentKey;
            }
            continue;
        }

        case Version: {
            if (v == CRLF[mCrlfCount]) {
                mCrlfCount++;
            } else if (v == LF[0]) {
                mCrlfCount = 1;
            } else {
                mCrlfCount = 0;
            }

            if (v == LF[0] || mCrlfCount == 2) {
                ByteArray vercontent = mReader->pop();
                String verstring = vercontent->toString()->subString(0,vercontent->size() - mCrlfCount);
                //    createString((const char *)vercontent->toValue(), 0,
                //                 vercontent->size() - mCrlfCount);
                HttpVersion ver = createHttpVersion();
                ver->import(verstring);
                mHeader->setVersion(ver);
                mStatus = ContentKey;
                mCrlfCount = 0;
            }
            continue;
        }

        case ContentKey: {
            if (v == CRLF[mCrlfCount]) {
                mCrlfCount++;
            } else if (v == 0x3a) { //':'
                mCrlfCount = 0;
                ByteArray key = mReader->pop();

                //mKey = createString((const char *)key->toValue(), 0,
                //                    key->size() - 1)
                //           ->toLowerCase();
                mKey = key->toString()->subString(0,key->size() - 1);
                mStatus = ContentValue;
            } else if (v == LF[0]) {
                mCrlfCount = 1;
            } else {
                mCrlfCount = 0;
            }

            if (v == LF[0] || mCrlfCount == 2) {
                // we should check whether it is end
                ByteArray content = mReader->pop();
                if (content->size() == 2 || content->size() == 1) {
                    mStatus = Idle;
                    //update cache control
                    //mHeader->updateCacheControl();
                    return mHeader;
                } else {
                    // if prev content value contains '\r\n'
                    String value = mHeader->get(mKey);
                    const char *valuestr = (const char *)content->toValue();
                    int size = content->size();
                    int start = 0;
                    if (value->size() == 0) {
                        for (; start < size; start++) {
                            if (valuestr[start] == ' ' ||
                                valuestr[start] == '\t' ||
                                valuestr[start] == '\r' ||
                                valuestr[start] == '\n') {
                                continue;
                            }
                            break;
                        }
                    }

                    String appendValue = nullptr;
                    if ((content->size() - start) == mCrlfCount ||
                        start == content->size()) {
                        appendValue = createString("");
                    } else {
                        appendValue = content->toString()->subString(start,content->size() - mCrlfCount - start);
                            //createString(&valuestr[start], 0,
                            //             content->size() - mCrlfCount - start);
                    }

                    value = value->append(appendValue);
                    mHeader->set(mKey, value);
                    mCrlfCount = 0;
                }
            }
            continue;
        }

        case ContentValue: {
            if (v == CRLF[mCrlfCount]) {
                mCrlfCount++;
            } else if (v == LF[0]) {
                mCrlfCount = 1;
            } else {
                mCrlfCount = 0;
            }

            if (v == LF[0] || mCrlfCount == 2) {
                ByteArray value = mReader->pop();
                int start = 0;
                int size = value->size();
                const char *valuestr = (const char *)value->toValue();
                for (; start < size; start++) {
                    if (valuestr[start] == ' ' || valuestr[start] == '\t' ||
                        valuestr[start] == '\r' || valuestr[start] == '\n') {
                        continue;
                    }
                    break;
                }

                if ((value->size() - start) == mCrlfCount ||
                    start == value->size()) {
                    mValue = createString("");
                } else {
                    mValue = value->toString()->subString(start,value->size() - mCrlfCount - start);
                    //mValue = createString(&valuestr[start], 0,
                    //                      value->size() - mCrlfCount - start);
                }
                mCrlfCount = 0;
                mHeader->set(mKey, mValue);
                // may be we should parse value
                mStatus = ContentKey;
                mNextStatus = -1;
            }
            continue;
        }
        }
    }

    return nullptr;
}

} // namespace obotcha