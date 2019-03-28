#ifndef __DES_HPP__
#define __DES_HPP__

extern "C" {
#include "des.h"
}

#include "File.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Des) {

public:
    void encrypt(File src,File des);
    String encrypt(String);

    void decrypt(File src,File des);
    String decrypt(String);

    void genKey(File);

private:
    File key;    

};

}
#endif
