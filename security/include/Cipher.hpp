#ifndef __OBOTCHA_CIPHER_HPP__
#define __OBOTCHA_CIPHER_HPP__

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "SecretKey.hpp"

namespace obotcha {

class _CipherCreator;

DECLARE_SIMPLE_CLASS(Cipher) {
public:
    friend class _CipherCreator;
    
    static const String ZeroPadingStr;
    static const String PKCS7PaddingStr;
    static const String PKCS5PaddingStr;
    static const String PKCS1PaddingStr;
    static const String PKCS8PaddingStr;

    static const String AesStr;
    static const String DesStr;
    static const String RsaStr;

    static const String CbcStr;
    static const String EcbStr;
    static const String CtrStr;
    static const String OcfStr;
    static const String CfbStr;

    enum Padding {
        ZeroPadding = 0,
        PKCS7Padding,
        PKCS5Padding,
        PKCS1Padding,
        PKCS8Padding   
    };

    enum Mode {
        Decrypt = 0,
        Encrypt
    };

    enum CipherType {
        AES = 0,
        DES,
        RSA
    };

    enum CipherPattern {
        CBC = 0,
        ECB,
        CTR,
        OCF,
        CFB
    };

    virtual ByteArray encrypt(ByteArray in) = 0;
    virtual void encrypt(File in,File out) = 0;

    virtual ByteArray decrypt(ByteArray in) = 0;
    virtual void decrypt(File in,File out) = 0;

    int getAlgorithm();
    int getPattern();
    int getPadding();
    int getMode();
    virtual void init(int mode,SecretKey key);

protected:
    void doPadding(ByteArray,int blocksize = 8); //PCKS5 is 8bit size
    void doUnPadding(ByteArray);

private:
    void setAlgorithm(int);
    void setPattern(int);
    void setPadding(int);

    void doPKCS7Padding(ByteArray,int blocksize);
    void doPKCS5Padding(ByteArray);
    void doPKCSZeroPadding(ByteArray,int blocksize);

    void doPKCS7UnPadding(ByteArray);
    void doPKCS5UnPadding(ByteArray);
    void doPKCSZeroUnPadding(ByteArray);

    int algorithmType;
    int patternType;
    int paddingType;

    int mMode;
    SecretKey mKey;

};

}

#endif
