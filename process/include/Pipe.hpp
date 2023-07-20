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

    int write(ByteArray data);
    int read(ByteArray buff);
    int closeReadChannel();
    int closeWriteChannel();
    int getReadChannel();
    int getWriteChannel();
    int getMaxSize();
    void close();
    ~_Pipe();

private:
    int pipeFd[2];
};

}
#endif
