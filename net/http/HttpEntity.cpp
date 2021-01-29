#include "HttpEntity.hpp"

namespace obotcha {

_HttpEntity::_HttpEntity() {
    mFormUrlEncodedMap = createHashMap<String,String>();
}
    
void _HttpEntity::setMultiPart(HttpMultiPart part) {
    mMultiPart = part;
}

HttpMultiPart _HttpEntity::getMultiPart() {
    return mMultiPart;
}

HashMap<String,String> _HttpEntity::getEncodedKeyValues() {
    return mFormUrlEncodedMap;
}

void _HttpEntity::setEncodedKeyValues(HashMap<String,String> map) {
    mFormUrlEncodedMap = map;
}

ByteArray _HttpEntity::getContent() {
    return mContent;
}
    
void _HttpEntity::setContent(ByteArray data) {
    mContent = data;
}


}

