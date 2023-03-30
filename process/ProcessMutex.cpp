#include "ProcessMutex.hpp"
#include "InitializeException.hpp"
#include "File.hpp"

namespace obotcha {

_ProcessMutex::_ProcessMutex(String path) {
    mPath = path;
    File file = createFile(path);
    if(!file->exists()) {
        file->createNewFile();
    }

    int fd = open(file->getAbsolutePath()->toChars(),O_WRONLY, 0666);
    Panic(fd < 0,InitializeException,"open process mutex file failed");

    mFd = createFileDescriptor(fd);
}

int _ProcessMutex::lock(long interval) {
    return mFd->lock(st(FileDescriptor)::WriteLock);
}

int _ProcessMutex::unlock() {
    return mFd->unlock();
}

_ProcessMutex::~_ProcessMutex() {
    if(mFd != nullptr) {
        mFd->close();
        mFd = nullptr;
    }
}

}
