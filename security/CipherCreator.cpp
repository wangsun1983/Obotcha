#include "CipherCreator.hpp"
#include "Log.hpp"

namespace obotcha {

Cipher _CipherCreator::getInstance(String param) {
    ArrayList<String> params = param->split("/");
    if(params->size() != 3) {
        LOG(ERROR)<<"Cipher getInstance error param";
        return nullptr;
    }

    //get algorithm type
    String algorithm = params->get(0);
    int algorithmType = -1;
    if(algorithm->equalsIgnoreCase(st(Cipher)::AesStr)) {
        algorithmType = st(Cipher)::AES;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::DesStr)) {
        algorithmType = st(Cipher)::DES;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        algorithmType = st(Cipher)::RSA;
    }

    if(algorithmType == -1) {
        return nullptr;
    }

    //get pattern
    String pattern = params->get(1);
    int patternType = -1;
    if(pattern->equalsIgnoreCase(st(Cipher)::CbcStr)) {
        patternType = st(Cipher)::CBC;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::EcbStr)) {
        patternType = st(Cipher)::ECB;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::CtrStr)) {
        patternType = st(Cipher)::CTR;
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::OcfStr)) {
        patternType = st(Cipher)::OCF;
    }else if(algorithm->equalsIgnoreCase(st(Cipher)::CfbStr)) {
        patternType = st(Cipher)::CFB;
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

    //start create cipher

}

Cipher _CipherCreator::getInstance(const char *param) {
    return getInstance(createString(param));
}

}
