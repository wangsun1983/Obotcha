#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#include "Pipe.hpp"
#include "Inspect.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

const int _Pipe::kMaxBuffSize = PIPE_BUF;
const int _Pipe::ReadChannel = 0;
const int _Pipe::WriteChannel = 1;

_Pipe::_Pipe(int type) {
    pipeFd[WriteChannel] = pipeFd[ReadChannel] = -1;
    pipe2(pipeFd,type);
}

_Pipe::_Pipe():_Pipe(static_cast<int>(st(IO)::FileControlFlags::CloseExec)) {
}


ssize_t _Pipe::write(ByteArray data) const {
    return (data->size() > PIPE_BUF || pipeFd[WriteChannel] == -1)?-EINVAL:
         ::write(pipeFd[WriteChannel],data->toValue(),data->size());
}

ssize_t  _Pipe::read(ByteArray buff) const {
    return (pipeFd[ReadChannel] == -1)?-1:
            ::read(pipeFd[ReadChannel],buff->toValue(),buff->size());
}

int _Pipe::closeReadChannel() {
    int ret = (pipeFd[ReadChannel] == -1)?0:(::close(pipeFd[ReadChannel]));
    pipeFd[ReadChannel] = -1;
    return ret;
}

int _Pipe::closeWriteChannel() {
    int ret = (pipeFd[WriteChannel] == -1)?0:(::close(pipeFd[WriteChannel]));
    pipeFd[WriteChannel] = -1;
    return ret;
}

int _Pipe::getReadChannel() const {
    return pipeFd[ReadChannel];
}

int _Pipe::getWriteChannel() const {
    return pipeFd[WriteChannel];
}

void _Pipe::close() {
    closeWriteChannel();
    closeReadChannel();
}

_Pipe::~_Pipe() {
   close();
}

}

