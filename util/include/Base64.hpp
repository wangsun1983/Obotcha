#ifndef __BASE64_HPP__
#define __BASE64_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

#define UUID4_LEN 37
namespace obotcha {

DECLARE_SIMPLE_CLASS(Base64) {

public:
    _Base64();

    String decode(String str);

    String encode(String str);

    String decodeUrl(String str);

    String encodeUrl(String str,int add_pad);

    ByteArray base64_encode(ByteArray buff);

    ByteArray base64_decode(ByteArray buff);

    ByteArray base64_url_encode(ByteArray buff,int add_pad);

    ByteArray base64_url_decode(ByteArray buff);

private:
    static const unsigned char base64_table[65];
    static const unsigned char base64_url_table[65];

    static unsigned char * base64_gen_encode(const unsigned char *src, int len,
                     int *out_len,
                     const unsigned char *table,
                     int add_pad);

    static unsigned char * base64_gen_decode(const unsigned char *src, int len,
                     int *out_len,
                     const unsigned char *table);
};

}
#endif