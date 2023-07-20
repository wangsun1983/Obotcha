extern "C" {
    #include "openssl/aes.h"
}

#include "Aes.hpp"
#include "ByteArray.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

ByteArray _Aes::encrypt(ByteArray buff) {
    if(getMode() != Encrypt) {
        Trigger(IllegalStateException,"do encrypt,but mode is decrypt");
    }

    switch(getPattern()) {
        case ECB:
            return _aesECB(buff);

        case CBC:
            return _aesCBC(buff);

        case CFB1:
            return _aesCFB1(buff);
        
        case CFB8:
            return _aesCFB8(buff);
        
        case CFB128:
            return _aesCFB128(buff);

        case OFB128:
            return _aesOFB128(buff);
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

        case CBC:
            return _aesCBC(buff);

        case CFB1:
            return _aesCFB1(buff);
        
        case CFB8:
            return _aesCFB8(buff);
        
        case CFB128:
            return _aesCFB128(buff);

        case OFB128:
            return _aesOFB128(buff);
    }

    return nullptr;
}

ByteArray _Aes::_aesECB(ByteArray data) {
    int inputSize = data->size();
    int type = AES_DECRYPT;

    if(getMode() == Encrypt) {
        doPadding(data,AES_BLOCK_SIZE);
        type = AES_ENCRYPT;
    }
    
    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    
    for(int i = 0; i < length/AES_BLOCK_SIZE; i++) {
        AES_ecb_encrypt((unsigned char*)input,
                        (unsigned char*)output,
                        (const AES_KEY *)getSecretKey()->get(),
                        type);
        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
    }

    if(getMode() == Decrypt) {
        doUnPadding(out);
    }
 
    return out;
}

ByteArray _Aes::_aesCBC(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int type = AES_DECRYPT;

    if(getMode() == Encrypt) {
        doPadding(data,AES_BLOCK_SIZE);
        type = AES_ENCRYPT;
    }

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();

    int length = data->size();
    AES_cbc_encrypt((unsigned char *)input,
                    (unsigned char *)output,
                    length,
                    (const AES_KEY *)getSecretKey()->get(),
                    ivec,
                    type);
    
    if(getMode() == Decrypt) {
        doUnPadding(out);
    }

    return out;
}

ByteArray _Aes::_aesCFB1(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };    
    int type = AES_DECRYPT;
    if(getMode() == Encrypt) {
        type = AES_ENCRYPT;
    }

    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    int num = 0;

    AES_cfb1_encrypt((const unsigned char *)input,
                    (unsigned char *)output,
                    length*8,
                    (const AES_KEY *)getSecretKey()->get(),
                    ivec,
                    &num,
                    type);

    return out;
}

ByteArray _Aes::_aesCFB8(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    int type = AES_DECRYPT;
    if(getMode() == Encrypt) {
        type = AES_ENCRYPT;
    }
    
    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    int num = 0;

    AES_cfb8_encrypt((const unsigned char *)input,
                    (unsigned char *)output,
                    length,
                    (const AES_KEY *)getSecretKey()->get(),
                    ivec,
                    &num,
                    type);
                    
    return out;
}

ByteArray _Aes::_aesCFB128(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int type = AES_DECRYPT;
    if(getMode() == Encrypt) {
        type = AES_ENCRYPT;
    }
    
    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    int num = 0;

    AES_cfb128_encrypt((unsigned char *)input,
                        (unsigned char *)output,
                        length,
                        (const AES_KEY *)getSecretKey()->get(),
                        ivec,
                        &num,
                        type);

    return out;
}

ByteArray _Aes::_aesOFB128(ByteArray data) {
    unsigned char ivec[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ByteArray out = createByteArray(data->size());
    char *output = (char *)out->toValue();
    char *input = (char *)data->toValue();
    int length = data->size();
    int num = 0;
    
    AES_ofb128_encrypt((unsigned char *)input,
                                (unsigned char *)output,
                                length,
                                (const AES_KEY *)getSecretKey()->get(),
                                ivec,
                                &num);
    return out;
}

}
