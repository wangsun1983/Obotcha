#ifndef __OBOTCHA_AUTO_CLOSE_HPP__
#define __OBOTCHA_AUTO_CLOSE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "OutputStream.hpp"
#include "InputStream.hpp"

namespace obotcha {

class AutoClose {
public:
    AutoClose(int fd):AutoClone(fd,nullptr,nullptr){

    }

    AutoClose(InputStream input):AutoClone(-1,input,nullptr){

    }

    AutoClose(OutputStream output):AutoClone(-1,nullptr,output){

    }

    AutoClose(int fd,InputStream input,OutputStream output){
        this->fd = fd;
        mOut = input;
        mInput = output;
    }

    AutoClose() {

    }

    ~AutoClose() {
        if(fd > 0) {
            close(fd);
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
