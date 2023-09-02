#ifndef __OBOTCHA_MAPPED_FILE_INPUT_STREAM_HPP__
#define __OBOTCHA_MAPPED_FILE_INPUT_STREAM_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "MappedFile.hpp"

namespace obotcha {

DECLARE_CLASS(MappedFileInputStream) IMPLEMENTS(InputStream) {
public:
    explicit _MappedFileInputStream(MappedFile);
    long read(ByteArray) override;
    long read(ByteArray, uint64_t start) override;
    long read(ByteArray, uint64_t start,uint64_t length) override;
    ByteArray readAll() override;
    bool open() override;
    void close() final;
    ~_MappedFileInputStream() override;

private:
    MappedFile mFile;
};

}
#endif
