#ifndef __OBOTCHA_AUTO_CLOSE_FILE_HPP__
#define __OBOTCHA_AUTO_CLOSE_FILE_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AutoCloseFile) {
public:
    _AutoCloseFile(int fd);
    ~_AutoCloseFile();
    int getFd();

private:
    int fd;
};

}
#endif
