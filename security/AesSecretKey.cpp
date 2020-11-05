
#include "AesSecretKey.hpp"
#include "UUID.hpp"
#include "Error.hpp"

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

int _AesSecretKey::generate(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    int result = -1;

    AES_KEY encryptKey;
    AES_KEY decryptKey;

    if(params != nullptr && params->size() != 0) {
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
    }

    const char *c = content->toChars();

    char keyBuff[AES_BLOCK_SIZE + 1] = {0};
    int length = content->size() > AES_BLOCK_SIZE?AES_BLOCK_SIZE:content->size();
    memcpy(keyBuff,c,length);

    if(AES_set_encrypt_key((const unsigned char*)keyBuff,128,encrypt) != 0) {
        return -GenKeyFail;
    }

    if(AES_set_decrypt_key((const unsigned char*)keyBuff,128,decrypt) != 0) {
        return -GenKeyFail;
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
