#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aes.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "IllegalStateException.hpp"
#include "Error.hpp"

#include "UUID.hpp"

namespace obotcha {

int _Aes::genKey(String decKeyFile,String encKeyFile) {
    int result = _genKey();
    if(result != 0) {
        return result;
    }
    
    result = _saveKey(encKeyFile,st(Cipher)::Encrypt);
    if(result != 0) {
        return result;
    }

    result = _saveKey(decKeyFile,st(Cipher)::Decrypt);

    return result;
}

int _Aes::genKey(String decKeyFile,String encKeyFile,String content) {
    int result = _genKey(content);
    if(result != 0) {
        return result;
    }

    result = _saveKey(encKeyFile,Encrypt);
    if(result != 0) {
        return result;
    }

    result = _saveKey(decKeyFile,Decrypt);

    return result;
}

void _Aes::init(int mode,SecretKey key) {
    st(Cipher)::init(mode,key);
    loadKey(key->getFile(),mode);
}

int _Aes::loadKey(File file,int mode) {
    FILE *key_file = fopen(file->getAbsolutePath()->toChars(), "rb");
    if (!key_file) {
        return -FileNotExists;
    }
    
    int size = 0;
    switch(mode) {
        case Encrypt:
            size = fread(&mEncryptKey, 1, sizeof(AES_KEY), key_file);
        break;

        case Decrypt:
            size = fread(&mDecryptKey, 1, sizeof(AES_KEY), key_file);
        break;
    }
    
    fclose(key_file);

    if(size <= 0) {
        return -ReadFail;
    }

    return 0;
}

void _Aes::decrypt(File src,File des) {
    _aseFile(src,des);
}

void _Aes::encrypt(File src,File des) {
    _aseFile(src,des);
}


ByteArray _Aes::_aseFile(File in,File out) {
    if(!out->exists()) {
        out->createNewFile();
    }

    FileInputStream inputStream = createFileInputStream(in);
    inputStream->open();
    ByteArray inputData = inputStream->readAll();

    if(inputData != nullptr) {

        ByteArray outputData = nullptr;
        switch(getMode()) {
            case Decrypt: {
                outputData = encrypt(inputData);
            }
            break;

            case Encrypt: {
                outputData = decrypt(inputData);
            }
            break;
        }
        
        FileOutputStream outputStream = createFileOutputStream(out);
        outputStream->open(st(OutputStream)::Trunc);
        outputStream->write(outputData,outputData->size());
        
        //outputStream->write(outputData);
        outputStream->flush();
        outputStream->close();
    }

    inputStream->close();
}
    
ByteArray _Aes::encrypt(ByteArray buff) {
    if(getMode() != Encrypt) {
        Trigger(IllegalStateException,"do encrypt,but mode is decrypt");
    }

    switch(getPattern()) {
        case ECB:
            return _aesECB(buff);
        break;

        case CBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv);
        break;
    }

    return nullptr;
}

ByteArray _Aes::decrypt(ByteArray buff) {
    if(getMode() != Encrypt) {
        Trigger(IllegalStateException,"do decrypt,but mode is encrypt");
    }

    switch(getPattern()) {
        case ECB:
            return _aesECB(buff);
        break;

        case CBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv);
        break;
    }

    return nullptr;
}

int _Aes::_genKey(String content) {
    const char *c = content->toChars();
    char keyBuff[AES_BLOCK_SIZE + 1];
    memset(keyBuff,0,AES_BLOCK_SIZE + 1);
    
    if(content->size() > AES_BLOCK_SIZE) {
        memcpy(keyBuff,c,AES_BLOCK_SIZE);
    } else {
        memcpy(keyBuff,c,content->size());
    }

    if(AES_set_encrypt_key((const unsigned char*)keyBuff,128,&mEncryptKey) != 0) {
        return -GenKeyFail;
    }

    if(AES_set_decrypt_key((const unsigned char*)keyBuff,128,&mDecryptKey) != 0) {
        return -GenKeyFail;
    }

    return 0;
}

int _Aes::_genKey() {
    UUID uuid = createUUID();
    const char *c = uuid->generate()->toChars();
    
    if(AES_set_encrypt_key((const unsigned char*)c,128,&mEncryptKey) != 0) {
        return -SetKeyFail;
    }

    if(AES_set_decrypt_key((const unsigned char*)c,128,&mDecryptKey) != 0) {
        return -SetKeyFail;
    }

    return 0;
}

int _Aes::_saveKey(String filepath,int mode) {
    FILE *key_file = fopen(filepath->toChars(), "wb");
    short int bytes_written = 0;
    int size = 0;
    switch(mode) {
        case st(Cipher)::Encrypt:
            size = fwrite(&mEncryptKey, 1, sizeof(AES_KEY), key_file);
        break;

        case st(Cipher)::Decrypt:
            size = fwrite(&mDecryptKey, 1, sizeof(AES_KEY), key_file);
        break;
    }
    
    fclose(key_file);

    if(size <= 0) {
        return  -1;
    }
    
    return 0;
}

ByteArray _Aes::_aesECB(ByteArray data) {
    int inputSize = data->size();
    doPadding(data,AES_BLOCK_SIZE);

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();

    switch(getMode()) {
        case Encrypt: {
            for(int i = 0; i < length/AES_BLOCK_SIZE; i++){
                AES_ecb_encrypt((unsigned char*)input,(unsigned char*)output,&mEncryptKey,AES_ENCRYPT);
                input += AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }
        }

        case Decrypt: { 
            for(int i = 0;i<inputSize/AES_BLOCK_SIZE;i++) {
                AES_ecb_encrypt((unsigned char *)input,(unsigned char *)output,&mDecryptKey,AES_DECRYPT);
                input+= AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }
        }
    }

    doUnPadding(out);
    
    return out;
    
}

ByteArray _Aes::_aesCBC(ByteArray data,unsigned char *ivec) {
    int inputSize = data->size();
    doPadding(data,AES_BLOCK_SIZE);

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();

    switch(getMode()) {
        case Encrypt:{
            AES_cbc_encrypt((unsigned char *)input,(unsigned char *)output,length,&mEncryptKey,ivec,AES_ENCRYPT);
        }
        break;

        case Decrypt:{
            AES_cbc_encrypt((unsigned char *)input,(unsigned char *)output,inputSize,&mDecryptKey,ivec,AES_DECRYPT);
        }
        break;
    }

    doUnPadding(out);

    return out;
}

}
