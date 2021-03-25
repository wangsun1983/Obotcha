#include "HttpHeaderParser.hpp"
#include "HttpText.hpp"
#include "HttpMethodParser.hpp"
#include "HttpVersionParser.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r,int mode) {
    mReader = r;
    mHeader = createHttpHeader();
    mCrlfCount = 0;
    if(mode == Full) {
        mStatus = Idle;
    } else {
        mStatus = ContentKey;
    }
}

HttpHeader _HttpHeaderParser::doParse() {
    byte v = 0;
    const byte *CRLF = (const byte *)st(HttpText)::CRLF->toChars();
    while(mReader->readNext(v) != ByteRingArrayReadComplete) {
        switch(mStatus) {
            case Idle:{
                if(v == ' ') {
                    ByteArray method = mReader->pop();
                    String tag = method->toString()->trimAll();
                    int methodid = st(HttpMethodParser)::doParse(tag);
                    if(methodid != -1) {
                        mHeader->setMethod(methodid);
                        mStatus = Url;
                    } else {
                        //this may be a response
                        HttpVersion ver = st(HttpVersionParser)::doParse(tag);
                        if(ver != nullptr) {
                            mHeader->setVersion(ver);
                            mStatus = State;
                        } else {
                            //TODO
                        }
                    }
                    
                }
                continue;
            }

            case State:{
                if(v == ' ') {
                    ByteArray state = mReader->pop();
                    String state_str = createString((const char *)state->toValue(),0,state->size() - 1);
                    int status = state_str->toBasicInt();
                    mHeader->setResponseStatus(status);
                    mStatus = Reason;
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

            case Reason:{
                //printf("HttpHeaderParser reason,v is %x \n",v);
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                } else {
                    mCrlfCount = 0;
                }

                if(mCrlfCount == 2) {
                   ByteArray reason = mReader->pop();
                   mHeader->setResponseReason(createString((const char *)reason->toValue(),0,reason->size() -2));
                   mCrlfCount = 0;
                   mStatus = ContentKey;
                }
                continue;
            }

            case Version:{
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                } else {
                    mCrlfCount = 0;
                }

                if(mCrlfCount == 2) {
                    //printf("version 2\n");
                    ByteArray vercontent = mReader->pop();
                    String verstring = createString((const char *)vercontent->toValue(),0,vercontent->size() -2);
                    mHeader->setVersion(st(HttpVersionParser)::doParse(verstring));
                    mStatus = ContentKey;
                    mCrlfCount = 0;
                }
                continue;
            }

            case ContentKey: {
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                }else if(v == ':') {
                    mCrlfCount = 0;
                    ByteArray key = mReader->pop();
                    mKey = createString((const char *)key->toValue(),0,key->size() - 1)->toLowerCase();
                    mStatus = ContentValue;
                }

                if(mCrlfCount == 2) {
                    mReader->pop();
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
                    int start = 0;
                    int size = value->size();
                    const char* valuestr = (const char*)value->toValue();
                    for(;start < size;start++) {
                        if(valuestr[start] == ' ') {
                            continue;
                        }
                        break;
                    }
                    if((value->size() - start) == 2) {
                        mValue = createString("");
                    } else {
                        mValue = createString(&valuestr[start],0,value->size() - 2 - start);
                    }
                    if(parseParticularHeader(mKey,mValue) == -1) {
                        mHeader->setValue(mKey->toLowerCase(),mValue);
                    }
                    //may be we should parse value
                    mStatus = ContentKey;
                    mNextStatus = -1;
                }
                continue;
            }
        }
    }

    return nullptr;
}

int _HttpHeaderParser::parseParticularHeader(String key,String value) {
    const char *p = key->toChars();
    switch(p[0]) {
        case 'c': {
            if(key->equals(st(HttpHeader)::Cookie)) {
                mHeader->addCookie(createHttpCookie(value));
                return 0;
            } else if(key->equals(st(HttpHeader)::CacheControl)) {
                mHeader->setCacheControl(createHttpCacheControl(value));
                return 0;
            } else if(key->equals(st(HttpHeader)::ContentType)) {
                mHeader->setContentType(value);
                return 0;
            } else if(key->equals(st(HttpHeader)::ContentLength)) {
                mHeader->setContentLength(value->trimAll()->toBasicInt());
                return 0;
            } else if(key->equals(st(HttpHeader)::Connection)) {
                if(st(HttpHeader)::ConnectionClose->equals(value->trimAll())) {
                    mHeader->setConnected(false);
                    printf("i set close!!! \n");
                    return 0;
                }
            }
            break;
        }

        case 's': {
            if(key->equals(st(HttpHeader)::SetCookie)) {
                mHeader->addCookie(createHttpCookie(value));
                return 0;
            }
        }
    }
    return -1;
}

}