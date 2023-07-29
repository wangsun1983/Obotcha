/**
 * @file FileInputStream.cpp
 * @brief FileInputStream obtains input bytes from a file in a file system.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#ifndef __OBOTCHA_FILE_INPUT_STREAM_HPP__
#define __OBOTCHA_FILE_INPUT_STREAM_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(FileInputStream) IMPLEMENTS(InputStream) {
public:

    explicit _FileInputStream(File f);
    
    explicit _FileInputStream(String path);

    explicit _FileInputStream(const char *);

    explicit _FileInputStream(FileDescriptor fd);

    ByteArray read(int size = 1024*4);
    long read(ByteArray) override;
    long read(ByteArray,int start) override;
    long read(ByteArray,int start,int length) override;

    long seekTo(int index);
    
    ByteArray readAll() override;

    bool open() final;
    void close() final;

    void reset();

    ~_FileInputStream() override;

private:
    String mPath;
    FileDescriptor mFd;
    bool mIsFdImport;
};

}
#endif
