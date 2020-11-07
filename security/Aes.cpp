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

static unsigned char default_iv[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

ByteArray _Aes::encrypt(ByteArray buff) {
    if(getMode() != Encrypt) {
        Trigger(IllegalStateException,"do encrypt,but mode is decrypt");
    }

    switch(getPattern()) {
        case ECB:
            return _aesECB(buff);
        break;

        case CBC:
            
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
            return _aesCBC(buff,default_iv);
        break;
    }

    return nullptr;
}

ByteArray _Aes::_aesECB(ByteArray data) {
    int inputSize = data->size();
    if(getMode() == Encrypt) {
        doPKCS7Padding(data,AES_BLOCK_SIZE);
    }
    
    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    
    switch(getMode()) {
        case Encrypt: {
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
    
    if(getMode() == Decrypt) {
        doPKCS7UnPadding(out);
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
