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

ByteArray _Aes::encrypt(ByteArray buff) {
    if(getMode() != Encrypt) {
        Trigger(IllegalStateException,"do encrypt,but mode is decrypt");
    }
    printf("start encrypt \n");

    switch(getPattern()) {
        case ECB:
            printf("start encrypt1 \n");
            return _aesECB(buff);
        break;

        case CBC:
            printf("start encrypt2 \n");
            unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return _aesCBC(buff,default_iv);
        break;
    }

    return nullptr;
}

ByteArray _Aes::decrypt(ByteArray buff) {
    if(getMode() != Decrypt) {
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

ByteArray _Aes::_aesECB(ByteArray data) {
    int inputSize = data->size();
    printf("_aesECB start \n");
    if(getMode() == Encrypt) {
        printf("_aesECB trace1 \n");
        doPKCS7Padding(data,AES_BLOCK_SIZE);
    }
    printf("11111 data size is %d \n",data->size());

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    printf("_aesECB trace2 \n");
    switch(getMode()) {
        case Encrypt: {
            printf("_aesECB trace3,length is %d,AES_BLOCK_SIZE is %d \n",length,AES_BLOCK_SIZE);
            for(int i = 0; i < length/AES_BLOCK_SIZE; i++){
                AES_ecb_encrypt((unsigned char*)input,
                                (unsigned char*)output,
                                (const AES_KEY *)getSecretKey()->get(),
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
                                (const AES_KEY *)getSecretKey()->get(),
                                AES_DECRYPT);
                input+= AES_BLOCK_SIZE;
                output += AES_BLOCK_SIZE;
            }
        }
        break;
    }
    printf("_aesECB trace4 \n");
    if(getMode() == Decrypt) {
        printf("_aesECB trace5 \n");
        doPKCS7UnPadding(out);
        printf("_aesECB trace5_1 size is %d \n",out->size());
    }
    
     
    return out;
    
}

ByteArray _Aes::_aesCBC(ByteArray data,unsigned char *ivec) {
    int inputSize = data->size();
    if(getMode() == Encrypt) {
        doPadding(data,AES_BLOCK_SIZE);
    }

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();

    switch(getMode()) {
        case Encrypt:{
            AES_cbc_encrypt((unsigned char *)input,
                            (unsigned char *)output,
                            length,
                            (const AES_KEY *)getSecretKey()->get(),
                            ivec,
                            AES_ENCRYPT);
        }
        break;

        case Decrypt:{
            AES_cbc_encrypt((unsigned char *)input,
                            (unsigned char *)output,
                            inputSize,
                            (const AES_KEY *)getSecretKey()->get(),
                            ivec,
                            AES_DECRYPT);
        }
        break;
    }
    
    if(getMode() == Decrypt) {
        doUnPadding(out);
    }

    return out;
}

}
