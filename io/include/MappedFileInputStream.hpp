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
    long read(ByteArray) final;
    long read(ByteArray, int start) final;
    long read(ByteArray, int start,int length) final;
    ByteArray readAll();
    bool open() final;
    void close() final;
    ~_MappedFileInputStream();

private:
    MappedFile mFile;
};

}
#endif
