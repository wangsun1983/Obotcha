#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "FileDescriptor.hpp"

namespace obotcha {

_FileDescriptor::_FileDescriptor(int fd) {
    _fd = fd;
    mMonitorCount = 0;
    isClosedRequired = false;
}

uint64_t _FileDescriptor::hashcode() {
    return _fd;
}

void _FileDescriptor::monitor() {
    mMonitorCount++;
}

void _FileDescriptor::unMonitor(bool isAutoClosed) {
    mMonitorCount--;
    if(mMonitorCount == 0) {
        if(isClosedRequired || isAutoClosed) {
            close();
        }
    }
}

int _FileDescriptor::close() {
    isClosedRequired = true;
    if (_fd > 0) {
        if(mMonitorCount == 0) {
            ::close(_fd);
            _fd = -1;
        } else {
            ::shutdown(_fd,SHUT_RDWR);
        }
    }
    return 0;
}

_FileDescriptor::~_FileDescriptor() {
    //::close(_fd);
}

int _FileDescriptor::setFileOption(int option) {
    return fcntl(_fd, F_SETFL, fcntl(_fd, F_GETFL, 0) | option);
}

int _FileDescriptor::getFileOption() {
    return fcntl(_fd, F_GETFL);
}

void _FileDescriptor::setAsync(bool async) {
    if (async) {
        fcntl(_fd, F_SETFL, fcntl(_fd, F_GETFL, 0) | O_NONBLOCK);
    } else {
        fcntl(_fd, F_SETFL, fcntl(_fd, F_GETFL, 0) & ~O_NONBLOCK);
    }
}

bool _FileDescriptor::isAsync() {
    return (fcntl(_fd, F_GETFL) & O_NONBLOCK) > 0;
}

bool _FileDescriptor::isSocket() {
    int error = 0;
    socklen_t error_length = sizeof(error);
    return TEMP_FAILURE_RETRY(getsockopt(_fd, SOL_SOCKET, SO_ERROR, &error, &error_length)) == 0;
}

bool _FileDescriptor::isClosed() {
    return fcntl(_fd,F_GETFL,0) == -1;
}

int _FileDescriptor::getFd() {
    return _fd;
}

} // namespace obotcha
