#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "FifoPipe.hpp"

namespace obotcha {

_FifoPipe::_FifoPipe(String name,int type) {
    mPipeName = name;
    mType = type;
    isCreated = false;
}

bool _FifoPipe::init() {
    if(access(mPipeName->toChars(),F_OK) != 0){
        int err = mkfifo(mPipeName->toChars(),S_IFIFO|0666);
        if(err != 0){
            return false;
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
    return isCreated;
}

bool _FifoPipe::writeTo(ByteArray data) {
    if(!isCreated || mType == FifoReadPipe) {
        return false;
    }

    int result = write(fifoId, data->toValue(), data->size());

    return (result != -1);
}

int _FifoPipe::readFrom(ByteArray buff) {
    if(!isCreated || mType == FifoWritePipe) {
        return false;
    }
    int res = read(fifoId, buff->toValue(), buff->size());
    return res;
}

_FifoPipe::~_FifoPipe() {
    if(fifoId != -1) {
        close(fifoId);
        unlink(mPipeName->toChars());
    }
}

}