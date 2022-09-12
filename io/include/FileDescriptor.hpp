#ifndef __OBOTCHA_FILE_DESCRIPTOR_HPP__
#define __OBOTCHA_FILE_DESCRIPTOR_HPP__

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _SocketMonitor;

DECLARE_CLASS(FileDescriptor) {
public:
    friend class _SocketMonitor;
    _FileDescriptor(int fd);

    ~_FileDescriptor();

    int close();

    int getFd();

    int setSockOption(int level,int optname,void *optval,socklen_t oplen);
    int getSockOption(int level,int optname,void *optval,socklen_t*oplen);

    int setFileOption(int option);
    int getFileOption();

    void setAsync(bool);
    bool isAsync();

    bool isSocket();

    bool isClosed();

    uint64_t hashcode();

private:
    int _fd;
    bool isMonitored;
    void setAsMonitored(bool);
};

}
#endif
