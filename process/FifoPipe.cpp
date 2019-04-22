#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "FifoPipe.hpp"

namespace obotcha {

_FifoPipe::_FifoPipe(String name,int type) {
    mPipeName = name;
    mType = type;
    isCreated = false;
}

bool _FifoPipe::init() {
    String tempFolder = "/tmp/";
    String fifoPath = tempFolder->append(mPipeName);

    if(access(fifoPath->toChars(),F_OK) != 0){
        int err = mkfifo(fifoPath->toChars(),0777);
        if(err != 0){
            return false;
        }
    }

    int fifoId = -1;

    switch(mType) {
        case WritePipe:
            fifoId = open(fifoPath->toChars(),O_WRONLY);
        break;

        case ReadPipe:
            fifoId = open(fifoPath->toChars(),O_WRONLY);
        break;
    }

    isCreated = (fifoId != -1);
    return isCreated;
}

bool _FifoPipe::writeTo(int type,ByteArray data) {
    if(!isCreated || mType == ReadPipe) {
        return false;
    }

    int result = write(fifoId, data->toValue(), data->size());

    return (result != -1);
}

int _FifoPipe::readFrom(int type,ByteArray buff) {
    if(!isCreated || mType == WritePipe) {
        return false;
    }

    int res = read(fifoId, buff->toValue(), buff->size());
    return res;
}

_FifoPipe::~_FifoPipe() {
    if(fifoId != -1) {
        close(fifoId);
    }
}

}
