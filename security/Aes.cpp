#include "Aes.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

#include "UUID.hpp"

namespace obotcha {

_Aes::_Aes(int aestype) {
    mType = aestype;
}

void _Aes::genKey(String filepath,int mode) {
    _genKey(mode);
    _saveKey(filepath,mode);
}

void _Aes::genKey(const char * filepath,int mode) {
    _genKey(mode);
    _saveKey(createString(filepath),mode);
}

void _Aes::genKey(File file,String content,int mode) {
    _genKey(content,mode);
    _saveKey(file->getAbsolutePath(),mode);
}

void _Aes::genKey(String filepath,String content,int mode) {
    _genKey(content,mode);
    _saveKey(filepath,mode);
}

void _Aes::genKey(const char * filepath,String content,int mode) {
    _genKey(content,mode);
    _saveKey(createString(filepath),mode);
}

void _Aes::loadKey(File file,int mode) {
    loadKey(file->getAbsolutePath(),mode);
}

void _Aes::loadKey(String path,int mode) {
    loadKey(path->toChars(),mode);
}

void _Aes::loadKey(const char *filepath,int mode) {
    FILE *key_file = fopen(filepath, "rb");
    if (!key_file) {
        return;
    }
    
    switch(mode) {
        case AES_ENCRYPT:
            fread(&mEncryptKey, 1, sizeof(AES_KEY), key_file);
        break;

        case AES_DECRYPT:
            fread(&mDecryptKey, 1, sizeof(AES_KEY), key_file);
        break;
    }
    
    fclose(key_file);
}

String _Aes::decode(String str) {
    ByteArray result;

    switch(mType) {
        case AesTypeECB:
            result = _aesECB(createByteArray(str),AES_DECRYPT);
        break;

        case AesTypeCBC:
        //TODO
        break;
    }

    char *p = result->toValue();
    return createString(p);
}

String _Aes::encode(String str) {
    ByteArray result;

    switch(mType) {
        case AesTypeECB:
            result = _aesECB(createByteArray(str),AES_ENCRYPT);
        break;

        case AesTypeCBC:
        //TODO
        break;
    }

    char *p = result->toValue();
    return createString(p);
}
    
ByteArray _Aes::encode(ByteArray buff) {
    switch(mType) {
        case AesTypeECB:
            return _aesECB(buff,AES_ENCRYPT);
        break;

        case AesTypeCBC:
        //TODO
        break;
    }

    return nullptr;
}

ByteArray _Aes::decode(ByteArray buff) {
    switch(mType) {
        case AesTypeECB:
            return _aesECB(buff,AES_DECRYPT);
        break;

        case AesTypeCBC:
        //TODO
        break;
    }

    return nullptr;
}

void _Aes::_genKey(String content,int mode) {
    const char *c = content->toChars();
    switch(mode) {
        case AES_ENCRYPT:
            AES_set_encrypt_key((const unsigned char*)c,128,&mEncryptKey);
        break;

        case AES_DECRYPT:
            AES_set_decrypt_key((const unsigned char*)c,128,&mDecryptKey);
        break;
    }
}

void _Aes::_genKey(int mode) {
    UUID uuid = createUUID();
    const char *c = uuid->toValue()->toChars();

    switch(mode) {
        case AES_ENCRYPT:
            AES_set_encrypt_key((const unsigned char*)c,128,&mEncryptKey);
        break;

        case AES_DECRYPT:
            AES_set_decrypt_key((const unsigned char*)c,128,&mDecryptKey);
        break;
    }
}

void _Aes::_saveKey(String filepath,int mode) {
    FILE *key_file = fopen(filepath->toChars(), "wb");
    short int bytes_written = 0;
    switch(mode) {
        case AES_ENCRYPT:
            fwrite(&mEncryptKey, 1, sizeof(AES_KEY), key_file);
        break;

        case AES_DECRYPT:
            fwrite(&mDecryptKey, 1, sizeof(AES_KEY), key_file);
        break;
    }
    
    fclose(key_file);
}

ByteArray _Aes::_aesECB(ByteArray data,int mode) {
    unsigned char *in = (unsigned char *)data->toValue();
    ByteArray outData = createByteArray(data->size());
    unsigned char *out = (unsigned char *)outData->toValue();
    switch(mode) {
        case AES_ENCRYPT:
            AES_ecb_encrypt(in,out,&mEncryptKey,AES_ENCRYPT);
        break;

        case AES_DECRYPT:
            AES_ecb_encrypt(in,out,&mDecryptKey,AES_DECRYPT);
        break;
    }
    
    return outData;
}

ByteArray _Aes::_aesCBC(ByteArray data,unsigned char *ivec,int mode) {

}

}
