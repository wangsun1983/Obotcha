#include "Pipe.hpp"
#include "Error.hpp"

namespace obotcha {

_Pipe::_Pipe(PipeIoType type) {
    mIoType = type;
    pipeFd[WritePipe] = -1;
    pipeFd[ReadPipe] = -1;
}

_Pipe::_Pipe():_Pipe{PipeDefault} {

}

int _Pipe::init() {
    if(pipeFd[WritePipe] != -1 && pipeFd[ReadPipe] != -1) {
        return -AlreadyExists;
    }

    int result = -1;
    switch(mIoType) {
        case PipeDefault:
            result = pipe(pipeFd);
        break;

        case PipeCloseOnExec:
        case PipeDirect:
        case PipeNonBlock:
            result = pipe2(pipeFd,mIoType);
        break;
    }

    return result;
}

int _Pipe::writeTo(ByteArray data) {
    if(pipeFd[WritePipe] == -1) {
        return -NotCreate;
    }

    if(data->size() > PIPE_BUF) {
        return -OverSize;
    }

    return write(pipeFd[WritePipe],data->toValue(),data->size());
}

int  _Pipe::readFrom(ByteArray buff) {
    if(pipeFd[ReadPipe] == -1) {
        return -NotCreate;
    }
    int nbytes = read(pipeFd[ReadPipe],buff->toValue(),buff->size());
    return nbytes;
}

int _Pipe::closeReadPipe() {
    if(pipeFd[ReadPipe] == -1) {
        return -NotCreate;
    }
    int ret = close(pipeFd[ReadPipe]);
    pipeFd[ReadPipe] = -1;
    return ret;
}

int _Pipe::closeWritePipe() {
    if(pipeFd[WritePipe] == -1) {
        return -NotCreate;
    }
    int ret = close(pipeFd[WritePipe]);
    pipeFd[WritePipe] = -1;
    return ret;
}

int _Pipe::getReadPipe() {
    if(pipeFd[ReadPipe] == -1) {
        return -NotCreate;
    }
    return pipeFd[ReadPipe];
}

int _Pipe::getWritePipe() {
    if(pipeFd[WritePipe] == -1) {
        return -NotCreate;
    }
    return pipeFd[WritePipe];
}

int _Pipe::getMaxSize() {
    return PIPE_BUF;
}

void _Pipe::release() {
    closeWritePipe();
    closeReadPipe();
}

_Pipe::~_Pipe() {
   release();
}

}

