#ifndef __OBOTCHA_FILE_DESCRIPTOR_HPP__
#define __OBOTCHA_FILE_DESCRIPTOR_HPP__

#include <atomic>
#include <fcntl.h>

#include "Object.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(FileDescriptor) {
public:
    // enum Option {
    //     ReadOnly = O_RDONLY,
    //     WriteOnly = O_WRONLY,
    //     ReadWriteOnly = O_RDWR,
    //     Create = O_CREAT,
    //     Excl = O_EXCL,
    //     Noctty = O_NOCTTY,
    //     Trunc = O_TRUNC,
    //     Append = O_APPEND,
    //     NonBlock = O_NONBLOCK,
    //     NDelay = O_NDELAY,
    //     Sync = O_SYNC,
    //     NoFollow = O_NOFOLLOW,
    //     Directory = O_DIRECTORY,
    // };

    // enum LockType {
    //     ReadLock = F_RDLCK,
    //     WriteLock = F_WRLCK,
    //     UnLock = F_UNLCK,
    // };

    explicit _FileDescriptor(int fd);
    ~_FileDescriptor() override = default;

    int getFd() const;
    int getOption() const;
    bool isAsync() const;
    bool isSocket() const;
    bool isClosed() const;
    uint64_t hashcode() const override;
    int lock(st(IO)::FileLockFlags) const;
    int unlock() const;
    
    int close();
    void setAsync(bool);
    int setOption(int option);
    int addOption(int option);
    int removeOption(int option);
    void monitor();
    void unMonitor(bool isAutoClosed = true);

private:
    int mFd;
    std::atomic<int> mMonitorCount = 0;
    bool mIsClosedRequired = false;
};

}
#endif
