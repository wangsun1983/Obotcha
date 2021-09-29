#include "CipherCreator.hpp"
#include "Log.hpp"
#include "Aes.hpp"
#include "Des.hpp"
#include "Rsa.hpp"

namespace obotcha {

Cipher _CipherCreator::getInstance(String param) {
    ArrayList<String> params = param->split("/");
    if(params->size() != 3) {
        LOG(ERROR)<<"Cipher getInstance error param";
        return nullptr;
    }

    //get pattern
    String pattern = params->get(1);
    int patternType = -1;
    if(pattern->equalsIgnoreCase(st(Cipher)::CbcStr)) {
        patternType = st(Cipher)::CBC;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::EcbStr)) {
        patternType = st(Cipher)::ECB;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::CtrStr)) {
        patternType = st(Cipher)::CTR;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::OcfStr)) {
        patternType = st(Cipher)::OCF;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Cfb1Str)) {
        patternType = st(Cipher)::CFB1;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Cfb8Str)) {
        patternType = st(Cipher)::CFB8;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Cfb128Str)) {
        patternType = st(Cipher)::CFB128;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Ofb128Str)) {
        patternType = st(Cipher)::OFB128;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Rsa3Str)) {
        patternType = st(Cipher)::RSA3;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Rsaf4Str)) {
        patternType = st(Cipher)::RSAF4;
    } 

    if(patternType == -1) {
        return nullptr;
    }

    //get padding
    String padding = params->get(2);
    int paddingType = -1;
    if(padding->equalsIgnoreCase(st(Cipher)::ZeroPadingStr)) {
        paddingType = st(Cipher)::ZeroPadding;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS5PaddingStr)) {
        paddingType = st(Cipher)::PKCS5Padding;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS7PaddingStr)) {
        paddingType = st(Cipher)::PKCS7Padding;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS1PaddingStr)) {
        paddingType = st(Cipher)::PKCS1Padding;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS8PaddingStr)) {
        paddingType = st(Cipher)::PKCS8Padding;
    }

    if(paddingType == -1) {
        return nullptr;
    }

    //get algorithm type
    String algorithm = params->get(0);
    printf("algorithm is %s \n",algorithm->toChars());
    int algorithmType = -1;
    if(algorithm->equalsIgnoreCase(st(Cipher)::AesStr)) {
        algorithmType = st(Cipher)::CipherAES;
        Aes c = createAes();
        c->setPadding(paddingType);
        c->setPattern(patternType);
        return (Cipher)c;
    } if(algorithm->equalsIgnoreCase(st(Cipher)::Aes128Str)) {
        algorithmType = st(Cipher)::CipherAES128;
        Aes c = createAes();
        c->setPadding(paddingType);
        c->setPattern(patternType);
        return (Cipher)c;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::Aes192Str)) {
        algorithmType = st(Cipher)::CipherAES192;
        Aes c = createAes();
        c->setPadding(paddingType);
        c->setPattern(patternType);
        return (Cipher)c;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::Aes256Str)) {
        algorithmType = st(Cipher)::CipherAES256;
        Aes c = createAes();
        c->setPadding(paddingType);
        c->setPattern(patternType);
        return (Cipher)c;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::DesStr)) {
        algorithmType = st(Cipher)::CipherDES;
        Des c = createDes();
        c->setPadding(paddingType);
        c->setPattern(patternType);
        return (Cipher)c;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        algorithmType = st(Cipher)::CipherRSA;
        Rsa c = createRsa();
        c->setPadding(paddingType);
        c->setPattern(patternType);
        return (Cipher)c;
    }

    return nullptr;
}

Cipher _CipherCreator::getInstance(const char *param) {
    return getInstance(createString(param));
}

}
