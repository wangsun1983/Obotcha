#include "SecretKeyCreator.hpp"
#include "AesSecretKey.hpp"
#include "DesSecretKey.hpp"
#include "RsaSecretKey.hpp"
#include "Cipher.hpp"
#include "Rsa.hpp"
#include "PaddingNotSupportException.hpp"

namespace obotcha {

//RSA or ECB
SecretKey _SecretKeyCreator::getInstance(String param) {
    //get algorithm type
    ArrayList<String> params = param->split("/");
    if(params == nullptr || params->size() == 0) {
        params = ArrayList<String>::New();
        params->add(param);
    }

    param = params->get(0);
    if(param->equalsIgnoreCase(st(Cipher)::AesStr)) {
        auto param2 = params->get(1);
        int keytype = -1;
        if(param2->equalsIgnoreCase(st(Cipher)::Cfb1Str)){
            keytype = st(SecretKey)::KeyAESCFB1;
        } else if(param2->equalsIgnoreCase(st(Cipher)::Cfb8Str)) {
            keytype = st(SecretKey)::KeyAESCFB8;
        } else if(param2->equalsIgnoreCase(st(Cipher)::Cfb128Str)) {
            keytype = st(SecretKey)::KeyAESCFB128;
        } else if(param2->equalsIgnoreCase(st(Cipher)::Ofb128Str)) {
            keytype = st(SecretKey)::KeyAESOFB128;
        }
        
        AesSecretKey c = AesSecretKey::New();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::Aes128Str)) {
        int keytype = st(SecretKey)::KeyAES128;
        AesSecretKey c = AesSecretKey::New();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::Aes192Str)) {
        int keytype = st(SecretKey)::KeyAES192;
        AesSecretKey c = AesSecretKey::New();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::Aes256Str)) {
        int keytype = st(SecretKey)::KeyAES256;
        AesSecretKey c = AesSecretKey::New();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::DesStr)) {
        DesSecretKey c = DesSecretKey::New();
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        //RSA/RSA3/PKCS1Padding
        RsaSecretKey c = RsaSecretKey::New();
        String rsakeymode = params->get(1);
        String paddingtype = params->get(2);

        if(rsakeymode->equalsIgnoreCase("RSAF4")) {
            c->setKeyPattern(st(Cipher)::Pattern::RSAF4);
        } else if(rsakeymode->equalsIgnoreCase("RSA3")) {
            c->setKeyPattern(st(Cipher)::Pattern::RSA3);
        }

        if(paddingtype->equalsIgnoreCase("PKCS1Padding")) {
            c->setKeyPaddingType(st(Cipher)::Padding::PKCS1);
        } else if(paddingtype->equalsIgnoreCase("OEAPPadding")) {
            c->setKeyPaddingType(st(Cipher)::Padding::OAEP);
        } else if(paddingtype->equalsIgnoreCase("PSSPadding")) {
            Trigger(PaddingNotSupportException,"do not support PSSPadding!")
        } else {
            Trigger(PaddingNotSupportException,"not support padding")
        }

        return (RsaSecretKey)c;
    }

    return nullptr;
}

SecretKey _SecretKeyCreator::getInstance(const char * param) {
    return getInstance(String::New(param));
}

}

