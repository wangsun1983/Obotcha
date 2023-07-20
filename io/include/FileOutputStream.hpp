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
    long write(char c);
    long write(ByteArray buff);
    long write(ByteArray buff,int start);
    long write(ByteArray buff,int start,int len);
    long writeString(String s);
    bool open();
    bool open(int type); //O_TRUNC or O_APPEND
    void close();
    void flush();
    ~_FileOutputStream()=default;

private:
    String mPath;
    FileDescriptor mFd;
    bool mIsFdImport;
};

}
#endif
