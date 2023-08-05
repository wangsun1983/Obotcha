#include "ProcessReadWriteLock.hpp"
#include "File.hpp"

namespace obotcha {

int _ProcessReadLock::lock(long interval) {
    return rwlock->mFd->lock(st(FileDescriptor)::ReadLock);
}

int _ProcessReadLock::unlock() {
    return rwlock->mFd->unlock();
}

String _ProcessReadLock::getPath() {
    return rwlock->getPath();
}

_ProcessReadLock::_ProcessReadLock(sp<_ProcessReadWriteLock> lock):rwlock(lock) {
}

//ProcessWriteLock
int _ProcessWriteLock::lock(long interval) {
    return rwlock->mFd->lock(st(FileDescriptor)::WriteLock);
}

int _ProcessWriteLock::unlock() {
    return rwlock->mFd->unlock();
}

String _ProcessWriteLock::getPath() {
    return rwlock->getPath();
}

_ProcessWriteLock::_ProcessWriteLock(ProcessReadWriteLock r):rwlock(r) {
}

//ProcessReadWriteLock
_ProcessReadWriteLock::_ProcessReadWriteLock(String path) {
    File file = createFile(path);
    if(!file->exists()) {
        file->createNewFile();
    }
    mPath = path;
    mFd = createFileDescriptor(open(file->getAbsolutePath()->toChars(),O_RDWR, 0666));
}

ProcessReadLock _ProcessReadWriteLock::getReadLock() {
    auto l = new _ProcessReadLock(AutoClone(this));
    return AutoClone(l);
}

ProcessWriteLock _ProcessReadWriteLock::getWriteLock() {
    auto l = new _ProcessWriteLock(AutoClone(this));
    return AutoClone(l);
}

String _ProcessReadWriteLock::getPath() {
    return mPath;
}

_ProcessReadWriteLock::~_ProcessReadWriteLock() {
    if(mFd != nullptr) {
        mFd->close();
        mFd = nullptr;
    }
}

}
