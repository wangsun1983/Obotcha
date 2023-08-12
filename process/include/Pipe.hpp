#ifndef __OBOTCHA_PIPE_HPP__
#define __OBOTCHA_PIPE_HPP__

#include <fcntl.h>

#include "Object.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Pipe) {

public:
    enum Type {
        Default = 0,
        CloseOnExec = O_CLOEXEC,
        Direct = O_DIRECT,
        NonBlock = O_NONBLOCK
    };

    enum Channel {
        ReadChannel = 0,
        WriteChannel
    };

    static const int kMaxBuffSize;

    _Pipe();
    explicit _Pipe(Type);

    ssize_t write(ByteArray data) const;
    ssize_t read(ByteArray buff) const;
    int closeReadChannel();
    int closeWriteChannel();
    int getReadChannel() const;
    int getWriteChannel() const;
    int getMaxSize();
    void close();
    ~_Pipe();

private:
    int pipeFd[2];
};

}
#endif
