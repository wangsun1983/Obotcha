#include "HttpChunk.hpp"
#include "FileInputStream.hpp"
#include "IllegalArgumentException.hpp"
#include "HttpText.hpp"
#include "Inspect.hpp"

namespace obotcha {

//--------------- HttpChunkInputStream ------------------//
_HttpChunkInputStream::_HttpChunkInputStream(ByteArray data) {
    mChunkData = data;
    mIndex = 0;
}

long _HttpChunkInputStream::read(ByteArray data) {
    return read(data,0);
}

long _HttpChunkInputStream::read(ByteArray data, int start) {
    return read(data,start,data->size() - start);
}

long _HttpChunkInputStream::read(ByteArray data, int start,int length) {
    Inspect(mIndex == mChunkData->size(),0);

    long size = std::min(mChunkData->size() - mIndex, // src rest length
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
_HttpChunk::_HttpChunk(File file) {
    mInput = createFileInputStream(file);
    mInput->open();
    mSize = file->length();
    mIsFile = true;
}

_HttpChunk::_HttpChunk(ByteArray data) {
    mInput = createHttpChunkInputStream(data);
    mInput->open();
    mSize = data->size();
    mIsFile = false;
}

bool _HttpChunk::isFile() {
    return mIsFile;
}

InputStream _HttpChunk::getInputStream() {
    return mInput;
}

long _HttpChunk::size() {
    return mSize;
}

_HttpChunk::~_HttpChunk() {
    mInput->close();
}

void _HttpChunk::onCompose(composeCallBack write) {
    ByteArray data = createByteArray(1024*16);
    long len = 0;
    while ((len = mInput->read(data)) > 0) {
        String chunkLength = createInteger(len)
                            ->toHexString()
                            ->append(st(HttpText)::CRLF);
        write(chunkLength->toByteArray());
        data->quickShrink(len);
        write(data);
        data->quickRestore();

        write(st(HttpText)::CRLF->toByteArray());
    }

    write(st(HttpText)::HttpChunkEnd->toByteArray());
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
