#ifndef __OBOTCHA_HTTP_CHUNK_HPP__
#define __OBOTCHA_HTTP_CHUNK_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "HttpHeader.hpp"
#include "HttpText.hpp"

namespace obotcha {

DECLARE_CLASS(HttpChunkInputStream) IMPLEMENTS(InputStream){
public:
    explicit _HttpChunkInputStream(ByteArray);
    long read(ByteArray) override;
    long read(ByteArray, uint64_t start) override;
    long read(ByteArray, uint64_t start,uint64_t length) override;
    ByteArray readAll() override;
    bool open() override;
    void close() override;

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

    ~_HttpChunk() override;

private:
    InputStream mInput;
    long mSize;
    bool mIsFile;

    HttpHeader mTrailingHeader;

    /**
     * ComposeCallback type is :void(ByteArray)>;
     **/
    template<typename ComposeCallback>
    void onCompose(ComposeCallback OnData) {
        ByteArray data = ByteArray::New(1024*16);
        long len = 0;
        while ((len = mInput->read(data)) > 0) {
            String chunkLength = Integer::New(len)
                                ->toHexString()
                                ->append(st(HttpText)::CRLF);
            OnData(chunkLength->toByteArray());
            data->quickShrink(len);
            OnData(data);
            data->quickRestore();

            OnData(st(HttpText)::CRLF->toByteArray());
        }
        OnData(st(HttpText)::HttpChunkEnd->toByteArray());
    }
};

} // namespace obotcha
#endif
