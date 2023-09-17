#ifndef __OBOTCHA_CIPHER_HPP__
#define __OBOTCHA_CIPHER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "SecretKey.hpp"

namespace obotcha {

class _CipherCreator;

DECLARE_CLASS(Cipher) {
public:
    friend class _CipherCreator;
    
    static const String ZeroPadingStr;
    static const String PKCS7PaddingStr;
    static const String PKCS5PaddingStr;
    static const String PKCS1PaddingStr;
    static const String PKCS8PaddingStr;
    static const String OAEPPaddingStr;
    static const String PSSPaddingStr;


    static const String AesStr;
    static const String Aes128Str;
    static const String Aes192Str;
    static const String Aes256Str;

    static const String DesStr;
    static const String RsaStr;
    static const String Rsa3Str;
    static const String Rsaf4Str;

    static const String CbcStr;
    static const String EcbStr;
    static const String CtrStr;
    static const String OcfStr;
    static const String Cfb1Str;
    static const String Cfb8Str;
    static const String Cfb128Str;
    static const String Ofb128Str;
    

    enum class Padding {
        Zero = 0,
        PKCS7,
        PKCS5,
        PKCS1,
        PKCS8,
        OAEP,
        PSS,
        Unknown = -1,
    };

    enum class Mode {
        Decrypt = 0,
        Encrypt
    };

    enum class Type {
        AES = 0,
        AES128,
        AES192,
        AES256,
        DES,
        RSA,
    };

    enum class Pattern {
        CBC = 0,
        ECB,
        CTR,
        OCF,
        CFB1,
        CFB8,
        CFB128,
        OFB128,
        RSA3,
        RSAF4,
        Unknown = -1,
    };

    virtual ByteArray encryptContent(ByteArray in) = 0;
    void encryptFile(File in,File out);

    virtual ByteArray decryptContent(ByteArray in) = 0;
    void decryptFile(File in,File out);
    virtual void init(Mode mode,SecretKey key);

    //int getAlgorithm() const;
    Pattern getPattern() const;
    Padding getPadding() const;
    Mode getMode() const;

protected:
    void doPadding(ByteArray,int blocksize = 8) const; //PCKS5 is 8bit size
    void doPKCS7Padding(ByteArray,int blocksize) const;
    void doPKCS5Padding(ByteArray) const;
    void doPKCSZeroPadding(ByteArray,int blocksize) const;

    void doPKCS7UnPadding(ByteArray) const;
    void doPKCS5UnPadding(ByteArray) const;
    void doPKCSZeroUnPadding(ByteArray) const;
    void doUnPadding(ByteArray) const;
    
    SecretKey getSecretKey();

private:
    //void setAlgorithm(int);
    void setPattern(Pattern);
    void setPadding(Padding);
    void doEncryptOrDescrypt(File in,File out);

    //int algorithmType;
    Pattern patternType;
    Padding paddingType;

    Mode mMode;
    SecretKey mKey;

};

}

#endif
