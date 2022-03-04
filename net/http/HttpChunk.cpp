#include "HttpChunk.hpp"
#include "FileInputStream.hpp"
#include "IllegalArgumentException.hpp"
#include "HttpText.hpp"

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
    mIsFile = true;
}

_HttpChunk::_HttpChunk(ByteArray data) {
    mInput = createHttpChunkInputStream(data);
    mSize = data->size();
    mIsFile = false;
}

bool _HttpChunk::isFile() {
    return mIsFile;
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

void _HttpChunk::onCompose(composeCallBack callback) {
    //InputStream input = mInput;
    ByteArray data = createByteArray(1024*16);
    int start = 0;
    while (1) {
        long len = mInput->read(data);
        if(len <= 0) {
            break;
        }

        String chunkLength = createInteger(len)
                            ->toHexString()
                            ->append(st(HttpText)::CRLF);
        callback(chunkLength->toByteArray());
        data->quickShrink(len);
        callback(data);
        data->quickRestore();

        callback(st(HttpText)::CRLF->toByteArray());
    }

    String end = createString("0")->append(st(HttpText)::HttpEnd);
    callback(end->toByteArray());
}

} // namespace obotcha
