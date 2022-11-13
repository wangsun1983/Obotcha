#ifndef __OBOTCHA_AUTO_CLOSE_HPP__
#define __OBOTCHA_AUTO_CLOSE_HPP__

#include "Object.hpp"
#include "FileDescriptor.hpp"
#include "InputStream.hpp"
#include "OutputStream.hpp"

namespace obotcha {

class AutoClose {
public:
    AutoClose(int fd) : AutoClose(fd, nullptr, nullptr) {
        //Nothing
    }

    AutoClose(FileDescriptor fd) : AutoClose(fd->getFd(), nullptr, nullptr) {
        //Nothing
    }

    AutoClose(InputStream input) : AutoClose(-1, input, nullptr) {
        //Nothing
    }

    AutoClose(OutputStream output) : AutoClose(-1, nullptr, output) {
        //Nothing
    }

    AutoClose() : AutoClose(-1,nullptr,nullptr) {
        //Nothing
    }

    AutoClose(int fd, InputStream input, OutputStream output) {
        this->fd = fd;
        mOut = output;
        mInput = input;
    }

    ~AutoClose() {
        if (fd > 0) {
            close(fd);
            fd = -1;
        }

        if (mOut != nullptr) {
            mOut->close();
            mOut = nullptr;
        }

        if (mInput != nullptr) {
            mInput->close();
            mOut = nullptr;
        }
    }

private:
    int fd;
    OutputStream mOut;
    InputStream mInput;
};

} // namespace obotcha

#endif
