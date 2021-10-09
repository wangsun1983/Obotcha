#include "HttpHeaderLink.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderLink::_HttpHeaderLink() {
    mUrl = nullptr;
    mProps = createHashMap<String,String>();
}

_HttpHeaderLink::_HttpHeaderLink(String v):_HttpHeaderLink() {
    import(v);
}

void _HttpHeaderLink::setUrl(String s) {
    mUrl = s;
}

void _HttpHeaderLink::setProp(String k,String v) {
    mProps->put(k,v);
}

String _HttpHeaderLink::getUrl() {
    return mUrl;
}

String _HttpHeaderLink::getProp(String k) {
    return mProps->get(k);
}

void _HttpHeaderLink::removeProp(String k) {
    return mProps->remove(k);
}

void _HttpHeaderLink::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            mUrl = directive->trimAll()->replaceAll("<","")->replaceAll(">","");
        } else if(directive != nullptr) {
            mProps->put(directive,parameter);
        }
    });
}

String _HttpHeaderLink::toString() {
    //TODO
}

} // namespace obotcha