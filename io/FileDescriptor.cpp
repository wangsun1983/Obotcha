#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


#include "FileDescriptor.hpp"

namespace obotcha {

_FileDescriptor::_FileDescriptor(int fd) {
    _fd = fd;
}

//TODO
uint64_t _FileDescriptor::hashcode() {
    return _fd;
}

int _FileDescriptor::close() {
    int ret = 0;
    if(_fd != -1) {
        ret = ::close(_fd);
        _fd = -1;
    }

    return ret;
}

_FileDescriptor::~_FileDescriptor() {
    //::close(_fd);
}

int _FileDescriptor::setFileOption(int cmd, ...) {
    va_list ap;
    void *arg;
    va_start(ap, cmd);
    arg = va_arg(ap, void*);
    va_end(ap);

    return fcntl(_fd,cmd,arg);
}

int _FileDescriptor::getFileOption() {
    return fcntl(_fd,F_GETFL);
}

void _FileDescriptor::setAsync(bool async) {
    if(async) {
        fcntl(_fd, F_SETFL, fcntl(_fd, F_GETFL, 0)| O_NONBLOCK);
    } else {
        fcntl(_fd, F_SETFL, fcntl(_fd, F_GETFL, 0)& ~O_NONBLOCK);
    }
}

int _FileDescriptor::setSockOption(int level,int optname,void *optval,socklen_t oplen) {
    return ::setsockopt(_fd,level,optname,optval,oplen);
}

int _FileDescriptor::getSockOption(int level,int optname,void *optval,socklen_t*oplen) {
    return ::getsockopt(_fd,level,optname,optval,oplen);
}

bool _FileDescriptor::isAsync() {
    return (fcntl(_fd,F_GETFL) & O_NONBLOCK) != 0;
}

int _FileDescriptor::getFd() {
    return _fd;
}



}