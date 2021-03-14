#include "HttpEntity.hpp"

namespace obotcha {

_HttpEntity::_HttpEntity() {
    mFormUrlEncodedMap = createArrayList<KeyValuePair<String,String>>();
}
    
void _HttpEntity::setMultiPart(HttpMultiPart part) {
    mMultiPart = part;
}

HttpMultiPart _HttpEntity::getMultiPart() {
    return mMultiPart;
}

ArrayList<KeyValuePair<String,String>> _HttpEntity::getEncodedKeyValues() {
    return mFormUrlEncodedMap;
}

void _HttpEntity::setEncodedKeyValues(ArrayList<KeyValuePair<String,String>> map) {
    mFormUrlEncodedMap = map;
}

ByteArray _HttpEntity::getContent() {
    return mContent;
}
    
void _HttpEntity::setContent(ByteArray data) {
    mContent = data;
}


}

