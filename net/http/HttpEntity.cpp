#include "HttpEntity.hpp"

namespace obotcha {

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
    mChunk = HttpChunk::New(data);
}

void _HttpEntity::setChunk(File file) {
    mChunk = HttpChunk::New(file);
}

void _HttpEntity::setChunk(HttpChunk c) {
    mChunk = c;
}

HttpChunk _HttpEntity::getChunk() {
    return mChunk;
}

} // namespace obotcha
