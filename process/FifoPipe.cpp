#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "FifoPipe.hpp"
#include "Error.hpp"

namespace obotcha {

_FifoPipe::_FifoPipe(String name,int type,int filemode) {
    mPipeName = name;
    mType = type;
    isCreated = false;
    mMode = filemode;
}

_FifoPipe::_FifoPipe(String name,int type) {
    mPipeName = name;
    mType = type;
    isCreated = false;
    mMode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
}

int _FifoPipe::init() {
    if(isCreated) {
        return -AlreadyExists;
    }

    if(access(mPipeName->toChars(),F_OK) != 0){
        int err = mkfifo(mPipeName->toChars(),S_IFIFO|mMode);
        if(err < 0){
            return err;
        }
    }

    switch(mType) {
        case FifoWritePipe:
            fifoId = open(mPipeName->toChars(),O_WRONLY);
        break;

        case FifoReadPipe:
            fifoId = open(mPipeName->toChars(),O_RDONLY);
        break;
    }

    isCreated = (fifoId != -1);
    return fifoId;
}

int _FifoPipe::writeTo(ByteArray data) {
    if(!isCreated){
        return -NotCreate;
    }

    if(mType == FifoReadPipe) {
        return -InvalidParam;
    }

    if(data->size() > PIPE_BUF) {
        return -OverSize;
    }

    return write(fifoId, data->toValue(), data->size());
}

int _FifoPipe::readFrom(ByteArray buff) {
    if(!isCreated) {
        return -NotCreate;
    }

    if(mType == FifoWritePipe) {
        return -InvalidParam;
    }

    return read(fifoId, buff->toValue(), buff->size());
}

void _FifoPipe::release() {
    if(fifoId != -1) {
        close(fifoId);
        //unlink(mPipeName->toChars());
    }
}

void _FifoPipe::destroy() {
    if(fifoId != -1) {
        close(fifoId);
        unlink(mPipeName->toChars());
    }
}

void _FifoPipe::clean() {
    unlink(mPipeName->toChars());
}

int _FifoPipe::getMaxSize() {
    return PIPE_BUF;
}

_FifoPipe::~_FifoPipe() {
    if(fifoId != -1) {
        close(fifoId);
        //unlink(mPipeName->toChars());
    }
}

}
