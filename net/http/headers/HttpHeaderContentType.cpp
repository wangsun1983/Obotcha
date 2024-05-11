#include "HttpHeaderContentType.hpp"
#include "HttpHeaderContentParser.hpp"
#include "String.hpp"
#include "HttpMime.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderContentType::_HttpHeaderContentType(String value) {
    load(value);
}

void _HttpHeaderContentType::load(String value) {
    st(HttpHeaderContentParser)::load(value,[this](String directive,String parameter) {
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
    StringBuffer result = StringBuffer::New();
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
