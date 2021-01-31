#ifndef __OBOTCHA_BASE_64_HPP__
#define __OBOTCHA_BASE_64_HPP__

#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/evp.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Base64) {

public:

    String decode(String str);

    String encode(String str);
    
    ByteArray encode(ByteArray buff);

    ByteArray encode(ByteArray buff,int);

    ByteArray decode(ByteArray buff);

    ByteArray encode(File f);

    ByteArray decode(File f);

private:
   char * _encode(const char * input, int length, bool with_new_line,int *);
   char * _decode(const char * input, int length, bool with_new_line,int *);
};

}

#endif
