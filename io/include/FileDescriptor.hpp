#ifndef __OBOTCHA_FILE_DESCRIPTOR_HPP__
#define __OBOTCHA_FILE_DESCRIPTOR_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(FileDescriptor) {
public:
    _FileDescriptor(int fd);

    ~_FileDescriptor();

    int close();

    int getFd();

    int setFileOption(int option);

    int getFileOption();

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
