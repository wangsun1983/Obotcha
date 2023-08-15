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
    long write(ByteArray buff,int start) override;
    long write(ByteArray buff,int start,int len) override;
    long writeString(String s);
    bool open() override;
    bool open(st(IO)::FileControlFlags type) override; //O_TRUNC or O_APPEND
    void close() override;
    void flush() override;
    ~_FileOutputStream() override = default;

private:
    String mPath;
    FileDescriptor mFd;
    bool mIsFdImport;
};

}
#endif
