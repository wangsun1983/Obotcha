#include "Object.hpp"
#include "StrongPointer.hpp"

#include "AutoLock.hpp"
#include "HttpContentType.hpp"
#include "HttpHeaderContentParser.hpp"
#include "String.hpp"
#include "HttpMime.hpp"

namespace obotcha {

_HttpContentType::_HttpContentType() {
    mContentType = nullptr;
    mBoundary = nullptr;
    mCharset = nullptr;
}

_HttpContentType::_HttpContentType(String value) {
    mContentType = nullptr;
    mBoundary = nullptr;
    mCharset = nullptr;
    import(value);
}

void _HttpContentType::import(String value) {
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
        if (parameter == nullptr) {
            mContentType = directive;
        } else if (st(HttpMime)::CharSet->equalsIgnoreCase(directive)) {
            mCharset = parameter;
        } else if(st(HttpMime)::Boundary->equalsIgnoreCase(directive)) {
            mBoundary = parameter;
        }
    });
}

void _HttpContentType::setType(String value) { mContentType = value; }

void _HttpContentType::setCharSet(String value) { mCharset = value; }

void _HttpContentType::setBoundary(String value) {
    mBoundary = value;
}

String _HttpContentType::getType() { return mContentType; }

String _HttpContentType::getCharSet() { return mCharset; }

String _HttpContentType::getBoundary() { return mBoundary; }

String _HttpContentType::toString() {
    String result = mContentType;
    if (mCharset != nullptr) {
        result = result->append(";charset=", mCharset);
    }
    if (mBoundary != nullptr) {
        result = result->append(";boundary=", mBoundary);
    }
    return result;
}

} // namespace obotcha
