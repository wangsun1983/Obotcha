#include "HttpEntity.hpp"

namespace obotcha {

_HttpEntity::_HttpEntity() {
    mFormUrlEncodedMap = createArrayList<KeyValuePair<String, String>>();
}

void _HttpEntity::setMultiPart(HttpMultiPart part) { 
    mMultiPart = part; 
}

HttpMultiPart _HttpEntity::getMultiPart() { 
    return mMultiPart; 
}

ByteArray _HttpEntity::getContent() { 
    return mContent; 
}

void _HttpEntity::setContent(ByteArray data) { 
    mContent = data; 
}

String _HttpEntity::getUpgrade() { 
    return mUpgrade; 
}

void _HttpEntity::setUpgrade(String u) { 
    mUpgrade = u; 
}

File _HttpEntity::getChunkFile() { 
    return mChunkFile;
}

void _HttpEntity::setChunkFile(File f) { 
    mChunkFile = f;
}

} // namespace obotcha
