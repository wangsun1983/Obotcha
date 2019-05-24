#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "FifoPipe.hpp"

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
        return -FifoPipeAlreadyCreate;
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
        return -FifoPipeNotCreate;
    }

    if(mType == FifoReadPipe) {
        return -FifoPipeWrongType;
    }

    if(data->size() > PIPE_BUF) {
        return -FifoPipeWriteOversize;
    }

    return write(fifoId, data->toValue(), data->size());
}

int _FifoPipe::readFrom(ByteArray buff) {
    if(!isCreated) {
        return -FifoPipeNotCreate;
    }

    if(mType == FifoWritePipe) {
        return -FifoPipeWrongType;
    }

    return read(fifoId, buff->toValue(), buff->size());
}

int _FifoPipe::release() {
    if(fifoId != -1) {
        close(fifoId);
        //unlink(mPipeName->toChars());
    }

    return 0;
}

int _FifoPipe::destroy() {
    if(fifoId != -1) {
        close(fifoId);
        unlink(mPipeName->toChars());
    }

    return 0;
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
