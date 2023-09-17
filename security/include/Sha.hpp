#ifndef __OBOTCHA_SHA_HPP__
#define __OBOTCHA_SHA_HPP__

#include "Object.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "MessageDigestInterface.hpp"

namespace obotcha {

DECLARE_CLASS(Sha) IMPLEMENTS(MessageDigestInterface) {

public:
    enum class Type {
        Sha1 = 0,
        Sha224,
        Sha256,
        Sha384,
        Sha512,
    };
    
    explicit _Sha(Type);

    String encodeContent(ByteArray) override;
    String encodeFile(File) override;

    ByteArray encryptRawData(ByteArray) const;
    
private:

    Type mType;

    void calc_fileSHA1(const char *filename,unsigned char *dgst) const;
    void calc_fileSHA224(const char *filename,unsigned char *dgst) const;
    void calc_fileSHA256(const char *filename,unsigned char *dgst) const;
    void calc_fileSHA384(const char *filename,unsigned char *dgst) const;
    void calc_fileSHA512(const char *filename,unsigned char *dgst) const;

    void calc_stringSHA1(const char *content,size_t length,unsigned char *dgst) const;
    void calc_stringSHA224(const char *content,size_t length,unsigned char *dgst) const;
    void calc_stringSHA256(const char *content,size_t length,unsigned char *dgst) const;
    void calc_stringSHA384(const char *content,size_t length,unsigned char *dgst) const;
    void calc_stringSHA512(const char *content,size_t length,unsigned char *dgst) const;

    ByteArray convert(ByteArray) const;
};

}

#endif
