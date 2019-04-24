#include <unistd.h>
#include <stdio.h>

#include "Pipe.hpp"

namespace obotcha {

_Pipe::_Pipe() {
    isCreated = false;
}

bool _Pipe::init() {
    int result = pipe(pipeFd);
    isCreated = (result != -1);
    return isCreated;
}

bool _Pipe::writeTo(int type,ByteArray data) {
    if(!isCreated) {
        return false;
    }

    int fd = pipeFd[type];
    int result = write(fd,data->toValue(),data->size());

    return (result != -1);
}

int  _Pipe::readFrom(int type,ByteArray buff) {
    if(!isCreated) {
        return -1;
    }

    int fd = pipeFd[type];
    int nbytes = read(fd,buff->toValue(),buff->size());
    return nbytes;
}

_Pipe::~_Pipe() {
    if(isCreated) {
        close(pipeFd[0]);
        close(pipeFd[1]);    
    }    
}

}

