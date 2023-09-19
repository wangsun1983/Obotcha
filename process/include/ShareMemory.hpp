#ifndef __OBOTCHA_SHARE_MEMORY_HPP__
#define __OBOTCHA_SHARE_MEMORY_HPP__

#include <fcntl.h>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(ShareMemory) {
public:
    enum class Type {
        Read = O_RDONLY,
        WriteRead = O_RDWR,
    };

    _ShareMemory(String name,size_t size,Type type);
    int write(ByteArray);
    int write(int index,ByteArray);
    int write(int index,char v);
    int read(ByteArray) const;
    int read(int index,ByteArray) const;
    int read(int) const;
    void close();
    void clear();
    int getChannel() const;
    ~_ShareMemory() override;

private:
    static const int kRetryTimes;
    String mName;
    size_t mSize;
    int mShareMemoryFd = -128;
    char *mPtr;
    Type mType;
};

}
#endif
