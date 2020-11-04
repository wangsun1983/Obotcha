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
        PKCS8Padding,
        OAEPPadding,
        PSSPadding,
    };

    enum Mode {
        Decrypt = 0,
        Encrypt
    };

    enum CipherType {
        CipherAES = 0,
        CipherDES,
        CipherRSA
    };

    enum CipherPattern {
        CBC = 0,
        ECB,
        CTR,
        OCF,
        CFB
    };

    virtual ByteArray encrypt(ByteArray in) = 0;
    void encrypt(File in,File out);

    virtual ByteArray decrypt(ByteArray in) = 0;
    void decrypt(File in,File out);
    virtual void init(int mode,SecretKey key);

    int getAlgorithm();
    int getPattern();
    int getPadding();
    int getMode();

protected:
    void doPadding(ByteArray,int blocksize = 8); //PCKS5 is 8bit size
    void doPKCS7Padding(ByteArray,int blocksize);
    void doPKCS5Padding(ByteArray);
    void doPKCSZeroPadding(ByteArray,int blocksize);

    void doPKCS7UnPadding(ByteArray);
    void doPKCS5UnPadding(ByteArray);
    void doPKCSZeroUnPadding(ByteArray);

    void doUnPadding(ByteArray);
    SecretKey getSecretKey();

private:
    void setAlgorithm(int);
    void setPattern(int);
    void setPadding(int);
    void doEncryptOrDescrypt(File in,File out);

    int algorithmType;
    int patternType;
    int paddingType;

    int mMode;
    SecretKey mKey;

};

}

#endif
