#ifndef __OBOTCHA_FILE_DESCRIPTOR_HPP__
#define __OBOTCHA_FILE_DESCRIPTOR_HPP__

#include <atomic>
#include <fcntl.h>

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(FileDescriptor) {
public:
    enum Option {
        ReadOnly = O_RDONLY,
        WriteOnly = O_WRONLY,
        ReadWriteOnly = O_RDWR,
        Create = O_CREAT,
        Excl = O_EXCL,
        Noctty = O_NOCTTY,
        Trunc = O_TRUNC,
        Append = O_APPEND,
        NonBlock = O_NONBLOCK,
        NDelay = O_NDELAY,
        Sync = O_SYNC,
        NoFollow = O_NOFOLLOW,
        Directory = O_DIRECTORY,
    };

    _FileDescriptor(int fd);

    ~_FileDescriptor();

    int close();

    int getFd();

    //File::Type
    int setOption(int option);

    int addOption(int option);

    int removeOption(int option);

    int getOption();

    void setAsync(bool);

    bool isAsync();

    bool isSocket();

    bool isClosed();
    
    uint64_t hashcode();
    
    void monitor();
    void unMonitor(bool isAutoClosed = true);

private:
    int _fd;
    //bool mShutdownBeforeClose;
    std::atomic<int> mMonitorCount;
    bool isClosedRequired;
};

}
#endif
