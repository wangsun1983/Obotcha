#include "HttpChunk.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

//--------------- HttpChunkInputStream ------------------//
_HttpChunkInputStream::_HttpChunkInputStream(ByteArray d) {
    data = d;
}

long _HttpChunkInputStream::read(ByteArray d) {
    if(index == d->size()) {
        return 0;
    }

    long restSize = data->size() - index;
    long len = (d->size() > restSize)?d->size():restSize;
    d->fillFrom(data->toValue(),index,len);
    index += len;
    return len;
}

long _HttpChunkInputStream::read(ByteArray d, int start) {
    if(index == d->size()) {
        return 0;
    }
    
    long restSize = data->size() - index;
    long len = (d->size() > restSize)?d->size():restSize;
    d->fillFrom(&data->toValue()[start],index,len);
    index += len;
    return len;
}

bool _HttpChunkInputStream::open() {
    //nothing
    return true;
}

void _HttpChunkInputStream::close() {
    data = nullptr;
}

//--------------- HttpChunk ------------------//
_HttpChunk::_HttpChunk(File file) {
    mInput = createFileInputStream(file);
    mSize = file->length();
}

_HttpChunk::_HttpChunk(ByteArray data) {
    mInput = createHttpChunkInputStream(data);
    mSize = data->size();
}

InputStream _HttpChunk::getInputStream() {
    mInput->open();
    return mInput;
}

long _HttpChunk::size() {
    return mSize;
}

_HttpChunk::~_HttpChunk() {
    mInput->close();
}

} // namespace obotcha
