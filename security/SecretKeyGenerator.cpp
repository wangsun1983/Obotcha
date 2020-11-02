#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "IllegalArgumentException.hpp"
#include "SecretKeyGenerator.hpp"
#include "Aes.hpp"

namespace obotcha {

//DES/xxxxx(content)/RSA TYPE/RSA HEAD Type
int _SecretKeyGenerator::genKey(String encrypt,String decrypt,String param) {
    ArrayList<String> params = param->split("/");
    if(params->size() <= 0) {
        Trigger(IllegalArgumentException,"Gen secret key's param is illegal");
    }

    ArrayList<String> restParams = createArrayList<String>();
    if(params->size() > 1) {
        for(int index = 1;index < params->size();index++) {
            restParams->add(params->get(index));
        }
    }

    //DES/AES/RSA
    String algorithm = params->get(0);
    int algorithmType = -1;
    if(algorithm->equalsIgnoreCase(st(Cipher)::AesStr)) {
        algorithmType = st(Cipher)::AES;
        Aes c = createAes();
        c->genKey(encrypt,decrypt,restParams);
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::DesStr)) {
        algorithmType = st(Cipher)::DES;
        //TODO
    } else if(algorithm->equalsIgnoreCase(st(Cipher)::RsaStr)) {
        algorithmType = st(Cipher)::RSA;
        //TODO
    }

    if(algorithmType == -1) {
        return -1;
    }
    
}

SecretKey _SecretKeyGenerator::loadKey(const char * path) {
    return loadKey(createString(path));
}

SecretKey _SecretKeyGenerator::loadKey(String path) {
    SecretKey key = createSecretKey();
    File file = createFile(path);
    key->setFile(file);
    return key;
}

SecretKey _SecretKeyGenerator::loadKey(ByteArray content) {
    SecretKey key = createSecretKey();
    key->setContent(content);
    return key;
}

}

