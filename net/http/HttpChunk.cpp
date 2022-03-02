#include "HttpChunk.hpp"
#include "FileInputStream.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

//--------------- HttpChunkInputStream ------------------//
_HttpChunkInputStream::_HttpChunkInputStream(ByteArray d) {
    data = d;
    index = 0;
}

long _HttpChunkInputStream::read(ByteArray d) {
    return read(d,0);
}

long _HttpChunkInputStream::read(ByteArray d, int start) {
    return read(d,start,d->size() - start);
}

long _HttpChunkInputStream::read(ByteArray d, int start,int length) {
    if(index == data->size()) {
        return 0;
    }
    
    long srcRestLength = data->size() - index;
    long destRestLength = d->size() - start;
    destRestLength = (destRestLength > length)?length:destRestLength;
    long size = (srcRestLength > destRestLength)?destRestLength:srcRestLength;
    
    d->fillFrom(&data->toValue()[index],start,size);
    index += size;
    return size;
}

ByteArray _HttpChunkInputStream::readAll() {
    return data;
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
