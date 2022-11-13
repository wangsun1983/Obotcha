#ifndef __OBOTCHA_PIPE_HPP__
#define __OBOTCHA_PIPE_HPP__

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <fstream>
#include <limits.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"

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

    _Pipe();

    _Pipe(Type);

    int write(ByteArray data);

    int read(ByteArray buff);

    int closeReadChannel();

    int closeWriteChannel();

    int getReadChannel();

    int getWriteChannel();

    int getMaxSize();

    void close();

    ~_Pipe();

    static const int MaxBuffSize;

private:

    int pipeFd[2];
};

}
#endif
