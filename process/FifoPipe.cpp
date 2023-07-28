
#include <fcntl.h>
#include <limits.h>

#include "FifoPipe.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"

namespace obotcha {

const int _FifoPipe::kMaxBuffSize = PIPE_BUF;

_FifoPipe::_FifoPipe(String name,int type,int filemode) {
    mPipeName = name;
    mType = type;
    
    if(mkfifo(mPipeName->toChars(),S_IFIFO|filemode) < 0 && (errno != EEXIST)){
        Trigger(InitializeException,"fifo create failed")
    }

    //Notice:
    //1.if we do not set O_NONBLOCK,
    //  write pipe will wait until read pipe is opened.
    //  read pipe will wait until write pipe open;
    //2.if there is no client is reading fifo pipe,
    //  write pipe with O_NONBLOCK will be failed to create.
    switch(mType) {
        case Write:
            mFifoId = ::open(mPipeName->toChars(),O_WRONLY,0);
        break;

        case AsyncWrite:
            mFifoId = ::open(mPipeName->toChars(),O_WRONLY|O_NONBLOCK,0);
        break;

        case Read:
            mFifoId = ::open(mPipeName->toChars(),O_RDONLY,0);
        break;

        case AsyncRead:
            mFifoId = ::open(mPipeName->toChars(),O_RDONLY|O_NONBLOCK,0);
        break;
    }

    Panic(mFifoId < 0,InitializeException,"fifo open failed")
}

int _FifoPipe::write(ByteArray data) {
    Inspect(mType == Read || mType == AsyncRead || data->size() > kMaxBuffSize,-EINVAL);
    return ::write(mFifoId, data->toValue(), data->size());
}

int _FifoPipe::read(ByteArray buff) {
    Inspect(mType == Write || mType == AsyncWrite,-EINVAL);
    return ::read(mFifoId, buff->toValue(), buff->size());
}

void _FifoPipe::close() {
    Inspect(mFifoId == -1);
    ::close(mFifoId);
    mFifoId = -1;
}

void _FifoPipe::clear() {
    close();
    unlink(mPipeName->toChars());
}

int _FifoPipe::getChannel() {
    return mFifoId;
}

String _FifoPipe::getName() {
    return mPipeName;
}

_FifoPipe::~_FifoPipe() {
    close();
}

}
