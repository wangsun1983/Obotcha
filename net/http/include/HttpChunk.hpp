#ifndef __OBOTCHA_HTTP_CHUNK_HPP__
#define __OBOTCHA_HTTP_CHUNK_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_CLASS(HttpChunkInputStream) IMPLEMENTS(InputStream){
public:
    explicit _HttpChunkInputStream(ByteArray);
    long read(ByteArray);
    long read(ByteArray, int start);
    long read(ByteArray, int start,int length);
    ByteArray readAll();
    bool open();
    void close();

private:
    ByteArray mChunkData;
    int mIndex = 0;
};

DECLARE_CLASS(HttpChunk) {
public:
    friend class _HttpPacketWriterImpl;
    explicit _HttpChunk(File);
    explicit _HttpChunk(ByteArray);

    InputStream getInputStream();
    ByteArray getData();
    long size() const;
    bool isFile() const;

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
