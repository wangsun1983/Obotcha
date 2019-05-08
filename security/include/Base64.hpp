#ifndef __BASE_64_HPP__
#define __BASE_64_HPP__

#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/evp.h"

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Base64) {

public:
    _Base64();

    String decode(String str);

    String encode(String str);
    
    ByteArray encode(ByteArray buff);

    ByteArray decode(ByteArray buff);

private:
   char * _encode(const char * input, int length, bool with_new_line);
   char * _decode(const char * input, int length, bool with_new_line);
};

}

#endif
