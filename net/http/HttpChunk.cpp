#include "HttpChunk.hpp"
#include "FileInputStream.hpp"
#include "IllegalArgumentException.hpp"
#include "Inspect.hpp"

namespace obotcha {

//--------------- HttpChunkInputStream ------------------//
_HttpChunkInputStream::_HttpChunkInputStream(ByteArray data):mChunkData(data) {
}

long _HttpChunkInputStream::read(ByteArray data) {
    return read(data,0);
}

long _HttpChunkInputStream::read(ByteArray data, uint64_t start) {
    return read(data,start,data->size() - start);
}

long _HttpChunkInputStream::read(ByteArray data, uint64_t start,uint64_t length) {
    Inspect(mIndex == mChunkData->size(),0)

    auto size = std::min(mChunkData->size() - mIndex, // src rest length
                         std::min(data->size() - start,length));
    
    data->fillFrom(&mChunkData->toValue()[mIndex],start,size);
    mIndex += size;
    return size;
}

ByteArray _HttpChunkInputStream::readAll() {
    return mChunkData;
}

bool _HttpChunkInputStream::open() {
    //nothing
    return true;
}

void _HttpChunkInputStream::close() {
    mChunkData = nullptr;
}

//--------------- HttpChunk ------------------//
_HttpChunk::_HttpChunk(File file) :mIsFile(true) {
    mInput = createFileInputStream(file);
    mInput->open();
    mSize = file->length();
}

_HttpChunk::_HttpChunk(ByteArray data):mIsFile(false) {
    mInput = createHttpChunkInputStream(data);
    mInput->open();
    mSize = data->size();
}

bool _HttpChunk::isFile() const {
    return mIsFile;
}

InputStream _HttpChunk::getInputStream() {
    return mInput;
}

long _HttpChunk::size() const {
    return mSize;
}

_HttpChunk::~_HttpChunk() {
    mInput->close();
}

ByteArray _HttpChunk::getData() {
    return (mInput != nullptr)? mInput->readAll():nullptr;
}

HttpHeader _HttpChunk::getTrailingHeader() {
    return mTrailingHeader;
}

void _HttpChunk::setTrailingHeader(HttpHeader h) {
    mTrailingHeader = h;
}

} // namespace obotcha
