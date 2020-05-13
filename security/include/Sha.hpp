#ifndef __OBOTCHA_SHA_HPP__
#define __OBOTCHA_SHA_HPP__

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum ShaAbstractType {
    SHA_1,
    SHA_224,
    SHA_256,
    SHA_384,
    SHA_512,
};

DECLARE_SIMPLE_CLASS(Sha) {

public:
    _Sha(int);

    String encrypt(String str);

    String encrypt(File);

    ByteArray encryptRawData(ByteArray);
    
private:

    int mType;

    void calc_fileSHA1(const char *filename,unsigned char *dgst);
    void calc_fileSHA224(const char *filename,unsigned char *dgst);
    void calc_fileSHA256(const char *filename,unsigned char *dgst);
    void calc_fileSHA384(const char *filename,unsigned char *dgst);
    void calc_fileSHA512(const char *filename,unsigned char *dgst);

    void calc_stringSHA1(const char *content,int length,unsigned char *dgst);
    void calc_stringSHA224(const char *content,int length,unsigned char *dgst);
    void calc_stringSHA256(const char *content,int length,unsigned char *dgst);
    void calc_stringSHA384(const char *content,int length,unsigned char *dgst);
    void calc_stringSHA512(const char *content,int length,unsigned char *dgst);

    String convert(unsigned char *,int length);
};

}

#endif
