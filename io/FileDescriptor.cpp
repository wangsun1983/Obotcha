/**
 * @file File.cpp
 * @brief Instances of the file descriptor class serve as an opaque handle
 *        to the underlying machine-specific structure representing an open
 *        file, an open socket, or another source or sink of bytes. 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "FileDescriptor.hpp"

namespace obotcha {

_FileDescriptor::_FileDescriptor(int fd):mFd(fd) {
}

uint64_t _FileDescriptor::hashcode() const {
    return mFd;
}

/**
 * flcok:
 * 锁定的状态这三个参数用于分段对文件加锁，若对整个文件加锁，
 * 则：l_whence=SEEK_SET,l_start=0,l_len=0;
 * short int l_type;
 * 
 * 决定l_start位置
 * short int l_whence;
 *  
 * 锁定区域的开头位置
 * off_t l_start;
 * 
 * 锁定区域的大小
 * off_t l_len;
 * 
 * 锁定动作的进程
 * pid_t l_pid;
 **/
int _FileDescriptor::lock(st(IO)::FileLockFlags type) const {
    struct flock s_flock;
    s_flock.l_type = static_cast<short>(type);
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(mFd, F_SETLKW, &s_flock);
}

int _FileDescriptor::unlock() const {
    struct flock s_flock;
    s_flock.l_type = static_cast<short>(st(IO)::FileLockFlags::UnLock);
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
    if(mMonitorCount == 0 &&(mIsClosedRequired || isAutoClosed)) {
        close();
    }
}

int _FileDescriptor::close() {
    mIsClosedRequired = true;
    Inspect(mFd < 0,0)
    if(mMonitorCount == 0) {
        ::close(mFd);
        mFd = -1;
    } else {
        ::shutdown(mFd,SHUT_RDWR);
    }
    return 0;
}

int _FileDescriptor::setOption(int option) {
    return fcntl(mFd, F_SETFL, option);
}

int _FileDescriptor::addOption(st(IO)::FileControlFlags option) {
    return fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL, 0) | option);
}


int _FileDescriptor::removeOption(int option) {
    return fcntl(mFd, F_SETFL, fcntl(mFd, F_GETFL, 0)  & ~option);
}

int _FileDescriptor::getOption() const {
    return fcntl(mFd, F_GETFL);
}

void _FileDescriptor::setAsync(bool async) {
    auto flags = fcntl(mFd, F_GETFL, 0);
    fcntl(mFd, F_SETFL,async?
                        flags|O_NONBLOCK:flags &~O_NONBLOCK);
}

bool _FileDescriptor::isAsync() const {
    return (fcntl(mFd, F_GETFL) & O_NONBLOCK) != 0;
}

bool _FileDescriptor::isSocket() const {
    int error = 0;
    socklen_t error_length = sizeof(error);
    return TEMP_FAILURE_RETRY(getsockopt(mFd, SOL_SOCKET, SO_ERROR, &error, &error_length)) == 0;
}

bool _FileDescriptor::isClosed() const {
    return fcntl(mFd,F_GETFL,0) == -1;
}

int _FileDescriptor::getFd() const {
    return mFd;
}

} // namespace obotcha
