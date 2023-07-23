#ifndef __OBOTCHA_DES_HPP__
#define __OBOTCHA_DES_HPP__

extern "C" {
    #include "openssl/des.h"
}

#include "Object.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "Cipher.hpp"

namespace obotcha {

DECLARE_CLASS(Des) IMPLEMENTS(Cipher){

public:
    ByteArray encryptContent(ByteArray in);
    ByteArray decryptContent(ByteArray in);

private:

    ByteArray _desECB(ByteArray data,DES_key_schedule *schedule);

    ByteArray _desCBC(ByteArray data,DES_key_schedule *schedule,DES_cblock *ivec);

    void _desFile(File in,File out);
};

}
#endif
