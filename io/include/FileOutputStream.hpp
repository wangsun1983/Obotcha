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
    long write(char c) final;
    long write(ByteArray buff) final;
    long write(ByteArray buff,int start) final;
    long write(ByteArray buff,int start,int len) final;
    long writeString(String s);
    bool open() final;
    bool open(int type) final; //O_TRUNC or O_APPEND
    void close() final;
    void flush();
    ~_FileOutputStream()=default;

private:
    String mPath;
    FileDescriptor mFd;
    bool mIsFdImport;
};

}
#endif
