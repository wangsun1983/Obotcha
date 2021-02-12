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
    if(param->equalsIgnoreCase(st(Cipher)::AesStr)) {
        algorithmType = st(Cipher)::CipherAES;
        AesSecretKey c = createAesSecretKey();
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::DesStr)) {
        algorithmType = st(Cipher)::CipherDES;
        DesSecretKey c = createDesSecretKey();
        return (SecretKey)c;
    } else if(param->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        algorithmType = st(Cipher)::CipherRSA;
        RsaSecretKey c = createRsaSecretKey();
        return (RsaSecretKey)c;
    }

    return nullptr;
}

SecretKey _SecretKeyCreator::getInstance(const char * param) {
    return getInstance(createString(param));
}

}

