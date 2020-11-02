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

//xxxxx(content)/RSA TYPE/RSA HEAD Type
int _Aes::genKey(String decKeyFile,String encKeyFile,ArrayList<String>params) {
    int result = -1;

    AES_KEY encryptKey;
    AES_KEY decryptKey;

    if(params != nullptr && params->size() != 0) {
        result = _genKey(params->get(0),&encryptKey,&decryptKey);
    } else {
        result = _genKey(nullptr,&encryptKey,&decryptKey);
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

void _Aes::decrypt(File src,File des) {
    _aseFile(src,des);
}

void _Aes::encrypt(File src,File des) {
    _aseFile(src,des);
}


void _Aes::_aseFile(File in,File out) {
  
    printf("out path is %s \n",out->getAbsolutePath()->toChars());
    if(!out->exists()) {
        printf("create file \n");
        out->createNewFile();
    }
  
    FileInputStream inputStream = createFileInputStream(in);
    inputStream->open();
    ByteArray inputData = inputStream->readAll();

    if(inputData != nullptr) {
        FileOutputStream outputStream = createFileOutputStream(out);
        ByteArray outputData = nullptr;
        
        switch(getMode()) {
            case Decrypt: {
                outputData = decrypt(inputData);
            }
            break;

            case Encrypt: {
                outputData = encrypt(inputData);
            }
            break;
        }

        if(outputData != nullptr) {
            outputStream->open(st(OutputStream)::Trunc);
            outputStream->write(outputData);
            outputStream->flush();
            outputStream->close();
        }
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

int _Aes::_genKey(String content,AES_KEY *encrypt,AES_KEY *decrypt) {
    const char *c = nullptr;
    if(content == nullptr) {
        UUID uuid = createUUID();
        c = uuid->generate()->toChars();
    } else {
        c = content->toChars(); 
    }

    char keyBuff[AES_BLOCK_SIZE + 1];
    memset(keyBuff,0,AES_BLOCK_SIZE + 1);
    
    if(content->size() > AES_BLOCK_SIZE) {
        memcpy(keyBuff,c,AES_BLOCK_SIZE);
    } else {
        memcpy(keyBuff,c,content->size());
    }

    if(AES_set_encrypt_key((const unsigned char*)keyBuff,128,encrypt) != 0) {
        return -GenKeyFail;
    }

    if(AES_set_decrypt_key((const unsigned char*)keyBuff,128,decrypt) != 0) {
        return -GenKeyFail;
    }

    return 0;
}

ByteArray _Aes::_aesECB(ByteArray data) {
    int inputSize = data->size();
    printf("start data size is %d \n",data->size());
    doPadding(data,AES_BLOCK_SIZE);

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    printf("data length is %d,key path is %s \n",length,getSecretKey()->getFile()->getAbsolutePath()->toChars());

    switch(getMode()) {
        case Encrypt: {
            printf("AES encrypt \n");
            for(int i = 0; i < length/AES_BLOCK_SIZE; i++){
                AES_ecb_encrypt((unsigned char*)input,
                                (unsigned char*)output,
                                (const AES_KEY *)getSecretKey()->getContent()->toValue(),
                                AES_ENCRYPT);
                input += AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }
        }
        break;

        case Decrypt: { 
            for(int i = 0;i<inputSize/AES_BLOCK_SIZE;i++) {
                AES_ecb_encrypt((unsigned char *)input,
                                (unsigned char *)output,
                                (const AES_KEY *)getSecretKey()->getContent()->toValue(),
                                AES_DECRYPT);
                input+= AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }
        }
        break;
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
            AES_cbc_encrypt((unsigned char *)input,
                            (unsigned char *)output,
                            length,
                            (const AES_KEY *)getSecretKey()->getContent()->toValue(),
                            ivec,
                            AES_ENCRYPT);
        }
        break;

        case Decrypt:{
            AES_cbc_encrypt((unsigned char *)input,
                            (unsigned char *)output,
                            inputSize,
                            (const AES_KEY *)getSecretKey()->getContent()->toValue(),
                            ivec,
                            AES_DECRYPT);
        }
        break;
    }

    doUnPadding(out);

    return out;
}

}
