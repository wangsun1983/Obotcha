#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "FileDescriptor.hpp"

namespace obotcha {

_FileDescriptor::_FileDescriptor(int fd) {
    mFd = fd;
    mMonitorCount = 0;
    mIsClosedRequired = false;
}

uint64_t _FileDescriptor::hashcode() {
    return mFd;
}

/*
 * struct flcok {
 *  short int l_type;    //锁定的状态
 *  //这三个参数用于分段对文件加锁，若对整个文件加锁，则：l_whence=SEEK_SET,l_start=0,l_len=0;
 *  short int l_whence;  //决定l_start位置
 *  off_t l_start;       //锁定区域的开头位置
 *  off_t l_len;         //锁定区域的大小
 *  pid_t l_pid;         //锁定动作的进程
 * };
 */
int _FileDescriptor::lock(int type) {
    struct flock s_flock;
    s_flock.l_type = type;
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(mFd, F_SETLKW, &s_flock);
}

int _FileDescriptor::unlock() {
    struct flock s_flock;
    s_flock.l_type = F_UNLCK;
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(mFd, F_SETLKW, &s_flock);
}

void _FileDescriptor::monitor() {
    mMonitorCount++;
}

void _FileDescriptor::unMonitor(bool isAutoClosed) {
    mMonitorCount--;
    if(mMonitorCount == 0) {
        if(mIsClosedRequired || isAutoClosed) {
            close();
        }
    }
}

int _FileDescriptor::close() {
    mIsClosedRequired = true;
    if (mFd > 0) {
        if(mMonitorCount == 0) {
            ::close(mFd);
            mFd = -1;
        } else {
            ::shutdown(mFd,SHUT_RDWR);
        }
    }
    return 0;
}

_FileDescriptor::~_FileDescriptor() {
    //::close(mFd);
}

int _FileDescriptor::setOption(int option) {
    return fcntl(mFd, F_SETFL, option);
}

int _FileDescriptor::addOption(int option) {
    return fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL, 0) | option);
}


int _FileDescriptor::removeOption(int option) {
    return fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL, 0)  & ~option);
}

int _FileDescriptor::getOption() {
    return fcntl(mFd, F_GETFL);
}

void _FileDescriptor::setAsync(bool async) {
    if (async) {
        fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL, 0) | O_NONBLOCK);
    } else {
        fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL, 0) & ~O_NONBLOCK);
    }
}

bool _FileDescriptor::isAsync() {
    return (fcntl(mFd, F_GETFL) & O_NONBLOCK) > 0;
}

bool _FileDescriptor::isSocket() {
    int error = 0;
    socklen_t error_length = sizeof(error);
    return TEMP_FAILURE_RETRY(getsockopt(mFd, SOL_SOCKET, SO_ERROR, &error, &error_length)) == 0;
}

bool _FileDescriptor::isClosed() {
    return fcntl(mFd,F_GETFL,0) == -1;
}

int _FileDescriptor::getFd() {
    return mFd;
}

} // namespace obotcha
