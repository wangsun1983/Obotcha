#include "HttpEntity.hpp"

namespace obotcha {

_HttpEntity::_HttpEntity() {
    //mFormUrlEncodedMap = createArrayList<Pair<String, String>>();
    //mChunks != nullptr;
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

void _HttpEntity::setChunk(ByteArray data) {
    mChunk = createHttpChunk(data);
}

void _HttpEntity::setChunk(File file) {
    mChunk = createHttpChunk(file);
}

HttpChunk _HttpEntity::getChunk() {
    return mChunk;
}

// String _HttpEntity::getUpgradeContent() { 
//     return mUpgrade; 
// }

// void _HttpEntity::setUpgradeContent(String u) { 
//     mUpgrade = u; 
// }

//File _HttpEntity::getChunkFile() { 
//    return mChunkFile;
//}

//void _HttpEntity::setChunkFile(File f) { 
//    mChunkFile = f;
//}

//ArrayList<ByteArray> _HttpEntity::getChunks() {
//    return mChunks;
//}

//void _HttpEntity::setChunks(ArrayList<ByteArray> data) {
//    mChunks = data;
//}

} // namespace obotcha
