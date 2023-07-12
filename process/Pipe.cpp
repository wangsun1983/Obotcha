#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#include "Pipe.hpp"
#include "Inspect.hpp"

namespace obotcha {

const int _Pipe::kMaxBuffSize = PIPE_BUF;

_Pipe::_Pipe(Type type) {
    pipeFd[WriteChannel] = pipeFd[ReadChannel] = -1;
    pipe2(pipeFd,type);
}

_Pipe::_Pipe():_Pipe(Type::Default) {
}


int _Pipe::write(ByteArray data) {
    return (data->size() > PIPE_BUF || pipeFd[WriteChannel] == -1)?-EINVAL:
         ::write(pipeFd[WriteChannel],data->toValue(),data->size());
}

int  _Pipe::read(ByteArray buff) {
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

int _Pipe::getReadChannel() {
    return pipeFd[ReadChannel];
}

int _Pipe::getWriteChannel() {
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

