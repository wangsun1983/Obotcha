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

//static const unsigned char default_iv[] =
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

_Aes::_Aes() {
    mType = AesTypeECB;
}

_Aes::_Aes(int aestype) {
    mType = aestype;
}

int _Aes::genKey(String decKeyFile,String encKeyFile) {
    int result = _genKey();
    if(result != 0) {
        return result;
    }
    
    result = _saveKey(encKeyFile,AesEncrypt);
    if(result != 0) {
        return result;
    }

    result = _saveKey(decKeyFile,AesDecrypt);

    return result;
}

int _Aes::genKey(String decKeyFile,String encKeyFile,String content) {
    int result = _genKey(content);
    if(result != 0) {
        return result;
    }

    result = _saveKey(encKeyFile,AesEncrypt);
    if(result != 0) {
        return result;
    }

    result = _saveKey(decKeyFile,AesDecrypt);

    return result;
}

int _Aes::loadKey(File file,int mode) {
    return loadKey(file->getAbsolutePath(),mode);
}

int _Aes::loadKey(String path,int mode) {
    return loadKey(path->toChars(),mode);
}

int _Aes::loadKey(const char *filepath,int mode) {
    FILE *key_file = fopen(filepath, "rb");
    if (!key_file) {
        return -FileNotExists;
    }
    
    int size = 0;
    switch(mode) {
        case AES_ENCRYPT:
            size = fread(&mEncryptKey, 1, sizeof(AES_KEY), key_file);
        break;

        case AES_DECRYPT:
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
        outputStream->open(FileOpenType::Trunc);
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
    switch(mType) {
        case AesTypeECB:
            outData = _aesECB(inputData,AES_ENCRYPT);
        break;

        case AesTypeCBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            outData = _aesCBC(inputData,default_iv,AES_ENCRYPT);
        break;
    }

    if(outData != nullptr) {
        FileOutputStream outputStream = createFileOutputStream(des);
        outputStream->open(FileOpenType::Trunc);
        outputStream->write(outData);
        outputStream->flush();
        outputStream->close();
    }
}

ByteArray _Aes::encrypt(String str) {
    ByteArray result;

    switch(mType) {
        case AesTypeECB:
            result = _aesECB(createByteArray(str),AES_ENCRYPT);
        break;

        case AesTypeCBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            result = _aesCBC(createByteArray(str),default_iv,AES_ENCRYPT);
        break;
    }

    return result;
}
    
ByteArray _Aes::encrypt(ByteArray buff) {
    switch(mType) {
        case AesTypeECB:
            return _aesECB(buff,AES_ENCRYPT);
        break;

        case AesTypeCBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv,AES_ENCRYPT);
            //return buff;
        break;
    }

    return nullptr;
}

ByteArray _Aes::decrypt(ByteArray buff) {
    switch(mType) {
        case AesTypeECB:
            return _aesECB(buff,AES_DECRYPT);
        break;

        case AesTypeCBC:
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv,AES_DECRYPT);
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
    const char *c = uuid->toValue()->toChars();
    
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
        case AES_ENCRYPT:
            size = fwrite(&mEncryptKey, 1, sizeof(AES_KEY), key_file);
        break;

        case AES_DECRYPT:
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
        case AES_ENCRYPT: {
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
                AES_ecb_encrypt((unsigned char*)input,(unsigned char*)output,&mEncryptKey,AES_ENCRYPT);
                input += AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }

            return out;
        }

        case AES_DECRYPT: {
            ByteArray out = createByteArray(inputSize);
            char *input = (char *)data->toValue();
            char *output = (char *)out->toValue();
            for(int i = 0;i<inputSize/AES_BLOCK_SIZE;i++) {
                AES_ecb_encrypt((unsigned char *)input,(unsigned char *)output,&mDecryptKey,AES_DECRYPT);
                input+= AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }

            int padding = 0;
            if(out->toValue()[(inputSize-1)] != 0) {
                padding = out->toValue()[(inputSize-1)];
            }
                
            if(padding == 0) {
                out->qucikShrink(inputSize - AES_BLOCK_SIZE);
            } else {
                out->qucikShrink(inputSize - AES_BLOCK_SIZE + padding);
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
        case AES_ENCRYPT:{
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

            AES_cbc_encrypt((unsigned char *)input,(unsigned char *)output,length,&mEncryptKey,ivec,AES_ENCRYPT);
            return out;
        }
        break;

        case AES_DECRYPT:{
            ByteArray out = createByteArray(inputSize);
            char *output = (char *)out->toValue();
            char *input = (char *)data->toValue();
            AES_cbc_encrypt((unsigned char *)input,(unsigned char *)output,inputSize,&mDecryptKey,ivec,AES_DECRYPT);
            int padding = output[inputSize - 1];

            out->qucikShrink(inputSize - AES_BLOCK_SIZE + padding);
            return out;
        }
            
        break;
    }

    return nullptr;
}

}
