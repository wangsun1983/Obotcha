#include <unistd.h>

#include "AutoCloseFile.hpp"

namespace obotcha {

_AutoCloseFile::_AutoCloseFile(int fd) {
    this->fd = fd;
}

_AutoCloseFile::~_AutoCloseFile() {
    close(fd);
}

int _AutoCloseFile::getFd() {
    return fd;
}

}