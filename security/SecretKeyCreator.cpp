#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "IllegalArgumentException.hpp"
#include "SecretKeyCreator.hpp"
#include "AesSecretKey.hpp"
#include "DesSecretKey.hpp"
#include "RsaSecretKey.hpp"
#include "Cipher.hpp"

namespace obotcha {

//RSA or ECB
SecretKey _SecretKeyCreator::getInstance(String param) {
    //get algorithm type
    int algorithmType = -1;
    ArrayList<String> params = param->split("/");
    if(params == nullptr || params->size() == 0) {
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
        
        AesSecretKey c = createAesSecretKey();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::Aes128Str)) {
        int keytype = st(SecretKey)::KeyAES128;
        AesSecretKey c = createAesSecretKey();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::Aes192Str)) {
        int keytype = st(SecretKey)::KeyAES192;
        AesSecretKey c = createAesSecretKey();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::Aes256Str)) {
        int keytype = st(SecretKey)::KeyAES256;
        AesSecretKey c = createAesSecretKey();
        c->setType(keytype);
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::DesStr)) {
        int keytype = st(SecretKey)::KeyDES;
        DesSecretKey c = createDesSecretKey();
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        int keytype = st(SecretKey)::KeyRSA;
        RsaSecretKey c = createRsaSecretKey();
        return (RsaSecretKey)c;
    }

    return nullptr;
}

SecretKey _SecretKeyCreator::getInstance(const char * param) {
    return getInstance(createString(param));
}

}

