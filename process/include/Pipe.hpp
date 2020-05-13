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

enum PipeIoType {
    PipeDefault = 0,
    PipeCloseOnExec = O_CLOEXEC,
    PipeDirect = O_DIRECT,
    PipeNonBlock = O_NONBLOCK
};

enum PipeType {
    ReadPipe = 0,
    WritePipe
};

DECLARE_SIMPLE_CLASS(Pipe) {
public:
    _Pipe();

    _Pipe(PipeIoType);

    int init();

    int writeTo(ByteArray data);

    int readFrom(ByteArray buff);

    int closeReadPipe();

    int closeWritePipe();

    int getReadPipe();

    int getWritePipe();

    int getMaxSize();

    void release();

    ~_Pipe();

private:

    int pipeFd[2];

    PipeIoType mIoType;

    //bool isCreated;
};

}
#endif
