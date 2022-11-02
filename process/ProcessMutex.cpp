#include "ProcessMutex.hpp"
#include "File.hpp"

namespace obotcha {

_ProcessMutex::_ProcessMutex(String path) {
    mPath = path;
    File file = createFile(path);
    if(!file->exists()) {
        file->createNewFile();
    }
    this->mFd = open(file->getAbsolutePath()->toChars(),O_WRONLY, 0666);
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
int _ProcessMutex::lock(long interval) {
    //TODO
    struct flock s_flock;
    s_flock.l_type = F_WRLCK;
    
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(mFd, F_SETLKW, &s_flock); 
}

int _ProcessMutex::unlock() {
    struct flock s_flock;
    s_flock.l_type = F_UNLCK;
    
    s_flock.l_whence = SEEK_SET;
    s_flock.l_start = 0;
    s_flock.l_len = 0;
    s_flock.l_pid = getpid();
    return fcntl(mFd, F_SETLKW, &s_flock); 
}

_ProcessMutex::~_ProcessMutex() {
    close(mFd);
}


}
