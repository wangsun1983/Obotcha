#ifndef __OBOTCHA_IO_HPP__
#define __OBOTCHA_IO_HPP__

#include <fcntl.h>
#include <sys/epoll.h>

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(IO) {
public:
    enum class Endianness {
        Little = 0,
        Big
    };

    enum FileControlFlags {
        Append = O_APPEND,
        Trunc = O_TRUNC,
        ReadOnly = O_RDONLY,
        WriteOnly = O_WRONLY,
        ReadWrite = O_RDWR,
        Create = O_CREAT,
        Excl = O_EXCL,
        Noctty = O_NOCTTY,
        NonBlock = O_NONBLOCK,
        NDelay = O_NDELAY,
        Sync = O_SYNC,
        NoFollow = O_NOFOLLOW,
        Directory = O_DIRECTORY,
        CloseExec = O_CLOEXEC,
    };

    enum class FileLockFlags {
        ReadLock = F_RDLCK,
        WriteLock = F_WRLCK,
        UnLock = F_UNLCK,
    };

    class Epoll {
        public:
            enum class Result {
                Ok = 0,
                Remove
            };

            enum Event {
                In = EPOLLIN,
                Pri = EPOLLPRI,
                Out = EPOLLOUT,
                Err = EPOLLERR,
                Hup = EPOLLHUP,
                RdNorm = EPOLLRDNORM,
                WrNorm = EPOLLWRNORM,
            };
    };

    class Reader {
        public:
            enum class Result {
                HasContent = 0,
                NoContent,
            };
    };
};

}
#endif
