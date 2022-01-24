
#include "AesSecretKey.hpp"
#include "UUID.hpp"
#include "Error.hpp"
#include "Cipher.hpp"
#include "InvalidKeyException.hpp"

namespace obotcha {

void * _AesSecretKey::get() {
    return &mKey;
}
    
int _AesSecretKey::loadEncryptKey(String path) {
    return loadKey(path);
}

int _AesSecretKey::loadDecryptKey(String path) {
    return loadKey(path);
}

void _AesSecretKey::setType(int type) {
    mType = type;
}

int _AesSecretKey::getKeyLength() {
    switch(mType) {
        case KeyAES128:
        return 128/8;

        case KeyAES192:
        return 192/8;

        case KeyAES256:
        return 256/8;

        case KeyAESCFB1:
        case KeyAESCFB8:
        case KeyAESCFB128:
        return 16;

        case KeyAESOFB128:
        return 128/8;
        break;
    }

    return -1;
}

int _AesSecretKey::keyCheck(String key) {
    switch(mType) {
        case KeyAESCFB1:
        case KeyAESCFB8:
        case KeyAESCFB128:
        if(key->size() != 16 && key->size() != 24 && key->size() != 32) {
            Trigger(InvalidKeyException,"CFB key size must be 16/24/32");
        }
        return 0;
    }

    return 0;
}

int _AesSecretKey::generate(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    int result = -1;

    AES_KEY encryptKey;
    AES_KEY decryptKey;
    
    if(params != nullptr && params->size() != 0) {
        keyCheck(params->get(0));
        result = genKey(params->get(0),&encryptKey,&decryptKey);
    } else {
        result = genKey(nullptr,&encryptKey,&decryptKey);
    }

    if(result != 0) {
        return result;
    }
    
    FILE *dec_key_file = fopen(decKeyFile->toChars(), "wb");
    int dec_size = fwrite(&decryptKey, 1, sizeof(AES_KEY), dec_key_file);

    FILE *enc_key_file = fopen(encKeyFile->toChars(), "wb");
    int enc_size = fwrite(&encryptKey, 1, sizeof(AES_KEY), enc_key_file);
    
    fclose(dec_key_file);
    fclose(enc_key_file);

    return (dec_size > 0) && (enc_size > 0);
}

int _AesSecretKey::genKey(String content,AES_KEY *encrypt,AES_KEY *decrypt) {
    if(content == nullptr) {
        UUID uuid = createUUID();
        content = uuid->generate();
        //if it is a cfb,size must be 8/16/32
        content = content->subString(0,32);
    }

    const char *c = content->toChars();

    int keylength = getKeyLength();
    char keyBuff[keylength];
    memset(keyBuff,0,keylength);

    int length = (content->size() > keylength)?keylength:content->size();
    memcpy(keyBuff,c,length);
    int ret = AES_set_encrypt_key((const unsigned char*)keyBuff,keylength*8,encrypt);
    if( ret!= 0) {
        return -GenKeyFail;
    }

    //Aes cfb/ofb's dec key is same as enc key!!!
    if(mType == KeyAESCFB1 || mType == KeyAESCFB8 || mType == KeyAESCFB128 || mType == KeyAESOFB128) {
        if(AES_set_encrypt_key((const unsigned char*)keyBuff,keylength*8,decrypt) != 0) {
            return -GenKeyFail;
        }
    } else {
        if(AES_set_decrypt_key((const unsigned char*)keyBuff,keylength*8,decrypt) != 0) {
            return -GenKeyFail;
        }
    }

    return 0;
}

int _AesSecretKey::loadKey(String path) {
    File file = createFile(path);

    FILE *key_file = fopen(file->getAbsolutePath()->toChars(), "rb");

    if (!key_file) {
        return -FileNotExists;
    }
    int size = fread(&mKey, 1, sizeof(AES_KEY), key_file);
    fclose(key_file);

    if(size <= 0) {
        return -ReadFail;
    }

    return size;
}

}
