
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>

#include "FifoPipe.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"
#include "Log.hpp"

namespace obotcha {

const int _FifoPipe::kMaxBuffSize = PIPE_BUF;


_FifoPipe::_FifoPipe(String name,Type type,int filemode):mType(type),mPipeName(name) {
    //Notice:
    //1.if we do not set O_NONBLOCK,
    //  write pipe will wait until read pipe is opened.
    //  read pipe will wait until write pipe open;
    //2.if there is no client is reading fifo pipe,
    //  write pipe with O_NONBLOCK will be failed to create.
    switch(mType) {
        case _FifoPipe::Type::Write:
            mFifoId = ::open(mPipeName->toChars(),O_WRONLY,0);
        break;

        case _FifoPipe::Type::AsyncWrite:
            mFifoId = ::open(mPipeName->toChars(),O_WRONLY|O_NONBLOCK,0);
        break;

        case _FifoPipe::Type::Read:
            mFifoId = ::open(mPipeName->toChars(),O_RDONLY,0);
        break;

        case _FifoPipe::Type::AsyncRead:
            mFifoId = ::open(mPipeName->toChars(),O_RDONLY|O_NONBLOCK,0);
        break;
    }

    Panic(mFifoId < 0,InitializeException,"fifo open failed")
}

ssize_t _FifoPipe::write(ByteArray data) const {
    Inspect(mType == _FifoPipe::Type::Read || mType == _FifoPipe::Type::AsyncRead || data->size() > kMaxBuffSize,-EINVAL)
    return ::write(mFifoId, data->toValue(), data->size());
}

ssize_t _FifoPipe::read(ByteArray buff) const {
    Inspect(mType == _FifoPipe::Type::Write || mType == _FifoPipe::Type::AsyncWrite,-EINVAL)
    return ::read(mFifoId, buff->toValue(), buff->size());
}

void _FifoPipe::close() {
    Inspect(mFifoId == -1)
    ::close(mFifoId);
    mFifoId = -1;
}

int _FifoPipe::getChannel() const {
    return mFifoId;
}

String _FifoPipe::getName() const {
    return mPipeName;
}

int _FifoPipe::Create(String name) {
    Clear(name);
    if(mkfifo(name->toChars(),S_IFIFO|0666) < 0 && (errno != EEXIST)){
        return -1;
    }

    return 0;
}

int _FifoPipe::Clear(String name) {
    return unlink(name->toChars());
}

_FifoPipe::~_FifoPipe() {
    close();
}

}
