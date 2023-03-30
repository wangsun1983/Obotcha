#include "Object.hpp"
#include "StrongPointer.hpp"

#include "AutoLock.hpp"
#include "HttpHeaderContentType.hpp"
#include "HttpHeaderContentParser.hpp"
#include "String.hpp"
#include "HttpMime.hpp"
#include "StringBuffer.hpp"
#include "HttpText.hpp"

namespace obotcha {

_HttpHeaderContentType::_HttpHeaderContentType() {
    mContentType = nullptr;
    mBoundary = nullptr;
    mCharset = nullptr;
}

_HttpHeaderContentType::_HttpHeaderContentType(String value) {
    mContentType = nullptr;
    mBoundary = nullptr;
    mCharset = nullptr;
    import(value);
}

void _HttpHeaderContentType::import(String value) {
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
        if (parameter == nullptr) {
            mContentType = directive;
        } else if (st(HttpMime)::CharSet->equalsIgnoreCase(directive)) {
            mCharset = parameter;
        } else if(st(HttpMime)::Boundary->equalsIgnoreCase(directive)) {
            //we should remove BoundarySeperator
            mBoundary = parameter;
        }
    });
}

void _HttpHeaderContentType::setType(String value) { 
    mContentType = value; 
}

void _HttpHeaderContentType::setCharSet(String value) { 
    mCharset = value; 
}

void _HttpHeaderContentType::setBoundary(String value) {
    mBoundary = value;
}

String _HttpHeaderContentType::getType() { 
    return mContentType; 
}

String _HttpHeaderContentType::getCharSet() { 
    return mCharset; 
}

String _HttpHeaderContentType::getBoundary() { 
    return mBoundary; 
}

String _HttpHeaderContentType::toString() {
    StringBuffer result = createStringBuffer();
    result->append(mContentType);
    if (mCharset != nullptr) {
        result = result->append(";charset=", mCharset);
    }
    if (mBoundary != nullptr) {
        result = result->append(";boundary=",mBoundary);
    }
    return result->toString();
}

} // namespace obotcha
