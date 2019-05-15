#ifndef __SHA_HPP__
#define __SHA_HPP__

#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum ShaAbstractType {
    AbstractSHA1,
    AbstractSHA224,
    AbstractSHA256,
    AbstractSHA384,
    AbstractSHA512,
};

DECLARE_SIMPLE_CLASS(Sha) {

public:
    _Sha(int);

    String encrypt(String str);

    String encrypt(File);
    
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
