#ifndef __OBOTCHA_BASE_64_HPP__
#define __OBOTCHA_BASE_64_HPP__

#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/evp.h"

#include "Object.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Base64) {

public:

    String decode(String str);

    String encode(String str);
    
    ByteArray encode(ByteArray buff);

    ByteArray encode(ByteArray buff,int);

    ByteArray decode(ByteArray buff);

    ByteArray encode(File f);

    ByteArray decode(File f);

    //https://base64.guru/standards/base64url
    ByteArray decodeBase64Url(ByteArray data);

    ByteArray encodeBase64Url(ByteArray data);

private:
   ByteArray _encode(const char * input, int length, bool with_new_line);
   ByteArray _decode(const char * input, int length, bool with_new_line);
};

}

#endif
