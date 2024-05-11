#include "CipherCreator.hpp"
#include "Log.hpp"
#include "Aes.hpp"
#include "Des.hpp"
#include "Rsa.hpp"
#include "Inspect.hpp"

namespace obotcha {

Cipher _CipherCreator::getInstance(String param) {
    ArrayList<String> params = param->split("/");
    if(params->size() != 3) {
        LOG(ERROR)<<"Cipher getInstance error param";
        return nullptr;
    }

    //get pattern
    String pattern = params->get(1);
    st(Cipher)::Pattern patternType = st(Cipher)::Pattern::Unknown;
    if(pattern->equalsIgnoreCase(st(Cipher)::CbcStr)) {
        patternType = st(Cipher)::Pattern::CBC;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::EcbStr)) {
        patternType = st(Cipher)::Pattern::ECB;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::CtrStr)) {
        patternType = st(Cipher)::Pattern::CTR;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::OcfStr)) {
        patternType = st(Cipher)::Pattern::OCF;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Cfb1Str)) {
        patternType = st(Cipher)::Pattern::CFB1;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Cfb8Str)) {
        patternType = st(Cipher)::Pattern::CFB8;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Cfb128Str)) {
        patternType = st(Cipher)::Pattern::CFB128;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Ofb128Str)) {
        patternType = st(Cipher)::Pattern::OFB128;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Rsa3Str)) {
        patternType = st(Cipher)::Pattern::RSA3;
    } else if(pattern->equalsIgnoreCase(st(Cipher)::Rsaf4Str)) {
        patternType = st(Cipher)::Pattern::RSAF4;
    } 

    Inspect(patternType == st(Cipher)::Pattern::Unknown,nullptr)

    //get padding
    String padding = params->get(2);
    st(Cipher)::Padding paddingType = st(Cipher)::Padding::Unknown;
    if(padding->equalsIgnoreCase(st(Cipher)::ZeroPadingStr)) {
        paddingType = st(Cipher)::Padding::Zero;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS5PaddingStr)) {
        paddingType = st(Cipher)::Padding::PKCS5;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS7PaddingStr)) {
        paddingType = st(Cipher)::Padding::PKCS7;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS1PaddingStr)) {
        paddingType = st(Cipher)::Padding::PKCS1;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PKCS8PaddingStr)) {
        paddingType = st(Cipher)::Padding::PKCS8;
    } else if(padding->equalsIgnoreCase(st(Cipher)::OAEPPaddingStr)) {
        paddingType = st(Cipher)::Padding::OAEP;
    } else if(padding->equalsIgnoreCase(st(Cipher)::PSSPaddingStr)) {
        paddingType = st(Cipher)::Padding::PSS;
    }
    Inspect(paddingType == st(Cipher)::Padding::Unknown,nullptr)

    //get algorithm type
    String algorithm = params->get(0);
    Cipher c = nullptr;
    if(algorithm->equalsIgnoreCase(st(Cipher)::AesStr) ||
       algorithm->equalsIgnoreCase(st(Cipher)::Aes128Str) ||
       algorithm->equalsIgnoreCase(st(Cipher)::Aes192Str) ||
       algorithm->equalsIgnoreCase(st(Cipher)::Aes256Str) ) {
        c = Aes::New();
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::DesStr)) {
        c = Des::New();
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        c = Rsa::New();
    }

    Inspect(c == nullptr,nullptr)
    c->setPadding(paddingType);
    c->setPattern(patternType);
    return c;
}

Cipher _CipherCreator::getInstance(const char *param) {
    return getInstance(String::New(param));
}

}
