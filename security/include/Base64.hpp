#ifndef __OBOTCHA_BASE_64_HPP__
#define __OBOTCHA_BASE_64_HPP__

extern "C" {
#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/evp.h"
}

#include "Object.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Base64) {

public:

    String decode(String str) const;

    String encode(String str) const;
    
    ByteArray encode(ByteArray buff) const;

    ByteArray encode(ByteArray buff,int) const;

    ByteArray decode(ByteArray buff) const;

    ByteArray encode(File f) const;

    ByteArray decode(File f) const;

    //https://base64.guru/standards/base64url
    ByteArray decodeBase64Url(ByteArray data) const;

    ByteArray encodeBase64Url(ByteArray data) const;

private:
   ByteArray _encode(const char * input, int length, bool with_new_line) const;
   ByteArray _decode(const char * input, int length, bool with_new_line) const;
};

}

#endif
