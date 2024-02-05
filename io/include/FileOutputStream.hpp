#ifndef __OBOTCHA_FILE_OUTPUT_STREAM_HPP__
#define __OBOTCHA_FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"

#include "String.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(FileOutputStream) IMPLEMENTS(OutputStream){

public:
    explicit _FileOutputStream(File file);
    explicit _FileOutputStream(String path);
    explicit _FileOutputStream(const char *);
    explicit _FileOutputStream(FileDescriptor fd);
    long write(char c) override;
    long write(ByteArray buff) override;
    long write(ByteArray buff,uint64_t start) override;
    long write(ByteArray buff,uint64_t start,uint64_t len) override;
    long writeString(String s);
    bool open() override;
    bool open(int options) override; //O_TRUNC or O_APPEND
    void close() override;
    void flush() override;
    ~_FileOutputStream() override = default;

private:
    String mPath;
    FileDescriptor mFd;
};

}
#endif
