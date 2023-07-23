#ifndef __OBOTCHA_MESSAGE_DIEGS_INTERFACE_HPP__
#define __OBOTCHA_MESSAGE_DIEGS_INTERFACE_HPP__

#include "Object.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(MessageDigestInterface) {
public:
    virtual String encodeContent(ByteArray data) = 0;
    virtual String encodeString(String data);
    virtual String encodeFile(File);
};

}

#endif
