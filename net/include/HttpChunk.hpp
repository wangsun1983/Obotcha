#ifndef __OBOTCHA_HTTP_CHUNK_HPP__
#define __OBOTCHA_HTTP_CHUNK_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_CLASS(HttpChunkInputStream) IMPLEMENTS(InputStream){
public:
    _HttpChunkInputStream(ByteArray);
    long read(ByteArray);
    long read(ByteArray, int start);
    long read(ByteArray, int start,int length);
    ByteArray readAll();
    bool open();
    void close();

private:
    ByteArray data;
    int index;
};

DECLARE_CLASS(HttpChunk) {
public:
    friend class _HttpPacketWriterImpl;
    _HttpChunk(File);
    _HttpChunk(ByteArray);

    InputStream getInputStream();
    ByteArray getData();
    long size();
    bool isFile();

    HttpHeader getTrailingHeader();
    void setTrailingHeader(HttpHeader);

    ~_HttpChunk();

private:
    InputStream mInput;
    long mSize;
    bool mIsFile;

    HttpHeader mTrailingHeader;

    using composeCallBack = std::function<void(ByteArray)>;
    void onCompose(composeCallBack callback);
};

} // namespace obotcha
#endif
