#include "HttpHeaderParser.hpp"
#include "HttpText.hpp"
#include "HttpMethodParser.hpp"
#include "HttpVersionParser.hpp"
#include "HttpUrlParser.hpp"

namespace obotcha {

_HttpHeaderParser::_HttpHeaderParser(ByteRingArrayReader r) {
    mReader = r;
    mHeader = createHttpHeader();
    mCrlfCount = 0;
    mStatus = Idle;
    //mPrevKey = nullptr;
}

void _HttpHeaderParser::changeToParseKeyValue() {
    mStatus = ContentKey;
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
                    printf("method id is %d,tag is %s \n",methodid,tag->toChars());
                    if(methodid != -1) {
                        mHeader->setMethod(methodid);
                        mStatus = Url;
                    } else {
                        //this may be a response
                        mHeader->setType(st(HttpHeader)::Response);
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
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                } else {
                    mCrlfCount = 0;
                }

                if(mCrlfCount == 2) { 
                    ByteArray state = mReader->pop();
                    String state_str = createString((const char *)state->toValue(),0,state->size() -2);
                    mHeader->setResponseStatus(state_str->toBasicInt());
                    mCrlfCount = 0;
                    mStatus = ContentKey;
                }else if(v == ' ') {
                    ByteArray state = mReader->pop();
                    String state_str = createString((const char *)state->toValue(),0,state->size() - 1);
                    int status = state_str->toBasicInt();
                    mHeader->setResponseStatus(status);
                    mStatus = Reason;
                }
                continue;
            }

            case Url:{
                //printf("url \n");
                if(v == ' ') {
                    ByteArray urlcontent = mReader->pop();
                    String url_str = createString((const char *)urlcontent->toValue(),0,urlcontent->size() - 1);
                    HttpUrl url = st(HttpUrlParser)::parseUrl(url_str);
                    mHeader->setUrl(url);
                    mStatus = Version;
                }
                continue;
            }

            case Reason:{
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
                    //printf("version \n");
                    ByteArray vercontent = mReader->pop();
                    String verstring = createString((const char *)vercontent->toValue(),0,vercontent->size() -2);
                    mHeader->setVersion(st(HttpVersionParser)::doParse(verstring));
                    mStatus = ContentKey;
                    mCrlfCount = 0;
                }
                continue;
            }

            case ContentKey: {
                //printf("Content key is %x,mCrlfCount is %d \n",v,mCrlfCount);
                if(v == CRLF[mCrlfCount]) {
                    mCrlfCount++;
                }else if(v == ':') {
                    mCrlfCount = 0;
                    ByteArray key = mReader->pop();
                    
                    mKey = createString((const char *)key->toValue(),0,key->size() - 1)->toLowerCase();
                    mStatus = ContentValue;
                } else {
                    mCrlfCount = 0;
                }

                if(mCrlfCount == 2) {
                    //we should check whether it is end
                    ByteArray content = mReader->pop();
                    //printf("content size is %d \n",content->size());
                    if(content->size() == 2) {
                        mStatus = Idle;
                        return mHeader;
                    } else {
                        //if prev content value contains '\r\n'
                        String value = mHeader->getValue(mKey);
                        const char* valuestr = (const char*)content->toValue();
                        int size = content->size();
                        int start = 0;
                        if(value->size() == 0) {
                            for(;start < size;start++) {
                                if(valuestr[start] == ' '||
                                valuestr[start] == '\t'||
                                valuestr[start] == '\r' ||
                                valuestr[start] == '\n') {
                                    continue;
                                }
                                break;
                            }
                        }

                        String appendValue = nullptr;
                        if((content->size() - start) == 2 || start == content->size()) {
                            appendValue = createString("");
                        } else {
                            appendValue = createString(&valuestr[start],0,content->size() - 2 - start);
                        }

                        value = value->append(appendValue);
                        mHeader->setValue(mKey,value);
                        //printf("key is %s,value is%s \n",mKey->toChars(),value->toChars());
                        mCrlfCount = 0;
                    }
                    
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
                        if(valuestr[start] == ' '||
                           valuestr[start] == '\t'||
                           valuestr[start] == '\r' ||
                           valuestr[start] == '\n') {
                            continue;
                        }
                        break;
                    }
                    
                    if((value->size() - start) == 2 || start == value->size()) {
                        mValue = createString("");
                    } else {
                        mValue = createString(&valuestr[start],0,value->size() - 2 - start);
                    }
                    parseParticularHeader(mKey,mValue);
                    mHeader->setValue(mKey,mValue);
                    //printf("start is %d,size is %d \n",start,size);
                    //printf("key is %s,value is%s \n",mKey->toChars(),mValue->toChars());
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