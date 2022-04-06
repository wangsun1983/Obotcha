#include "Pipe.hpp"
#include "Error.hpp"

namespace obotcha {

_Pipe::_Pipe(Type type) {
    pipeFd[WriteChannel] = -1;
    pipeFd[ReadChannel] = -1;
    pipe2(pipeFd,type);
}

_Pipe::_Pipe():_Pipe(Type::Default) {
}


int _Pipe::write(ByteArray data) {
    if(data->size() > PIPE_BUF || pipeFd[WriteChannel] == -1) {
        return -EINVAL;
    }

    return ::write(pipeFd[WriteChannel],data->toValue(),data->size());
}

int  _Pipe::read(ByteArray buff) {
    if(pipeFd[ReadChannel] == -1) {
        return -1;
    }
    return ::read(pipeFd[ReadChannel],buff->toValue(),buff->size());
}

int _Pipe::closeReadChannel() {
    int ret = 0;
    if(pipeFd[ReadChannel] != -1) {
        ret = ::close(pipeFd[ReadChannel]);
        pipeFd[ReadChannel] = -1;
    }

    return ret;
}

int _Pipe::closeWriteChannel() {
    int ret = 0;
    if(pipeFd[WriteChannel] != -1) {
        ret = ::close(pipeFd[WriteChannel]);
        pipeFd[WriteChannel] = -1;
    }

    return ret;
}

int _Pipe::getReadChannel() {
    return pipeFd[ReadChannel];
}

int _Pipe::getWriteChannel() {
    return pipeFd[WriteChannel];
}

int _Pipe::getMaxSize() {
    return PIPE_BUF;
}

void _Pipe::close() {
    closeWriteChannel();
    closeReadChannel();
}

_Pipe::~_Pipe() {
   close();
}

}

