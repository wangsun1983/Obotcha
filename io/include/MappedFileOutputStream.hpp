#ifndef __OBOTCHA_MAPPED_FILE_OUTPUT_STREAM_HPP__
#define __OBOTCHA_MAPPED_FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "MappedFile.hpp"

namespace obotcha {

DECLARE_CLASS(MappedFileOutputStream) IMPLEMENTS(OutputStream){

public:
    explicit _MappedFileOutputStream(MappedFile);
    long write(char c) override;
    long write(ByteArray buff) override;
    long write(ByteArray buff,uint64_t start) override;
    long write(ByteArray buff,uint64_t start,uint64_t len) override;
    long writeString(String s);
    bool open(int options) override;
    bool open() override;
    void close() final;
    void flush() override;
    ~_MappedFileOutputStream() override;

private:
    MappedFile mFile;
};

}
#endif
