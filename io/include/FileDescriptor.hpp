#ifndef __OBOTCHA_FILE_DESCRIPTOR_HPP__
#define __OBOTCHA_FILE_DESCRIPTOR_HPP__

#include <atomic>
#include <fcntl.h>

#include "Object.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(FileDescriptor) {
public:
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
    int addOption(st(IO)::FileControlFlags option);
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
