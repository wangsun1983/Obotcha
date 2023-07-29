#ifndef __OBOTCHA_MAPPED_FILE_HPP__
#define __OBOTCHA_MAPPED_FILE_HPP__

#include <unistd.h>
#include <sys/mman.h>

#include "Object.hpp"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "Byte.hpp"
#include "InputStream.hpp"
#include "OutputStream.hpp"

namespace obotcha {

class _MappedFileOutputStream;
class _MappedFileInputStream;

DECLARE_CLASS(MappedFile) {
public:
    friend class _MappedFileOutputStream;
    friend class _MappedFileInputStream;

    enum Prot{
        Read = PROT_READ,
        Write = PROT_WRITE
    };

    enum Flag {
        Shared = MAP_SHARED,
        Private = MAP_PRIVATE
    };

    explicit _MappedFile(String path,long size = 0,int type = PROT_READ|PROT_WRITE,int flag = MAP_SHARED);

    InputStream getInputStream();
    OutputStream getOutputStream();
    long size() const;
    ByteArray read(int start,int length);
    ~_MappedFile() override;

private:
    byte *mapPtr;
    long mSize;
    void sync();
};

} // namespace obotcha
#endif
