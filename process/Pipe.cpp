#include "Pipe.hpp"

namespace obotcha {

_Pipe::_Pipe(PipeIoType type) {
    mIoType = type;
    isCreated = false;

}

_Pipe::_Pipe() {
    mIoType = PipeDefault;
    isCreated = false;
}

int _Pipe::init() {
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
    
    isCreated = (result != -1);
    return result;
}

int _Pipe::writeTo(ByteArray data) {
    if(!isCreated) {
        return PipeNotInit;
    }

    if(data->size() > PIPE_BUF) {
        return PipeWriteOversize;
    }

    return write(pipeFd[WritePipe],data->toValue(),data->size());
}

int  _Pipe::readFrom(ByteArray buff) {
    if(!isCreated) {
        return PipeNotInit;
    }

    int nbytes = read(pipeFd[ReadPipe],buff->toValue(),buff->size());
    return nbytes;
}

int _Pipe::closePipe(PipeType type) {
    if(!isCreated) {
        return PipeNotInit;
    }
    return close(pipeFd[type]);
}

int _Pipe::getMaxSize() {
    return PIPE_BUF;
}

void _Pipe::destroy() {
    if(isCreated) {
        close(pipeFd[ReadPipe]);
        close(pipeFd[WritePipe]);    
    }
}

_Pipe::~_Pipe() {
    if(isCreated) {
        close(pipeFd[ReadPipe]);
        close(pipeFd[WritePipe]);    
    }
}

}

