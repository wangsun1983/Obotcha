#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aes.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
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
    if(!des->exists()) {
        des->createNewFile();
    }

    FileInputStream inputStream = createFileInputStream(src);
    inputStream->open();
    ByteArray inputData = inputStream->readAll();

    if(inputData != nullptr) {
        ByteArray outputData = decrypt(inputData);
        FileOutputStream outputStream = createFileOutputStream(des);
        outputStream->open(st(OutputStream)::Trunc);
        outputStream->write(outputData,outputData->size());
        
        //outputStream->write(outputData);
        outputStream->flush();
        outputStream->close();
    }
}

void _Aes::encrypt(File src,File des) {
    
    if(!des->exists()) {
        des->createNewFile();
    }
    
    FileInputStream inputStream = createFileInputStream(src);
    inputStream->open();
    ByteArray inputData = inputStream->readAll();
    ByteArray outData;
    switch(getPattern()) {
        case ECB:
            outData = _aesECB(inputData,Encrypt);
        break;

        case CBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            outData = _aesCBC(inputData,default_iv,Encrypt);
        break;
    }

    if(outData != nullptr) {
        FileOutputStream outputStream = createFileOutputStream(des);
        outputStream->open(st(OutputStream)::Trunc);
        outputStream->write(outData);
        outputStream->flush();
        outputStream->close();
    }
}
    
ByteArray _Aes::encrypt(ByteArray buff) {
    switch(getPattern()) {
        case ECB:
            return _aesECB(buff,Encrypt);
        break;

        case CBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv,Encrypt);
            //return buff;
        break;
    }

    return nullptr;
}

ByteArray _Aes::decrypt(ByteArray buff) {
    switch(getPattern()) {
        case ECB:
            return _aesECB(buff,Decrypt);
        break;

        case CBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv,Decrypt);
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

ByteArray _Aes::_aesECB(ByteArray data,int mode) {
    int inputSize = data->size();

    switch(mode) {
        case Encrypt: {
            int length = (inputSize%AES_BLOCK_SIZE == 0)?inputSize + AES_BLOCK_SIZE:(inputSize/AES_BLOCK_SIZE)*AES_BLOCK_SIZE + AES_BLOCK_SIZE;
    
            ByteArray out = createByteArray(length);
            ByteArray in = createByteArray(data->toValue(),length);

            char *output = (char *)out->toValue();
            char *input = (char *)in->toValue();
            //we should fill the last 8 byte data;
            if(inputSize%AES_BLOCK_SIZE == 0) {
                char *lastData = input + length - AES_BLOCK_SIZE;
                memset(lastData,0,AES_BLOCK_SIZE);
            } else {
                int padding = inputSize%AES_BLOCK_SIZE;
                char *lastData = input + inputSize;
                memset(lastData,(char)padding,AES_BLOCK_SIZE-padding);
            }

            for(int i = 0; i < length/AES_BLOCK_SIZE; i++){
                //memcpy(input,input,AES_BLOCK_SIZE);
                AES_ecb_encrypt((unsigned char*)input,(unsigned char*)output,&mEncryptKey,Encrypt);
                input += AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }

            return out;
        }

        case Decrypt: {
            ByteArray out = createByteArray(inputSize);
            char *input = (char *)data->toValue();
            char *output = (char *)out->toValue();
            for(int i = 0;i<inputSize/AES_BLOCK_SIZE;i++) {
                AES_ecb_encrypt((unsigned char *)input,(unsigned char *)output,&mDecryptKey,Decrypt);
                input+= AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }

            int padding = 0;
            if(out->toValue()[(inputSize-1)] != 0) {
                padding = out->toValue()[(inputSize-1)];
            }
                
            if(padding == 0) {
                out->quickShrink(inputSize - AES_BLOCK_SIZE);
            } else {
                out->quickShrink(inputSize - AES_BLOCK_SIZE + padding);
            }

            return out;
        }

    }
    
    return nullptr;
    
}

ByteArray _Aes::_aesCBC(ByteArray data,unsigned char *ivec,int mode) {
    int inputSize = data->size();
    //int outputSize = inputSize%AES_BLOCK_SIZE?(inputSize/AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE : inputSize;
    switch(mode) {
        case Encrypt:{
            int length = (inputSize%AES_BLOCK_SIZE == 0)?inputSize + AES_BLOCK_SIZE:(inputSize/AES_BLOCK_SIZE)*AES_BLOCK_SIZE + AES_BLOCK_SIZE;
    
            ByteArray out = createByteArray(length);
            ByteArray in = createByteArray(data->toValue(),length);

            char *output = (char *)out->toValue();
            char *input = (char *)in->toValue();
            //we should fill the last 8 byte data;
            if(inputSize%AES_BLOCK_SIZE == 0) {
                char *lastData = input + length - AES_BLOCK_SIZE;
                memset(lastData,0,AES_BLOCK_SIZE);
            } else {
                int padding = inputSize%AES_BLOCK_SIZE;
                char *lastData = input + inputSize;
                memset(lastData,(char)padding,AES_BLOCK_SIZE-padding);
            }

            AES_cbc_encrypt((unsigned char *)input,(unsigned char *)output,length,&mEncryptKey,ivec,Encrypt);
            return out;
        }
        break;

        case Decrypt:{
            ByteArray out = createByteArray(inputSize);
            char *output = (char *)out->toValue();
            char *input = (char *)data->toValue();
            AES_cbc_encrypt((unsigned char *)input,(unsigned char *)output,inputSize,&mDecryptKey,ivec,Decrypt);
            int padding = output[inputSize - 1];

            out->quickShrink(inputSize - AES_BLOCK_SIZE + padding);
            return out;
        }
            
        break;
    }

    return nullptr;
}

}
