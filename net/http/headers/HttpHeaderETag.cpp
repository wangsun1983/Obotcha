#include "HttpHeaderETag.hpp"

namespace obotcha {

_HttpHeaderETag::_HttpHeaderETag(String content) {
    this->load(content);
}

void _HttpHeaderETag::load(String content) {
    if(content->startsWith("W/")) {
        content = content->subString(2,content->size()-2);    
        mWeakCheck = true;
    }
    
    mValue = content->replaceAll("\"","");
}

bool _HttpHeaderETag::isWeakCheck() {
    return mWeakCheck;
}

String _HttpHeaderETag::getValue() {
    return mValue;
}

void _HttpHeaderETag::setWeakCheck(bool weakcheck) {
    mWeakCheck = weakcheck;
}

void _HttpHeaderETag::setValue(String value) {
    mValue = value;
}

String _HttpHeaderETag::toString() {
    String etag = "";
    if(mWeakCheck) {
        etag = String::New("W/");
    }

    return etag->append("\"",mValue,"\"");
}

}

