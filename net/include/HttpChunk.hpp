#ifndef __OBOTCHA_HTTP_CHUNK_HPP__
#define __OBOTCHA_HTTP_CHUNK_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "File.hpp"
#include "InputStream.hpp"

namespace obotcha {

DECLARE_CLASS(HttpChunkInputStream) IMPLEMENTS(InputStream){
public:
    _HttpChunkInputStream(ByteArray);
    long read(ByteArray);
    long read(ByteArray, int start);
    bool open();
    void close();

private:
    ByteArray data;
    int index;
};

DECLARE_CLASS(HttpChunk) {
public:
    _HttpChunk(File);
    _HttpChunk(ByteArray);

    InputStream getInputStream();
    long size();
    ~_HttpChunk();

private:
    InputStream mInput;
    long mSize;
};

} // namespace obotcha
#endif