#ifndef __OBOTCHA_DES_HPP__
#define __OBOTCHA_DES_HPP__

#include "openssl/des.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Des) IMPLEMENTS(Cipher){

public:
    ByteArray encrypt(ByteArray in);
    void encrypt(File in,File out);

    ByteArray decrypt(ByteArray in);
    void decrypt(File in,File out);

private:

    ByteArray _desECB(ByteArray data,DES_key_schedule *schedule);

    ByteArray _desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec);

    void _desFile(File in,File out);
};

}
#endif
