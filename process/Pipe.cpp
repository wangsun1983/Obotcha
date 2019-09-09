#include "Pipe.hpp"
#include "Error.hpp"

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
    if(isCreated) {
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
    
    isCreated = (result != -1);
    return result;
}

int _Pipe::writeTo(ByteArray data) {
    if(!isCreated) {
        return -NotCreate;
    }

    if(data->size() > PIPE_BUF) {
        return -OverSize;
    }
    printf("wirteTo content is %s \n",data->toValue());

    return write(pipeFd[WritePipe],data->toValue(),data->size());
}

int  _Pipe::readFrom(ByteArray buff) {
    if(!isCreated) {
        return -NotCreate;
    }

    int nbytes = read(pipeFd[ReadPipe],buff->toValue(),buff->size());
    return nbytes;
}

int _Pipe::closeReadPipe() {
    if(!isCreated) {
        return -NotCreate;
    }
    return close(pipeFd[ReadPipe]);
}

int _Pipe::closeWritePipe() {
    if(!isCreated) {
        return -NotCreate;
    }
    return close(pipeFd[WritePipe]);
}

int _Pipe::getReadPipe() {
    if(!isCreated) {
        return -NotCreate;
    }
    return pipeFd[ReadPipe];
}

int _Pipe::getWritePipe() {
    if(!isCreated) {
        return -NotCreate;
    }
    return pipeFd[WritePipe];
}

int _Pipe::getMaxSize() {
    return PIPE_BUF;
}

void _Pipe::release() {
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

