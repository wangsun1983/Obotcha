#ifndef __OBOTCHA_FILE_DESCRIPTOR_HPP__
#define __OBOTCHA_FILE_DESCRIPTOR_HPP__

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileDescriptor) {
public:
    _FileDescriptor(int fd);

    ~_FileDescriptor();

    int close();

    int getFd();

    int setSockOption(int level,int optname,void *optval,socklen_t oplen);
    int getSockOption(int level,int optname,void *optval,socklen_t*oplen);

    int setFileOption(int cmd,int option);
    int getFileOption();

    void setAsync(bool);
    bool isAsync();

    bool isClosed();

    uint64_t hashcode();

private:
    int _fd;
};

}
#endif
