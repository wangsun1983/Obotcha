#include "ProcessReadWriteLock.hpp"
#include "File.hpp"

namespace obotcha {

//ProcessReadLock

int _ProcessReadLock::lock(long interval) {
    //TODO?
    struct flock s_flock;
    s_flock.l_type = F_RDLCK;
    
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(rwlock->fd, F_SETLKW, &s_flock);
}

int _ProcessReadLock::unlock() {
    struct flock s_flock;
    s_flock.l_type = F_UNLCK;
    
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(rwlock->fd, F_SETLKW, &s_flock);
}

String _ProcessReadLock::getPath() {
    return rwlock->getPath();
}

_ProcessReadLock::_ProcessReadLock(sp<_ProcessReadWriteLock> lock) {
    this->rwlock = lock;
}

//ProcessWriteLock
int _ProcessWriteLock::lock(long interval) {
    //TODO
    struct flock s_flock;
    s_flock.l_type = F_WRLCK;
    
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(rwlock->fd, F_SETLKW, &s_flock);
}

int _ProcessWriteLock::unlock() {
    struct flock s_flock;
    s_flock.l_type = F_UNLCK;
    
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(rwlock->fd, F_SETLKW, &s_flock);
}

String _ProcessWriteLock::getPath() {
    return rwlock->getPath();
}

_ProcessWriteLock::_ProcessWriteLock(ProcessReadWriteLock r) {
    rwlock = r;
}

//ProcessReadWriteLock
_ProcessReadWriteLock::_ProcessReadWriteLock(String path) {
    File file = createFile(path);
    if(!file->exists()) {
        file->createNewFile();
    }
    mPath = path;
    fd = open(file->getAbsolutePath()->toChars(),O_RDWR, 0666);
}

ProcessReadLock _ProcessReadWriteLock::getReadLock() {
    //return createProcessReadLock(AutoClone(this));
    _ProcessReadLock *l = new _ProcessReadLock(AutoClone(this));
    return AutoClone(l);
}

ProcessWriteLock _ProcessReadWriteLock::getWriteLock() {
    _ProcessWriteLock *l = new _ProcessWriteLock(AutoClone(this));
    return AutoClone(l);
}

String _ProcessReadWriteLock::getPath() {
    return mPath;
}

_ProcessReadWriteLock::~_ProcessReadWriteLock() {
    close(fd);
}

}
