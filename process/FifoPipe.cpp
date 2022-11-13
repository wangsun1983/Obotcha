#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "FifoPipe.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"

namespace obotcha {

const int _FifoPipe::MaxBuffSize = PIPE_BUF;

_FifoPipe::_FifoPipe(String name,int type,int filemode) {
    mPipeName = name;
    mType = type;
    
    if(mkfifo(mPipeName->toChars(),S_IFIFO|filemode) < 0 && (errno != EEXIST)){
        Trigger(InitializeException,"fifo create failed");
    }

    //Notice:
    //1.if we do not set O_NONBLOCK,
    //  write pipe will wait until read pipe is opened.
    //  read pipe will wait until write pipe open;
    //2.if there is no client is reading fifo pipe,
    //  write pipe with O_NONBLOCK will be failed to create.
    switch(mType) {
        case Write:
            fifoId = ::open(mPipeName->toChars(),O_WRONLY,0);
        break;

        case AsyncWrite:
            fifoId = ::open(mPipeName->toChars(),O_WRONLY|O_NONBLOCK,0);
        break;

        case Read:
            fifoId = ::open(mPipeName->toChars(),O_RDONLY,0);
        break;

        case AsyncRead:
            fifoId = ::open(mPipeName->toChars(),O_RDONLY|O_NONBLOCK,0);
        break;
    }

    if(fifoId < 0) {
        Trigger(InitializeException,"fifo open failed");
    }
}

int _FifoPipe::write(ByteArray data) {
    Inspect(mType == Read || mType == AsyncRead || data->size() > MaxBuffSize,-EINVAL);
    return ::write(fifoId, data->toValue(), data->size());
}

int _FifoPipe::read(ByteArray buff) {
    Inspect(mType == Write || mType == AsyncWrite,-EINVAL);
    return ::read(fifoId, buff->toValue(), buff->size());
}

void _FifoPipe::close() {
    Inspect(fifoId == -1);
    ::close(fifoId);
    fifoId = -1;
}

void _FifoPipe::clear() {
    close();
    unlink(mPipeName->toChars());
}

//int _FifoPipe::getMaxSize() {
//    return PIPE_BUF;
//}

int _FifoPipe::getChannel() {
    return fifoId;
}

String _FifoPipe::getName() {
    return mPipeName;
}

_FifoPipe::~_FifoPipe() {
    close();
}

}
