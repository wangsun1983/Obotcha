#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aes.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"

#include "UUID.hpp"

namespace obotcha {

//static const unsigned char default_iv[] =
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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

void _Aes::decrypt(File src,File des) {
    //printf("wangsl,decrypt 1 \n");
    //printf("src path is %s,des path is %s \n",src->getAbsolutePath()->toChars(),des->getAbsolutePath()->toChars());
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

        //we should check last 8byte
        char *checkP = outputData->toValue();
        printf("decrypt checkP is %s \n",checkP);
        int length = outputData->size();

        int padding = 0;
        if(checkP[(length-1)] != 0) {
            padding = checkP[(length-1)];
        }
        printf("padding is %d \n",padding);
                
        if(padding == 0) {
            outputStream->write(outputData,length - AES_BLOCK_SIZE);
        } else {
            outputStream->write(outputData,length - AES_BLOCK_SIZE + padding);
        }

        //outputStream->write(outputData);
        outputStream->flush();
        outputStream->close();
    }
}


String _Aes::decrypt(String str) {
    ByteArray result;

    switch(mType) {
        case AesTypeECB:
        printf("encrypt ecb \n");
            result = _aesECB(createByteArray(str),AES_DECRYPT);
        break;

        case AesTypeCBC:
        printf("encrypt cbc \n");
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            result = _aesCBC(createByteArray(str),default_iv,AES_DECRYPT);
        break;
    }

    char *p = result->toValue();
    return createString(p);
}


void _Aes::encrypt(File src,File des) {
    //printf("wangsl,decrypt 1 \n");
    printf("wangsl,encrypt 1 \n");
    printf("encrypt src path is %s,des path is %s \n",src->getAbsolutePath()->toChars(),des->getAbsolutePath()->toChars());
    
    if(!des->exists()) {
        des->createNewFile();
    }

    FileInputStream inputStream = createFileInputStream(src);
    inputStream->open();
    //calcute size for 8 byte
    long inputSize = src->length();
    long length = (inputSize%AES_BLOCK_SIZE == 0)?(inputSize + AES_BLOCK_SIZE):(inputSize/AES_BLOCK_SIZE)*AES_BLOCK_SIZE + AES_BLOCK_SIZE;
    ByteArray inputData = createByteArray(length);
    inputStream->readAll(inputData);

    if(inputSize%AES_BLOCK_SIZE == 0) {
        char *lastData = inputData->toValue() + (inputData->size() - 1) - AES_BLOCK_SIZE;
        memset(lastData,0,AES_BLOCK_SIZE);
        printf("encrypt padding is %d \n",0);
    } else {
        int padding = inputSize%AES_BLOCK_SIZE;
        printf("encrypt padding is %d \n",padding);
        char *lastData = inputData->toValue() + inputData->size()  - AES_BLOCK_SIZE + padding;
        memset(lastData,(char)padding,AES_BLOCK_SIZE-padding);
    }
    //ByteArray inputData = inputStream->readAll();
    printf("encrypt inputData size is %d \n",inputData->size());

    if(inputData != nullptr) {
        ByteArray outputData = encrypt(inputData);
        printf("encrypt outputData size is %d \n",outputData->size());
        FileOutputStream outputStream = createFileOutputStream(des);
        outputStream->open(FileOpenType::Trunc);
        outputStream->write(outputData);
        outputStream->flush();
        outputStream->close();
    }
}

String _Aes::encrypt(String str) {
    printf("ase encrypt str\n");
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

    char *p = result->toValue();
    return createString(p);
}
    
ByteArray _Aes::encrypt(ByteArray buff) {
    printf("ase encrypt buff\n");
    switch(mType) {
        case AesTypeECB:
            printf("ase encrypt buff1\n");
            return _aesECB(buff,AES_ENCRYPT);
        break;

        case AesTypeCBC:
            printf("ase encrypt buff2\n");
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
    unsigned char *in = (unsigned char *)data->toValue();
    printf("_aesCBC size is %d \n",data->size());
    ByteArray outData = createByteArray(data->size());
    unsigned char *out = (unsigned char *)outData->toValue();
    switch(mode) {
        case AES_ENCRYPT:
            AES_cbc_encrypt(in,out,data->size(),&mEncryptKey,ivec,AES_ENCRYPT);
        break;

        case AES_DECRYPT:
            AES_cbc_encrypt(in,out,data->size(),&mDecryptKey,ivec,AES_DECRYPT);
        break;
    }
    
    return outData;
}

}