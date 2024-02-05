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

    enum class Flag {
        Shared = MAP_SHARED,
        Private = MAP_PRIVATE
    };

    explicit _MappedFile(String path,
                         uint64_t size = 0,
                         Flag flag = Flag::Shared);

    InputStream getInputStream();
    OutputStream getOutputStream();
    uint64_t size() const;
    ~_MappedFile() override;

private:
    byte *mapPtr;
    uint64_t mSize;
    void sync();
};

} // namespace obotcha
#endif
