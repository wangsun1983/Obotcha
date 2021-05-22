#ifndef __OBOTCHA_AUTO_CLOSE_HPP__
#define __OBOTCHA_AUTO_CLOSE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "OutputStream.hpp"
#include "InputStream.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

class AutoClose {
public:
    AutoClose(int fd):AutoClose(fd,nullptr,nullptr){

    }

    AutoClose(FileDescriptor fd):AutoClose(fd->getFd(),nullptr,nullptr){

    }

    AutoClose(InputStream input):AutoClose(-1,input,nullptr){

    }

    AutoClose(OutputStream output):AutoClose(-1,nullptr,output){

    }

    AutoClose(int fd,InputStream input,OutputStream output){
        this->fd = fd;
        mOut = output;
        mInput = input;
    }

    AutoClose() {

    }

    ~AutoClose() {
        if(fd > 0) {
            close(fd);
            fd = -1;
        }

        if(mOut != nullptr) {
            mOut->close();
        }

        if(mInput != nullptr) {
            mInput->close();
        }
    }

private:
    int fd;
    OutputStream mOut;
    InputStream mInput;
};


}

#endif
